/*
 * main.h
 *
 *  Created on: Jan 28, 2023
 *      Author: shishel
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>
#include "stm32f1xx.h"
#include "inits.h"

#define u8 		uint8_t
#define u16 	uint16_t
#define u32		uint32_t

#define s8 		int8_t
#define s16		int16_t
#define s32		int32_t

#define ARR_SIZE 	1024
#define VDRAIN		3300
#define DEL_VAL		2000

void delay(u32 del_val);
u16 read_adc(void);


#endif /* MAIN_H_ */
