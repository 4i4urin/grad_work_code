/*
 * led_and_buttons.c
 *
 *  Created on: 5 апр. 2023 г.
 *      Author: shishel
 */
#include "color_musical_illum.h"

#define NOISE_DELAY 	50

u8 _is_power_press = 0;
u8 _is_mode_press = 0;

static void set_device_mode(void);

// OFF/ON ctrl led
void TIM3_IRQHandler(void)
{
	if (TIM3->SR & TIM_SR_UIF)
	{
		SWAP_CTRL_LED();
		TIM3->SR &= ~(TIM_SR_UIF);
	}
}


// PB9 ON/OFF button
void EXTI9_5_IRQHandler(void)
{
	if (EXTI->PR & EXTI_PR_PR9) // if PB9
	{
		EXTI->PR |= EXTI_PR_PR9; // drop flag
		delay(NOISE_DELAY);
		if (GPIOB->IDR & GPIO_IDR_IDR9) // if PB9 == 1
			return;

		_is_power_press = 1;
	}
	set_device_mode();
}


// PB15 change mode button
void EXTI15_10_IRQHandler(void)
{
	if (EXTI->PR & EXTI_PR_PR15) // if PB15
	{
		EXTI->PR |= EXTI_PR_PR15; // drop flag
		delay(NOISE_DELAY);
		if (GPIOB->IDR & GPIO_IDR_IDR15) // if PB15 == 1
			return;

		_is_mode_press = 1;
	}
	set_device_mode();
}


void set_device_mode(void)
{
	//delay(1000);
	_is_mode_press  = (GPIOB->IDR & GPIO_IDR_IDR15) ? 0 : 1;
	_is_power_press = (GPIOB->IDR & GPIO_IDR_IDR9)  ? 0 : 1;

	if (_is_mode_press && _is_power_press)
		set_dev_state(E_DEV_CALIB);
	else if (_is_mode_press)
		set_dev_state(E_DEV_WORK);
	else if (_is_power_press)
		set_dev_state(E_DEV_SLEEP);


}

