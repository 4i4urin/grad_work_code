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

#define ON_PA6()		GPIOA->BSRR = GPIO_BSRR_BS6;
#define OFF_PA6()		GPIOA->BSRR = GPIO_BSRR_BR6;

void delay(u32 del_val);
u16 read_adc(void);
void tx_str(char *str);
void tx_char(char ch);
void start_tim4_khz(u16 kHz);
u16* make_meas_adc(u16* parr, u16 size, u16 khz);

void spi1_write(u16* pdata);
void send_dpot(u8 res_byte);
u8 reverse(u8 byte);

void wait_com_uart(void);

#pragma pack(push, 1)
// spi transmit data strct
typedef enum _e_dpot_comm
{
	E_DPOT_COM_NONE = 0x00,
	E_DPOT_COM_SHUTD = 0x01,
	E_DPOT_COM_WRITE = 0x02,
	E_DPOT_COM_NONE_2 = 0x03
} e_dpot_comm;

typedef struct _t_dpot_hdr
{
	u8 		 	    db_1 : 2; // don't care bits
	e_dpot_comm 	comm : 2; // command bits
	u8 	  			db_2 : 2; // don't care bits
	u8  ch_select : 2;// channel select
} t_dpot_hdr;

typedef struct _t_dpot_send
{
	t_dpot_hdr  hdr;
	u8 			data;
} t_dpot_send;

#pragma pack(pop)

#endif /* MAIN_H_ */
