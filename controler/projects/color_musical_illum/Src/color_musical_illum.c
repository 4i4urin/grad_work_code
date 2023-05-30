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

static void show_u16(u16* parr, u16 size);
static void show_u8(u8* parr, u16 size);

u8 _inject[4] = { 0 };


u8 _meas_full_ready = 0;
u8 _meas_half_ready = 0;

char _tx_buf[MAX_TX_STR] = { 0 };

u8  _volts[MEAS_FULL_NUM] = { 0 };
u8* _pvolts = _volts;

t_fft _fft = { 0 };
u16* _pfft_abs = _fft.abs_res;
t_complex* _pfft_res = _fft.cmpx_val;


void coloor_music(void)
{

	if (_meas_half_ready)
	{
		sprintf(_tx_buf, "1 dpot = %d\tampl = %d\r\n",
				get_depot_res(), meas_max_ampl(_pvolts, MEAS_HALF_NUM));

		_pfft_abs = make_fft_abs(_pfft_res, _pfft_abs, _pvolts);
		*_pfft_abs = 0;
		_meas_half_ready = 0;
		tx_str(_tx_buf);
		OFF_CTRL_LED();
		if (ws2815_is_ready())
			freq_led_mode(_pfft_abs, _tx_buf);
	} else if (_meas_full_ready)
	{
		sprintf(_tx_buf, "2 dpot = %d\tampl = %d\r\n",
				get_depot_res(), meas_max_ampl(_pvolts + MEAS_HALF_NUM, MEAS_HALF_NUM));

		_pfft_abs = make_fft_abs(_pfft_res, _pfft_abs, _pvolts + MEAS_HALF_NUM);
		*_pfft_abs = 0;
		_meas_full_ready = 0;
		tx_str(_tx_buf);
		OFF_CTRL_LED();
		if (ws2815_is_ready())
			freq_led_mode(_pfft_abs, _tx_buf);
	}




	//one_colore_full_led(_inject[I_RED], _inject[I_GREEN], _inject[I_BLUE], _inject[I_BRIGHT]);
}


void show_u8(u8* parr, u16 size)
{
	for (u16 i = 0; i < size; i++)
	{
		sprintf(_tx_buf, "%d\r\n", parr[i]);
		tx_str(_tx_buf);
	}
}

void show_u16(u16* parr, u16 size)
{
	for (u16 i = 0; i < size; i++)
	{
		sprintf(_tx_buf, "-");
		tx_str(_tx_buf);
		while (parr[i] > 0)
		{
			sprintf(_tx_buf, "-");
			tx_str(_tx_buf);
			parr[i] -= 1;
		}
		tx_str("\r\n");
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

