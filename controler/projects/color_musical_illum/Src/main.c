#include "color_musical_illum.h"
#include "inits.h"
#include "digital_pot.h"
#include "adc.h"
#include "usart.h"
#include "fft.h"


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

e_device_state _dev_state = E_DEV_WORK;
u16 _inject[4] = { 0 };
u8 meas_max_ampl(u8* pvolts, u16 number);


u8 _meas_full_ready = 0;
u8 _meas_half_ready = 0;


int main(void)
{
	init_device();
	delay(1000000);
	send_res_dpot(50, ADD_200_OHM);
	char tx_buf[MAX_TX_STR] = { 0 };
	set_dev_state(E_DEV_WORK);
	start_adc_meas();


	while (1)
	{
		switch (get_dev_state())
		{
		case E_DEV_WORK:
			// do you work
			break;

		case E_DEV_CALIB:
			// change number of leds
			while (get_dev_state() != E_DEV_SLEEP) { }
			set_dev_state(E_DEV_WORK);
			break;

		case E_DEV_SLEEP:
			// turn device OFF
			set_dev_state(E_DEV_WORK);
			break;

		default:
			break;
			//return 1;
		}
		if (_meas_half_ready)
		{
			sprintf(tx_buf, "1 dpot = %d\tampl = %d\r\n",
					get_depot_res(), meas_max_ampl(_pvolts, MEAS_HALF_NUM));
			tx_str(tx_buf);

			_pfft_abs = make_fft_abs(_pfft_res, _pfft_abs, _pvolts);
			OFF_CTRL_LED();
			_meas_half_ready = 0;

		} else if (_meas_full_ready)
		{
			sprintf(tx_buf, "2 dpot = %d\tampl = %d\r\n",
					get_depot_res(), meas_max_ampl(_pvolts + MEAS_HALF_NUM, MEAS_HALF_NUM));
			tx_str(tx_buf);

			_pfft_abs = make_fft_abs(_pfft_res, _pfft_abs, _pvolts + MEAS_HALF_NUM);

			OFF_CTRL_LED();
			_meas_full_ready = 0;
		}
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


void set_dev_state(e_device_state state)
{
	switch (state)
	{
	case E_DEV_WORK:
	case E_DEV_SLEEP:
	case E_DEV_CALIB:
		break;

	default:
		return;
	}
	_dev_state = state;
}


inline e_device_state get_dev_state(void)
{
	return _dev_state;
}

// Задержка по попугаям
void delay(u32 del_val)
{
	while (del_val)
		del_val -= 1;
}
