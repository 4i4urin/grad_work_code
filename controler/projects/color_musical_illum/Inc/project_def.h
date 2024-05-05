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


#define MCU_FREQ		64000000 // 64 MHz


#define USE_BRIGHT 1
#define NUM_ILUM_MODE 3


#define MEAS_POW2     12
#define MEAS_FULL_NUM (1 << MEAS_POW2) // Number of ADC measurements
#define MEAS_HALF_NUM (MEAS_FULL_NUM >> 1) // for ping-pong

// for ping-pong buffer
#define FFT_DATA_POW2 (MEAS_POW2 - 1)
#define FFT_DATA_NUM  (1 << FFT_DATA_POW2)
#define FFT_ABS_DATA_NUM (FFT_DATA_NUM >> 1)

#define SAMPL_FRQ 	 24000 //Hz



#define DELAY_LEN 50
#define MAX_LED_COUNT 100
#define BUF_LED_SIZE DELAY_LEN + MAX_LED_COUNT * 24 + 1



#define MAX_TX_STR   128


#define ON_CTRL_LED()  	GPIOB->BSRR = GPIO_BSRR_BS1
#define OFF_CTRL_LED() 	GPIOB->BSRR = GPIO_BSRR_BR1
#define SWAP_CTRL_LED()	GPIOB->ODR ^= GPIO_ODR_ODR1

#define ON_PB4()	GPIOB->BSRR = GPIO_BSRR_BS4
#define OFF_PB4()	GPIOB->BSRR = GPIO_BSRR_BR4

#define ON_LED_POWER() 	GPIOB->BSRR = GPIO_BSRR_BS7
#define OFF_LED_POWER() GPIOB->BSRR = GPIO_BSRR_BR7


#define DISABLE_NVIC() 	NVIC_DisableIRQ(TIM2_IRQn); \
						NVIC_DisableIRQ(DMA1_Channel5_IRQn); \
						NVIC_DisableIRQ(EXTI9_5_IRQn); \
						NVIC_DisableIRQ(EXTI15_10_IRQn); \
						NVIC_DisableIRQ(TIM4_IRQn); \
						NVIC_DisableIRQ(TIM3_IRQn); \
						NVIC_DisableIRQ(USART3_IRQn);

#define ENABLE_NVIC()	NVIC_EnableIRQ(TIM2_IRQn); \
						NVIC_EnableIRQ(DMA1_Channel5_IRQn); \
						NVIC_EnableIRQ(EXTI9_5_IRQn); \
						NVIC_EnableIRQ(EXTI15_10_IRQn); \
						NVIC_EnableIRQ(TIM4_IRQn); \
						NVIC_EnableIRQ(TIM3_IRQn); \
						NVIC_EnableIRQ(USART3_IRQn);


// GOERTZEL
#define FREQ_NUM 7



#define MCSEC_IN_SEC 	1000000

#define I_RED 	 0
#define I_GREEN  1
#define I_BLUE 	 2
#define I_BRIGHT 3



#endif /* PROJECT_DEF_H_ */
