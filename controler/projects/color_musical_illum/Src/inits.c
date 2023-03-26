/*
 * inits.c
 *
 *  Created on: Mar 20, 2023
 *      Author: shishel
 */
#include "inits.h"


static void init_adc(void);
static void init_clk(void);
static void init_usart3(void);
static void init_spi(void);
static void init_tim3(void);
static void init_led_pb1(void);


void init_device(void)
{
	init_clk();
//	init_adc();
//	init_usart3();
	init_spi();
	//init_tim3();
	init_led_pb1();
}


void init_led_pb1(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	GPIOB->CRL |= GPIO_CRL_MODE1;
	GPIOB->CRL &= ~(GPIO_CRL_CNF1);
}


void init_spi(void)
{
	// SPI1 + remap
	// PB3 - SCK
	// PB4 - ~CS
	// PB5 - SI
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; // SPI clocking
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; // ports alternative function clocking
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // PB clocking

	AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE; // free PB3 PB4 from Jtag
	AFIO->MAPR |= AFIO_MAPR_SPI1_REMAP; // remap spi1 to PB3, pb4, pb5

	GPIOB->CRL |= GPIO_CRL_MODE3; // init PB3 50 Mhz, alt func push pull
	GPIOB->CRL &= ~(GPIO_CRL_CNF3);
	GPIOB->CRL |= GPIO_CRL_CNF3_1;

	GPIOB->CRL |= GPIO_CRL_MODE4;
	GPIOB->CRL &= ~(GPIO_CRL_CNF4);  // general purpose

	GPIOB->CRL |= GPIO_CRL_MODE5; // init PB5 50 Mhz, alt func push pull
	GPIOB->CRL &= ~(GPIO_CRL_CNF5);
	GPIOB->CRL |= GPIO_CRL_CNF5_1;


	SPI1->CR1 |= SPI_CR1_LSBFIRST; // LSB
	SPI1->CR1 &= ~(SPI_CR1_BR);
	SPI1->CR1 |= SPI_CR1_BR_1; // 010 = f MCU / 8 = 8Mhz
	SPI1->CR1 |= SPI_CR1_MSTR; // master mode

	SPI1->CR1 |= SPI_CR1_CPHA;
	SPI1->CR1 &= ~(SPI_CR1_DFF);
	SPI1->CR1 |= SPI_CR1_DFF; // 16 bit to send

	SPI1->CR1 |= SPI_CR1_SPE; // turn on spi
	ON_PB4();// turn CS to high
}


// timer for meas sqrt
void init_tim3(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->PSC = TIM3_PSC - 1; // timer period 10 kHz
	TIM3->CNT = 0; //  tic in 0,1 ms
	TIM3->ARR = (2 << 16) - 1; // max val
}


/**
  * @brief  Инициализация USART2
  * @param  None
  * @retval None
  */
void init_usart3(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;						//включить тактирование альтернативных ф-ций портов
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;					//включить тактирование UART2

	GPIOB->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10);		//PB10 на выход
	GPIOB->CRH |= (GPIO_CRH_MODE10_1 | GPIO_CRH_CNF10_1);

	GPIOB->CRH &= ~(GPIO_CRH_MODE11 | GPIO_CRH_CNF11);		//PB11 - вход
	GPIOB->CRH |= GPIO_CRH_CNF11_0;

	/*****************************************
	Скорость передачи данных - 115200 / 9600
	Частота шины APB1 - 32МГц
	1. USARTDIV = 32'000'000/(16*115200) = 17.4
	2. 17 = 0x11 .. 0xD0
	3. 16*0.4 = 6
	4. Итого 0x116 .. 0xD06
	*****************************************/
	USART3->BRR = 0xD06;

	USART3->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
	USART3->CR1 |= USART_CR1_RXNEIE;						//разрешить прерывание по приему байта данных

	NVIC_EnableIRQ(USART3_IRQn);
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


	ADC1->CR2 |= ADC_CR2_CONT; // continuous mode //as fast as can
	ADC1->CR1 &= ~(ADC_CR1_SCAN); // no scan mode

	ADC1->CR2 |= ADC_CR2_ADON; // turn on adc

	// calibration
	delay(DEL_ADC); // wait to stabilization adc
	ADC1->CR2 |= ADC_CR2_CAL; // start calibration
	while (ADC1->CR2 & ADC_CR2_CAL) ;// wait finish of calibration


	ADC1->CR2 |= ADC_CR2_EXTTRIG; // enable conversion on external event
	ADC1->CR2 |= ADC_CR2_EXTSEL;  // turn on by SWSTART
	ADC1->CR2 |= ADC_CR2_SWSTART; // turn on
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


