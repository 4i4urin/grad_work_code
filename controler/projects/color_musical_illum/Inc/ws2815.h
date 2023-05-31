/*
 * ws2815.h
 *
 *  Created on: May 12 2023 г.
 *      Author: shishel
 */

#ifndef WS2815_H_
#define WS2815_H_


#define BIT_IS_SET(reg, bit) ((reg & (1<<bit)) != 0)

// Calculate ws2815 frequency
#define PERIOD_WS2815       0.0000014  // 200ns
#define FREQ_TIM2			64000000   // 64 MEGHz

#define PSC_WS2815 		 	(u32)(MCU_FREQ / FREQ_TIM2)
#define ARR_WS2815			(u32)(PERIOD_WS2815 * FREQ_TIM2)


#define LOW 				 (u32)(ARR_WS2815 / 3)  // ws2815 - 0  0,4 us
#define HIGH                 (u32)(ARR_WS2815 * 2 / 3)  // ws2815 - 1  0,8 us


#define NUM_BAND 	4
#define SINGLE_SAMPLE_RATE (SAMPL_FRQ / (FFT_ABS_DATA_NUM * 2))
#define FREQ_LIM_1	500		// band 0 Hz - 250 Hz
#define FREQ_LIM_2 	2000	// band 250 Hz - 2000 Hz
#define FREQ_LIM_3 	6000	// band 250 Hz - 2000 Hz
#define FREQ_LIM_4 	12000 	// band 6 kHz - 12 kHz
//#define BAND_0  (SINGLE_SAMPLE_RATE * 250) // band 0 Hz - 250 Hz
//#define BAND_1	(SINGLE_SAMPLE_RATE * 2000) // band 250 Hz - 2000 Hz
//#define BAND_2  (SINGLE_SAMPLE_RATE * 6000) // band 2 kHz - 6 kHz
//#define BAND_3  (SINGLE_SAMPLE_RATE * 12000) // band 6 kHz - 12 kHz


void one_colore_running(u8 Rpixel, u8 Gpixel, u8 Bpixel, u8 bright);
void one_colore_full_led(u8 Rpixel, u8 Gpixel, u8 Bpixel, u8 brigh);

void freq_led_mode(u16* pfft_abs, char* tx_buf);


void ws2815_buff_clear(void);
u8 ws2815_set(u8 posX, u8 Rpixel, u8 Gpixel, u8 Bpixel, u8 bright);
u8* get_buf_led_pointer(void);
u8 ws2815_is_ready(void);
void ws2815_send(void);




#endif /* WS2815_H_ */
