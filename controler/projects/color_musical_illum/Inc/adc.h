/*
 * adc.h
 *
 *  Created on: 5 апр. 2023 г.
 *      Author: Саня
 */

#ifndef ADC_H_
#define ADC_H_


#define START_TIM4()	TIM4->CR1 |= TIM_CR1_CEN
#define STOP_TIM4() 	TIM4->CR1 &= ~(TIM_CR1_CEN)


#define CALIB_MEAS_NUM 		20
#define LOWER_AMPL_LIMIT 	45
#define HIGHER_AMPL_LIMIT 	210


u8* make_meas_adc(u8* parr, const u16 size, const u16 kHz);
void stop_adc_meas(void);
void start_adc_meas(void);


#endif /* ADC_H_ */
