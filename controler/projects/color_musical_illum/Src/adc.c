/*
 * adc.c
 *
 *  Created on: 28 мар. 2023 г.
 *      Author: Shishel
 */
#include "color_musical_illum.h"
#include "adc.h"
#include "digital_pot.h"

// debug
#include "usart.h"

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
	u8 signal_ampl = 0;
	u8 volt_max = 0;
	u8 volt_min = 0xFF;
	u8 dpot_res = get_depot_res();

	// debug
	char tx_buf[32] = { 0 };
	for(u16 i = 0; i < size; i++)
	{
		if (i % CALIB_MEAS_NUM == 0)
		{
			signal_ampl = volt_max - volt_min;
			if (signal_ampl < LOWER_AMPL_LIMIT)
			{	// increase gain
				dpot_res = (dpot_res + 1 > MAX_DPOT_RES) ? MAX_DPOT_RES : dpot_res + 1;
				send_res_dpot(dpot_res, ADD_200_OHM);// add dpot_1
//				sprintf(tx_buf, "dpot = %d\r\n", dpot_res);
//				tx_str(tx_buf);
			}
			else if (signal_ampl > HIGHER_AMPL_LIMIT)
			{
				// decrease gain
				dpot_res = (dpot_res - 1 == 0) ? 0 : dpot_res - 1;
				send_res_dpot(dpot_res, ADD_200_OHM);// decrease dpot 1
//				sprintf(tx_buf, "dpot = %d\r\n", dpot_res);
//				tx_str(tx_buf);
			}
		}
		while ( !tim4_enable) {};
		parr[i] = read_adc() >> 4;
		tim4_enable = 0;
		volt_max = (parr[i] > volt_max) ? parr[i] : volt_max;
		volt_min = (parr[i] < volt_min) ? parr[i] : volt_min;
	}
	STOP_TIM4();
	return parr;
}


