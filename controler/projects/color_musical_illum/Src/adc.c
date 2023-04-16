/*
 * adc.c
 *
 *  Created on: 28 мар. 2023 г.
 *      Author: Shishel
 */
#include "color_musical_illum.h"
#include "adc.h"

static void start_tim4_khz(const u16 kHz);
static u16 read_adc(void);

u8 tim4_enable = 0;

//extern u8 _is_half_volts;

void DMA1_Channel1_IRQHandler(void)
{
	if (DMA1->ISR & DMA_ISR_HTIF1)
	{
		DMA1->IFCR |= DMA_IFCR_CHTIF1; // drop flag
		//_is_half_volts = 1;
	}

	else if (DMA1->ISR & DMA_ISR_TCIF1)
	{
		DMA1->IFCR |= DMA_IFCR_CTCIF1;// drop flag
		//_is_half_volts = 0;
	}
}


void TIM4_IRQHandler(void)
{
	TIM4->SR &= ~TIM_SR_UIF; // drop update flag
	tim4_enable = 1;
}

void start_tim4_khz(const u16 kHz)
{
	TIM4->ARR = TIM4_FREQ / (kHz * 1000); // set freq
	START_TIM4();
}

// Считываем значения с АЦП
u16 read_adc(void)
{
	//ADC1->CR2 |= ADC_CR2_SWSTART;
	//while ( !(ADC1->SR & ADC_SR_EOC) ) { } // wait finish of conversion
	return ADC1->DR;
}


u8* make_meas_adc(u8* parr, const u16 size, const u16 kHz)
{
	start_tim4_khz(kHz);
	for(u16 i = 0; i < size; i++)
	{
		while ( !tim4_enable) {};
		parr[i] = read_adc() >> 4;
		tim4_enable = 0;
	}
	STOP_TIM4();
	return parr;
}


