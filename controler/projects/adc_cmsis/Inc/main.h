/*
 * main.h
 *
 *  Created on: Jan 28, 2023
 *      Author: shishel
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "stm32f1xx.h"
#include "inits.h"

#define u8 		uint8_t
#define u16 	uint16_t
#define u32		uint32_t

#define s8 		int8_t
#define s16		int16_t
#define s32		int32_t

#define ARR_SIZE 		4096
#define VDRAIN			3300
#define DEL_VAL			2000
#define MAX_STR_SIZE	128

#define TIM4_FREQ 		1000000 // 1 MHz
#define MCU_FREQ		64000000 // 64 MHz

#define START_TIM4()	TIM4->CR1 |= TIM_CR1_CEN;
#define STOP_TIM4() 	TIM4->CR1 &= ~(TIM_CR1_CEN)

void delay(u32 del_val);
u16 read_adc(void);
void tx_str(char *str);
void tx_char(char ch);
void start_tim4_khz(u16 kHz);
u16* make_meas(u16* parr, u16 size, u16 khz);


#endif /* MAIN_H_ */
