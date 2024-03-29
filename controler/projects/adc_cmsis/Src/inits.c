/*
 * inits.c
 *
 *  Created on: Jan 28, 2023
 *      Author: shishel
 */
#include "inits.h"


static void init_adc(void);
static void init_clk(void);
static void init_usart3(void);
static void init_tim4(void);
static void init_spi(void);
static void init_tim3(void);


void init_device(void)
{
	init_clk();
	init_adc();
	init_usart3();
	init_tim4();
	init_spi();
	init_tim3();
}


void init_spi(void)
{
	// SPI1 + remap
	// PB3 - SCK  	PA5 D13
	// PB4 - ~CS 	PA6 D12
	// PB5 - SI - MOSI PA7 D11
	// 8 bit
	// f clk = 10Mhz
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; // SPI clocking
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; // ports alternative function clocking
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // PB clocking
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

//	GPIOB->CRL |= GPIO_CRL_MODE3; // init PB3 50 Mhz, alt func push pull
//	GPIOB->CRL &= ~(GPIO_CRL_CNF3);
//	GPIOB->CRL |= GPIO_CRL_CNF3_1;
//
//	GPIOB->CRL |= GPIO_CRL_MODE4; // init PB4 50 Mhz, alt func push pull
//	GPIOB->CRL &= ~(GPIO_CRL_CNF4);
//	GPIOB->CRL |= GPIO_CRL_CNF4_1;
//
//	GPIOB->CRL |= GPIO_CRL_MODE5; // init PB5 50 Mhz, alt func push pull
//	GPIOB->CRL &= ~(GPIO_CRL_CNF5);
//	GPIOB->CRL |= GPIO_CRL_CNF5_1;

	GPIOA->CRL |= GPIO_CRL_MODE5; // init PB3 50 Mhz, alt func push pull
	GPIOA->CRL &= ~(GPIO_CRL_CNF5);
	GPIOA->CRL |= GPIO_CRL_CNF5_1;

//	GPIOA->CRL |= GPIO_CRL_MODE6; // init PB4 50 Mhz, alt func push pull
//	GPIOA->CRL &= ~(GPIO_CRL_CNF6);
//	GPIOA->CRL |= GPIO_CRL_CNF6_1;

	GPIOA->CRL |= GPIO_CRL_MODE6;
	GPIOA->CRL &= ~(GPIO_CRL_CNF6); // general purpose


	GPIOA->CRL |= GPIO_CRL_MODE7; // init PB5 50 Mhz, alt func push pull
	GPIOA->CRL &= ~(GPIO_CRL_CNF7);
	GPIOA->CRL |= GPIO_CRL_CNF7_1;

//	AFIO->MAPR |= AFIO_MAPR_SPI1_REMAP; // remap spi1 to PB3, pb4, pb5

	SPI1->CR1 |= SPI_CR1_LSBFIRST; // LSB
	SPI1->CR1 &= ~(SPI_CR1_BR);
	SPI1->CR1 |= SPI_CR1_BR_1 | SPI_CR1_BR_2; // 010 = f MCU / 8 = 8Mhz
	SPI1->CR1 |= SPI_CR1_MSTR; // master mode
	//SPI1->CR1 |= SPI_CR1_CPOL; // idel is 1
//	SPI1->CR1 |= SPI_CR1_BIDIMODE; // transmit only mode
	SPI1->CR1 |= SPI_CR1_CPHA;
	SPI1->CR1 &= ~(SPI_CR1_DFF);
	SPI1->CR1 |= SPI_CR1_DFF; // 16 bit to send

	SPI1->CR1 |= SPI_CR1_SPE; // turn on spi
	ON_PA6();// turn CS to high
}

// timer for meas sqrt
void init_tim3(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->PSC = TIM3_PSC - 1; // timer period 10 kHz
	TIM3->CNT = 0; //  tic in 0,1 ms
	TIM3->ARR = (2 << 16) - 1; // max val
}


// timer for reading adc
void init_tim4(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

	TIM4->PSC = TIM4_PSC - 1; // timer period 1 MHz
	TIM4->DIER |= TIM_DIER_UIE; // enable interrupts by update
	TIM4->CNT = 0;
	TIM4->ARR = 0;

//	TIM4->CR1 |= TIM_CR1_CEN;

	NVIC_EnableIRQ(TIM4_IRQn);				//Рарзрешить прерывание от TIM2
	NVIC_SetPriority(TIM4_IRQn, 1);			//Выставляем приоритет
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
	2. 17 = 0x11 / 0xD0
	3. 16*0.4 = 6
	4. Итого 0x116 / 0xD06
	*****************************************/
	USART3->BRR = 0x116;

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


