/*
 * inits.h
 *
 *  Created on: Mar 20, 2023
 *      Author: shishel
 */

#ifndef INITS_H_
#define INITS_H_


#include "color_musical_illum.h"


#define MCU_FREQ		64000000 // 64 MHz


#define DEL_ADC 		10000
#define TIM4_FREQ 		1000000 // 1 MHz
#define TIM4_PSC 		(MCU_FREQ / TIM4_FREQ)


#define TIM3_FREQ		10000 // 10 kHz
#define TIM3_PSC 		(MCU_FREQ / TIM3_FREQ) // tic in 0,1 ms


void init_device(void);


#endif /* INITS_H_ */
