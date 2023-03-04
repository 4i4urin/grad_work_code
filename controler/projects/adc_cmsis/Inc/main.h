/*
 * main.h
 *
 *  Created on: Jan 28, 2023
 *      Author: shishel
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "stm32f1xx.h"
#include "my_types.h"

#include "fft_table.h"
#include "fft.h"
#include "inits.h"

#define VDRAIN			3300 // 3.3 V
#define DEL_VAL			2000
#define MAX_STR_SIZE	256

#define START_TIM4()	TIM4->CR1 |= TIM_CR1_CEN
#define STOP_TIM4() 	TIM4->CR1 &= ~(TIM_CR1_CEN)

#define START_TIM3()	TIM3->CR1 |= TIM_CR1_CEN
#define STOP_TIM3() 	TIM3->CR1 &= ~(TIM_CR1_CEN)

u16 read_adc(void);
void tx_str(const char *str);
void tx_char(const char ch);
void start_tim4_khz(u16 kHz);
u8* make_meas_adc(u8* parr, u16 size, u16 khz);

void spi1_write(u16* pdata);
void send_dpot(u8 res_byte);
u8 reverse_8(u8 byte);

void wait_com_uart(void);

u16 take_tim3_val(void);
u32 meas_sqrt_time(const t_complex* pcplx_arr, u16 (*pfsqrt)(u32));


#endif /* MAIN_H_ */
