/*
 * led_mode.h
 *
 *  Created on: 31 may 2023 г.
 *      Author: shishel
 */

#ifndef LED_MODE_H_
#define LED_MODE_H_

#define NUM_BAND 	4
#define SINGLE_SAMPLE_RATE (SAMPL_FRQ / (FFT_ABS_DATA_NUM * 2))
#define FREQ_LIM_1	500		// band 0 Hz - 250 Hz
#define FREQ_LIM_2 	2000	// band 250 Hz - 2000 Hz
#define FREQ_LIM_3 	6000	// band 250 Hz - 2000 Hz
#define FREQ_LIM_4 	12000 	// band 6 kHz - 12 kHz

#define ARR_FREQ_LIM_1 FREQ_LIM_1 / SINGLE_SAMPLE_RATE
#define ARR_FREQ_LIM_2 FREQ_LIM_2 / SINGLE_SAMPLE_RATE
#define ARR_FREQ_LIM_3 FREQ_LIM_3 / SINGLE_SAMPLE_RATE
#define ARR_FREQ_LIM_4 FREQ_LIM_4 / SINGLE_SAMPLE_RATE


void one_colore_running(u8 Rpixel, u8 Gpixel, u8 Bpixel, u8 bright);
void one_colore_full_led(u8* pctrl);
void freq_led_mode(u16* pfft_abs, u8* preg);

#endif /* LED_MODE_H_ */
