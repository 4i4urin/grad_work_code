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

void TIM4_IRQHandler()
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


