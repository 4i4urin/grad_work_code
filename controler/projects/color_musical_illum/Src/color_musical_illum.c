/*
 * color_musical_illum.c
 *
 *  Created on: May 10 2023
 *      Author: shishel
 */
#include "main.h"

#include "color_musical_illum.h"
#include "digital_pot.h"
#include "adc.h"
#include "usart.h"
#include "fft.h"
#include "ws2815.h"


u8 meas_max_ampl(u8* pvolts, u16 number);

u8 _inject[4] = { 0 };


u8 _meas_full_ready = 0;
u8 _meas_half_ready = 0;

char _tx_buf[MAX_TX_STR] = { 0 };

u8  _volts[MEAS_FULL_NUM] = { 0 };
u8* _pvolts = _volts;

t_fft _fft = { 0 };
u16* _pfft_abs = _fft.abs_res;
t_complex* _pfft_res = _fft.cmpx_val;
//u16 _fft_abs[FFT_DATA_NUM] = { 0 };
//u16* _pfft_abs = _fft_abs;
//
//t_complex _fft_res[FFT_DATA_NUM] = { 0 };
//t_complex* _pfft_res = _fft_res;



void coloor_music(void)
{
	if (_meas_half_ready)
	{
		sprintf(_tx_buf, "1 dpot = %d\tampl = %d\r\n",
				get_depot_res(), meas_max_ampl(_pvolts, MEAS_HALF_NUM));
		tx_str(_tx_buf);

		_pfft_abs = make_fft_abs(_pfft_res, _pfft_abs, _pvolts);
		OFF_CTRL_LED();
		_meas_half_ready = 0;
		if (!ws2812b_is_ready())
			set_dev_state(E_DEV_SLEEP);
		one_colore_full_led(_inject[0], _inject[1], _inject[2], _inject[3]);
	} else if (_meas_full_ready)
	{
		sprintf(_tx_buf, "2 dpot = %d\tampl = %d\r\n",
				get_depot_res(), meas_max_ampl(_pvolts + MEAS_HALF_NUM, MEAS_HALF_NUM));
		tx_str(_tx_buf);

		_pfft_abs = make_fft_abs(_pfft_res, _pfft_abs, _pvolts + MEAS_HALF_NUM);

		OFF_CTRL_LED();
		_meas_full_ready = 0;
		if (!ws2812b_is_ready())
			set_dev_state(E_DEV_SLEEP);
		one_colore_full_led(_inject[0], _inject[1], _inject[2], _inject[3]);
	}
}


u8 meas_max_ampl(u8* pvolts, u16 number)
{
	u8 min = 0xFF;
	u8 max = 0;
	for (u16 i = 0; i < number; i++)
	{
		if (pvolts[i] < min)
			min = pvolts[i];
		if (pvolts[i] > max)
			max = pvolts[i];
	}
	return max - min;
}

