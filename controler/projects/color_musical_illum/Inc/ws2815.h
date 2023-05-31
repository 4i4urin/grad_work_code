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


void ws2815_buff_clear(void);
u8 ws2815_set(u8 posX, u8 Rpixel, u8 Gpixel, u8 Bpixel, u8 bright);
u8* get_buf_led_pointer(void);
u8 ws2815_is_ready(void);
void ws2815_send(void);
u8 ws2815_send_dma(void);
u8 ws2815_set_control(u8 posX, u8* pctrl);



#endif /* WS2815_H_ */
