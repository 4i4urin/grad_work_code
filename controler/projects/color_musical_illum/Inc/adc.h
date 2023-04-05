/*
 * adc.h
 *
 *  Created on: 5 апр. 2023 г.
 *      Author: Саня
 */

#ifndef ADC_H_
#define ADC_H_


#define TIM4_FREQ 		1000000 // 1 MHz
#define TIM4_PSC 		(MCU_FREQ / TIM4_FREQ)


#define START_TIM4()	TIM4->CR1 |= TIM_CR1_CEN
#define STOP_TIM4() 	TIM4->CR1 &= ~(TIM_CR1_CEN)


u8* make_meas_adc(u8* parr, const u16 size, const u16 kHz);


#endif /* ADC_H_ */
