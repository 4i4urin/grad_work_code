/*
 * inits.c
 *
 *  Created on: Jan 28, 2023
 *      Author: shishel
 */
#include "inits.h"

/**
  * @brief  Инициализация USART2
  * @param  None
  * @retval None
  */
void init_usart2(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;						//включить тактирование альтернативных ф-ций портов
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;					//включить тактирование UART2

	GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);		//PA2 на выход
	GPIOA->CRL |= (GPIO_CRL_MODE2_1 | GPIO_CRL_CNF2_1);

	GPIOA->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3);		//PA3 - вход
	GPIOA->CRL |= GPIO_CRL_CNF3_0;

	/*****************************************
	Скорость передачи данных - 115200
	Частота шины APB1 - 32МГц
	1. USARTDIV = 32'000'000/(16*115200) = 17.4
	2. 17 = 0x11
	3. 16*0.4 = 6
	4. Итого 0x116
	*****************************************/
	USART2->BRR = 0x116;

	USART2->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
	USART2->CR1 |= USART_CR1_RXNEIE;						//разрешить прерывание по приему байта данных

	NVIC_EnableIRQ(USART2_IRQn);
}


void init_adc(void)
{
	// PA0 ADC1 in0
	// gpio init PA0
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL &= ~(GPIO_CRL_CNF0); // 00 - analog mode
	GPIOA->CRL &= ~(GPIO_CRL_MODE0); // 00 - input mode

	// ADC in0
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	ADC1->SMPR2 &= ~(ADC_SMPR2_SMP0); // 000
	ADC1->SMPR2 |= ADC_SMPR2_SMP0_2 | ADC_SMPR2_SMP0_1 | ADC_SMPR2_SMP0_0; // 111 - sample time = 239,5 cycles

	ADC1->SQR1  &= ~(ADC_SQR1_L); 	// 1 conversion  // if was 0010 would be 3 conversion (require 3 channels)
	ADC1->SQR3  &= ~(ADC_SQR3_SQ1); // 0 channel is first conversion in regular

	ADC1->CR2 |= ADC_CR2_ADON; // turn on adc

	// calibration
	delay(DEL_ADC); // wait to stabilization adc
	ADC1->CR2 |= ADC_CR2_CAL; // start calibration
	while (ADC1->CR2 & ADC_CR2_CAL) ;// wait finish of calibration

	ADC1->CR2 &= ~(ADC_CR2_CONT); // no continuous mode
	ADC1->CR1 &= ~(ADC_CR1_SCAN); // no scan mode

	ADC1->CR2 |= ADC_CR2_EXTTRIG; // enable conversion on external event
	ADC1->CR2 |= ADC_CR2_EXTSEL;  // SWSTART
}


/**
 * @brief  Инициализация систем тактирования:
 * 		Источник тактирования: HSI
 * 		Частота: 64МГц
 * @param  None
 * @retval None
 */
void init_clk(void) {
	// Enable HSI
	RCC->CR |= RCC_CR_HSION;
	while (!(RCC->CR & RCC_CR_HSIRDY)) {
	};

	// Enable Prefetch Buffer
	FLASH->ACR |= FLASH_ACR_PRFTBE;

	// Flash 2 wait state
	FLASH->ACR &= ~FLASH_ACR_LATENCY;
	FLASH->ACR |= FLASH_ACR_LATENCY_2;

	// HCLK = SYSCLK
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

	// PCLK2 = HCLK
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

	// PCLK1 = HCLK
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

	// PLL configuration: PLLCLK = HSI/2 * 16 = 64 MHz
	RCC->CFGR &= ~RCC_CFGR_PLLSRC;
	RCC->CFGR |= RCC_CFGR_PLLMULL16;

	// Enable PLL
	RCC->CR |= RCC_CR_PLLON;

	// Wait till PLL is ready
	while ((RCC->CR & RCC_CR_PLLRDY) == 0) {
	};

	// Select PLL as system clock source
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	// Wait till PLL is used as system clock source
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {
	};
}


