/*
 * ws2815.h
 *
 *  Created on: May 12 2023 г.
 *      Author: shishel
 */

#ifndef WS2815_H_
#define WS2815_H_


#define DELAY_LEN 50
#define LED_COUNT 50
#define BUF_LED_SIZE DELAY_LEN + LED_COUNT * 24 + 1


#define BIT_IS_SET(reg, bit) ((reg & (1<<bit)) != 0)

// Calculate ws2812b frequency
#define FREQ_F103            64000000   // 64 MEGHz
#define PERIOD_WS2812B       0.0000014  // 200ns
#define FREQ_TIM2			 64000000   // 64 MEGHz

#define PSC_WS2812B 		 (u32)(FREQ_F103 / FREQ_TIM2)
#define ARR_WS2812B			 (u32)(PERIOD_WS2812B * FREQ_TIM2)


#define LOW 				 (u32)(ARR_WS2812B / 3)  // ws2812b - 0  0,4 us
#define HIGH                 (u32)(ARR_WS2812B * 2 / 3)  // ws2812b - 1  0,8 us


void one_colore_running(u8 Rpixel, u8 Gpixel, u8 Bpixel, u8 bright);
void one_colore_full_led(u8 Rpixel, u8 Gpixel, u8 Bpixel, u8 brigh);


void ws2812b_buff_clear(void);
u8 ws2812b_set(u8 posX, u8 Rpixel, u8 Gpixel, u8 Bpixel, u8 bright);
u8* get_buf_led_pointer(void);
u8 ws2812b_is_ready(void);


#endif /* WS2815_H_ */
