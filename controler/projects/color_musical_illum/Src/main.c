#include "color_musical_illum.h"
#include "inits.h"
#include "digital_pot.h"
#include "adc.h"
#include "usart.h"
#include "fft.h"


u8 volts[MEAS_NUM] = { 0 };
u16 fft_abs[FFT_DATA_NUM << 1] = { 0 };
e_device_state _dev_state = E_DEV_WORK;
u16 _inject[4] = { 0 };
//u8 _is_half_volts = 0;


int main(void)
{
	init_device();
	delay(1000000);
	send_res_dpot(0, ADD_200_OHM);
	char tx_buf[MAX_TX_STR] = { 0 };
	u8* pvolts_first_half = volts;
	u8* pvolts_second_half = (&volts[0]) + (MEAS_NUM << 1);
	u16* pfft_res = fft_abs;

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
			return 1;
		}
		for (u8 dpot_res = 0; dpot_res < 11; dpot_res++)
		{
			send_res_dpot(dpot_res, ADD_400_OHM);
			//wait_com_uart();
			//pvolts = make_meas_adc(pvolts, MEAS_NUM, SAMPL_FRQ);
//			pfft_res = (is_half_volts) ? make_fft_abs(pfft_res, pvolts)
//									   : make_fft_abs(pfft_res, pvolts + (MEAS_NUM << 1));
			//pfft_res = make_fft_abs(pfft_res, pvolts_first_half);
			sprintf(tx_buf, "%d, %d, %d, %d\r\n", _inject[0], _inject[1], _inject[2], _inject[3]);
			tx_str(tx_buf);
			//sprintf(tx_buf, "dpot_res = %d\r\n", dpot_res);
			//tx_str(tx_buf);
//			for (u16 i = 0; i < MEAS_NUM / 2; i++)
//			{
//				sprintf(tx_buf, "%d\r\n", pvolts[i]);
//				tx_str(tx_buf);
//			}
		}
	}
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
