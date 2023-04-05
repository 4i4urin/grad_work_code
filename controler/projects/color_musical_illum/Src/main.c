#include "color_musical_illum.h"
#include "inits.h"
#include "digital_pot.h"
#include "adc.h"
#include "usart.h"
#include "fft.h"


u8 volts[MEAS_NUM] = { 0 };
u16 fft_abs[MEAS_NUM << 1] = { 0 };


int main(void)
{
	init_device();
	delay(1000000);
	send_res_dpot(20);
	char tx_buf[MAX_TX_STR] = { 0 };
	u8* pvolts = volts;
	u16* pfft_res = fft_abs;

	while (1)
	{

		ON_PB1();
		delay(1000000);
		OFF_PB1();
		delay(1000000);
		for (u8 dpot_res = 10; dpot_res < 100; dpot_res += 10)
		{
			send_res_dpot(dpot_res);
			wait_com_uart();
			pvolts = make_meas_adc(pvolts, MEAS_NUM, SAMPL_FRQ);
			pfft_res = make_fft_abs(pfft_res, pvolts);
			sprintf(tx_buf, "dpot_res = %d\r\n", dpot_res);
			tx_str(tx_buf);
			for (u16 i = 0; i < MEAS_NUM / 2; i++)
			{
				sprintf(tx_buf, "%d\r\n", pvolts[i]);
				tx_str(tx_buf);
			}
		}
	}
}


// Задержка по попугаям
void delay(u32 del_val)
{
	while (del_val)
		del_val -= 1;
}
