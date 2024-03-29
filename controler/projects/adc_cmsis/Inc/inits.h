/*
 * inits.h
 *
 *  Created on: Jan 28, 2023
 *      Author: shishel
 */

#ifndef INITS_H_
#define INITS_H_


#include "stm32f1xx.h"
#include "my_types.h"


#define MCU_FREQ		64000000 // 64 MHz


#define DEL_ADC 		100
#define TIM4_FREQ 		1000000 // 1 MHz
#define TIM4_PSC 		(MCU_FREQ / TIM4_FREQ)


#define TIM3_FREQ		10000 // 10 kHz
#define TIM3_PSC 		(MCU_FREQ / TIM3_FREQ) // tic in 0,1 ms


#define ON_PA6()		GPIOA->BSRR = GPIO_BSRR_BS6
#define OFF_PA6()		GPIOA->BSRR = GPIO_BSRR_BR6


void init_device(void);


#endif /* INITS_H_ */
