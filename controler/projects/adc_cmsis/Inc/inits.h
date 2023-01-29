/*
 * inits.h
 *
 *  Created on: Jan 28, 2023
 *      Author: Саня
 */

#ifndef INITS_H_
#define INITS_H_

#include "main.h"

#define DEL_ADC 	100
#define TIM4_PSC 	MCU_FREQ / TIM4_FREQ

void init_adc(void);
void init_clk(void);
void init_usart2(void);
void init_tim4(void);



#endif /* INITS_H_ */
