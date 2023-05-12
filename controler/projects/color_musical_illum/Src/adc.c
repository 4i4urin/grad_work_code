/*
 * adc.c
 *
 *  Created on: 28 мар. 2023 г.
 *      Author: Shishel
 */
#include "main.h"
#include "adc.h"
#include "digital_pot.h"

#include "usart.h"


static void calib_gain(u8 signal_ampl);


extern u8* _pvolts;
extern u8 _meas_half_ready;
extern u8 _meas_full_ready;

inline void start_adc_meas(void)
{
	TIM4->CR1 |= TIM_CR1_CEN;  // turn on timer4
}

inline void stop_adc_meas(void)
{
	TIM4->CR1 &= ~(TIM_CR1_CEN);  // turn off timer4
}


void TIM4_IRQHandler(void)
{
	if (TIM4->SR & TIM_SR_UIF)
	{
		static u16 i = 0;
		static u8 volt_max = 0;
		static u8 volt_min = 0xFF;

		if (_meas_half_ready && i < MEAS_HALF_NUM)
		{
			ON_CTRL_LED();
			TIM4->SR &= ~(TIM_SR_UIF);
			return;
		}
		if (_meas_full_ready && i >= MEAS_HALF_NUM)
		{
			ON_CTRL_LED();
			TIM4->SR &= ~(TIM_SR_UIF);
			return;
		}

		_pvolts[i] = ADC1->DR >> 4;

		if (i % CALIB_MEAS_NUM == 0)
		{
			calib_gain(volt_max - volt_min);
			volt_min = 0xFF; volt_max = 0;
		}
		volt_max = (_pvolts[i] > volt_max) ? _pvolts[i] : volt_max;
		volt_min = (_pvolts[i] < volt_min) ? _pvolts[i] : volt_min;

		if (i == MEAS_HALF_NUM)
		{
			_meas_half_ready = 1;
			i += 1;
		} else if (i == MEAS_FULL_NUM)
		{
			_meas_full_ready = 1;
			i = 0;
		} else
		{
			i += 1;
		}

		TIM4->SR &= ~(TIM_SR_UIF);
	}
}


void calib_gain(u8 signal_ampl)
{
	static u8 dpot_res = 0;
	dpot_res = get_depot_res();

	if (signal_ampl < LOWER_AMPL_LIMIT)
	{
		dpot_res = (dpot_res + 1 > MAX_DPOT_RES) ? MAX_DPOT_RES : dpot_res + 1;
		send_res_dpot(dpot_res, ADD_200_OHM);// decrease dpot 1
	}
	else if (signal_ampl > HIGHER_AMPL_LIMIT)
	{
		dpot_res = (dpot_res - 1 == 0) ? 0 : dpot_res - 1;
		send_res_dpot(dpot_res, ADD_200_OHM);// decrease dpot 1
	}
}
