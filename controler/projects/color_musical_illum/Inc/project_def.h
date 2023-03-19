/*
 * project_def.h
 *
 *  Created on: Mar 20, 2023
 *      Author: shishel
 */

#ifndef PROJECT_DEF_H_
#define PROJECT_DEF_H_


#include <stdint.h>


#define u8 		uint8_t
#define u16 	uint16_t
#define u32		uint32_t

#define s8 		int8_t
#define s16		int16_t
#define s32		int32_t


#define BITS_U16 	16
#define BITS_U8 	8


#define TRUE 		1
#define FALSE 		0


#define ON_PB1()  GPIOB->BSRR = GPIO_BSRR_BS1
#define OFF_PB1() GPIOB->BSRR = GPIO_BSRR_BR1


#define ON_PB4()		GPIOB->BSRR = GPIO_BSRR_BS4
#define OFF_PB4()		GPIOB->BSRR = GPIO_BSRR_BR4


#endif /* PROJECT_DEF_H_ */
