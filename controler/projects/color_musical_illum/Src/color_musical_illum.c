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
#include "led_mode.h"


static u8 meas_max_ampl(u8* pvolts, u16 number);

u8 _num_led = 20;


u8 _meas_full_ready = 0;
u8 _meas_half_ready = 0;

char _tx_buf[MAX_TX_STR] = { 0 };

u8  _volts[MEAS_FULL_NUM] = { 0 };
u8* _pvolts = _volts;

u8 _ilum_mode = 0;

t_fft _fft = { 0 };
u16* _pfft_abs = _fft.abs_res;
t_complex* _pfft_res = _fft.cmpx_val;


void coloor_music(void)
{
	u8 max_ampl = 0;
	if (_meas_half_ready)
	{
		_pfft_abs = make_fft_abs(_pfft_res, _pfft_abs, _pvolts);
		max_ampl = meas_max_ampl(_pvolts, MEAS_HALF_NUM);
		_meas_half_ready = 0;
	} else if (_meas_full_ready)
	{
		_pfft_abs = make_fft_abs(_pfft_res, _pfft_abs, _pvolts + MEAS_HALF_NUM);
		max_ampl = meas_max_ampl(_pvolts + MEAS_HALF_NUM, MEAS_HALF_NUM);
		_meas_full_ready = 0;
	} else
		return;

	sprintf(_tx_buf, "dpot = %d\tampl = %d\r\n",
			get_depot_res(), max_ampl);
	tx_str(_tx_buf);

	*_pfft_abs = 0;
	OFF_CTRL_LED();
	switch (get_ilum_mode())
	{
	case 0: // sound
		if (get_depot_res() == MAX_DPOT_RES && max_ampl < LOWER_AMPL_LIMIT)
		{
			clear_led();
			break;
		}
		freq_led_mode(_pfft_abs, get_pctrl_panel());
		break;

	case 1: // sound
		if (get_depot_res() == MAX_DPOT_RES && max_ampl < LOWER_AMPL_LIMIT)
		{
			clear_led();
			break;
		}
		freq_led_linear_mode(_pfft_abs);
		break;

	case 2:
		one_colore_full_led(get_pctrl_panel());
		break;


	default:
		clear_led();
		break;
	}
}


void clear_led(void)
{
	tx_str("OFF LED OFF LED\r\n");
	ws2815_buff_clear();
	ws2815_send();
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


u8 get_ilum_mode(void)
{
	return _ilum_mode;
}


void set_ilum_mode(u8 new_mode)
{
	if (new_mode >= NUM_ILUM_MODE)
		new_mode = 0;
	_ilum_mode = new_mode;
	sprintf(_tx_buf, "MODE = %d\r\n", _ilum_mode);
	tx_str(_tx_buf);
}


inline u8 get_num_led(void)
{
	return _num_led;
}

void set_num_led(u8 number)
{
	if (number > MAX_LED_COUNT)
		return;
	_num_led = number;
}
