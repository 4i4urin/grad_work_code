/*
 * led_mode.c
 *
 *  Created on: 31 may 2023 г.
 *      Author: shishel
 */
#include "main.h"
#include "led_mode.h"
#include "ws2815.h"
#include "usart.h"


static u16 sum_arr(u16* pstart, u16 size);
static u16 init_freq_band(t_freq_led* pfreq_band, u16* pfft_abs);
static u8 calc_tail_len(u8 bright);


void one_colore_full_led(u8* pctrl)
{
	for (register u16 i = 0; i < LED_COUNT; i++)
		ws2815_set_control(i, pctrl);
	ws2815_send_dma();
}


void one_colore_running(u8* pctrl)
{
	u8 Rpixel = pctrl[I_RED];  u8 Gpixel = pctrl[I_GREEN];
	u8 Bpixel = pctrl[I_BLUE]; u8 bright = pctrl[I_BRIGHT];

	u8 tail_len = calc_tail_len(bright);
	if (Rpixel > Gpixel)
		tail_len +=	(Rpixel > Bpixel) ? calc_tail_len(Rpixel) : calc_tail_len(Bpixel);
	else
		tail_len +=	(Gpixel > Bpixel) ?	calc_tail_len(Gpixel) : calc_tail_len(Bpixel);

	for (u8 i = 0; i < LED_COUNT + tail_len; i++) {

		ws2815_set(i, Rpixel, Gpixel, Bpixel, bright);
		u8 Rpixel_tail = Rpixel, Gpixel_tail = Gpixel,
				Bpixel_tail = Bpixel, bright_tail = bright;
		for (u8 taile = i - 1;
				taile >= 0	&& (Rpixel_tail || Gpixel_tail || Bpixel_tail || bright_tail);
				taile--) {

			Rpixel_tail >>= 1;
			Gpixel_tail >>= 1;
			Bpixel_tail >>= 1;
			Rpixel_tail |= (Rpixel != 0) ? (bright_tail << 3) : 0;
			Gpixel_tail |= (Gpixel != 0) ? (bright_tail << 3) : 0;
			Bpixel_tail |= (Bpixel != 0) ? (bright_tail << 3) : 0;
			bright_tail >>= 1;
			ws2815_set(taile, Rpixel_tail, Gpixel_tail, Bpixel_tail,
					bright_tail);
		}
		ws2815_send_dma();
		delay(10000);
	}
	ws2815_buff_clear();
}


u8 calc_tail_len(u8 fourbin) {
	for (u8 offset = 3; offset > 0; offset--) {
		if ((fourbin >> offset) == 1)
			return offset + 1;
	}
	return fourbin;
}


void freq_led_mode(u16* pfft_abs, u8* pctrl)
{
	t_freq_led freq_band[NUM_BAND] = { 0 };
	u8 turnon_border = init_freq_band(freq_band, pfft_abs) / LED_COUNT;
	u8 led_pos = 0;
	u8 led_pos_start = 0;
	for (u8 i = 0; i < NUM_BAND; i++)
	{
		u8 counts_per_LED = freq_band[i].size_freq / freq_band[i].num_led;
		for ( ; led_pos < freq_band[i].num_led + led_pos_start; led_pos++)
		{
			if (sum_arr(freq_band[i].p_freq_arr, counts_per_LED) > turnon_border)
				ws2815_set_control(led_pos, pctrl);
			else
				ws2815_set(led_pos, 0, 0, 0, 0);

			freq_band[i].p_freq_arr += counts_per_LED;
		}
		led_pos_start = led_pos;
	}
	ws2815_send_dma();
}


void freq_led_linear_mode(u16* pfft_abs)
{
	u16 led_sum = (u16) FFT_ABS_DATA_NUM / LED_COUNT;
	u16 sum_abs = 0;

	for (register u16 i = 0; i < LED_COUNT; i++)
	{
		sum_abs = sum_arr(pfft_abs + (i * led_sum), led_sum);
//		sprintf(tx_buf, "%d\r\n", sum_abs);
//		tx_str(tx_buf);
		if (sum_abs > 25)
			ws2815_set(i, 2, 3, 8, 8);
		else
			ws2815_set(i, 0, 0, 0, 0);
	}
	ws2815_send_dma();
}


u16 init_freq_band(t_freq_led* pfreq_band, u16* pfft_abs)
{
	u16 abs_sum = 0;
	u16 band_width[NUM_BAND] = {ARR_FREQ_LIM_1, ARR_FREQ_LIM_2,
								ARR_FREQ_LIM_3, ARR_FREQ_LIM_4};

	band_width[NUM_BAND - 1] = (band_width[NUM_BAND - 1] > FFT_ABS_DATA_NUM)
							 ? FFT_ABS_DATA_NUM : band_width[NUM_BAND - 1];

	u8 num_led_in_band = LED_COUNT / NUM_BAND;
	u8 num_led_mod = LED_COUNT % NUM_BAND;

	pfreq_band[0].num_led = num_led_in_band;
	pfreq_band[0].p_freq_arr = pfft_abs;
	pfreq_band[0].size_freq = band_width[0];

	abs_sum += sum_arr(pfreq_band[0].p_freq_arr, pfreq_band[0].size_freq);

	for (u8 i = 1; i < NUM_BAND; i++)
	{
		pfreq_band[i].num_led = (i == 1)
							  ? num_led_in_band + num_led_mod
							  : num_led_in_band;

		pfreq_band[i].p_freq_arr = pfft_abs + pfreq_band[i - 1].size_freq;
		pfreq_band[i].size_freq = band_width[i] - band_width[i - 1];

		abs_sum += sum_arr(pfreq_band[i].p_freq_arr, pfreq_band[i].size_freq);
	}
	return abs_sum;
}


u16 sum_arr(u16* pstart, u16 size)
{
	u16 sum = 0;
	for (u16 i = 0; i < size; i++)
		sum += pstart[i];
	return sum;
}
