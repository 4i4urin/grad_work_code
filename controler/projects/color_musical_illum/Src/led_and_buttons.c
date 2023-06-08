/*
 * led_and_buttons.c
 *
 *  Created on: 5 апр. 2023 г.
 *      Author: shishel
 */
#include "main.h"
#include "color_musical_illum.h"

#define NOISE_DELAY 	50

u8 _is_power_press = 0;
u8 _is_mode_press = 0;
u8 _inject[4] = { 0 };


#if USE_BRIGHT
	u8 _adc_offset = 8;
#else
	u8 _adc_offset = 4;
#endif

static void set_device_mode(e_device_state new_state);
static void change_illum_mode(void);

// OFF/ON ctrl led
// read inject channels every 5 ms
void TIM3_IRQHandler(void)
{
	if (TIM3->SR & TIM_SR_UIF)
	{
		static u32 click = 0;
		static u16 power_press = 0;
		static u16 mode_press = 0;
		click += 1;
//		if (click % 100 == 0) // every 0,5 sec
//			SWAP_CTRL_LED();

		_inject[I_RED]   = ADC1->JDR1 >> _adc_offset;
		_inject[I_GREEN] = ADC1->JDR2 >> _adc_offset;
		_inject[I_BLUE]  = ADC1->JDR3 >> _adc_offset;
		_inject[I_BRIGHT]= ADC1->JDR4 >> _adc_offset;

		mode_press = _is_mode_press ? mode_press + 1 : 0;
		power_press = _is_power_press ? power_press + 1 : 0;

		if (_is_mode_press && _is_power_press)
		{
			if ((power_press + mode_press) > 20)
			{
				power_press = 0;
				mode_press= 0;
				set_device_mode(E_DEV_CALIB);
				_is_mode_press = 0;
				_is_power_press = 0;
			}
			else
			{
				TIM3->SR &= ~(TIM_SR_UIF);
				return;
			}
		}

		if (get_dev_state() == E_DEV_CALIB)
		{
			TIM3->SR &= ~(TIM_SR_UIF);
			return;
		}

		if (mode_press > 4)
		{
			mode_press = 0;
			change_illum_mode();
			_is_mode_press = 0;
		}
		if (power_press > 4)
		{
			power_press = 0;
			set_device_mode(E_DEV_WORK);
			_is_power_press = 0;
		}

		TIM3->SR &= ~(TIM_SR_UIF);
	}
}


// PB9 ON/OFF button
void EXTI9_5_IRQHandler(void)
{
	if (EXTI->PR & EXTI_PR_PR9) // if PB9
	{
		delay(NOISE_DELAY);
		if (GPIOB->IDR & GPIO_IDR_IDR9) // if PB9 == 1
		{
			EXTI->PR |= EXTI_PR_PR9; // drop flag
			return;
		}

		_is_power_press = (_is_power_press) ? 0 : 1;
		EXTI->PR |= EXTI_PR_PR9; // drop flag
	}
}


// PB15 change mode button
void EXTI15_10_IRQHandler(void)
{
	if (EXTI->PR & EXTI_PR_PR15) // if PB15
	{
		delay(NOISE_DELAY * 10);
		if (GPIOB->IDR & GPIO_IDR_IDR15) // if PB15 == 1
		{
			EXTI->PR |= EXTI_PR_PR15; // drop flag
			return;
		}

		_is_mode_press = (_is_mode_press) ? 0 : 1;
		EXTI->PR |= EXTI_PR_PR15; // drop flag
	}
}


void set_device_mode(e_device_state new_state)
{
	_is_mode_press  = (GPIOB->IDR & GPIO_IDR_IDR15) ? 0 : 1;
	_is_power_press = (GPIOB->IDR & GPIO_IDR_IDR9)  ? 0 : 1;

	switch (new_state)
	{
	case E_DEV_WORK:
	case E_DEV_SLEEP:
		if (get_dev_state() == E_DEV_CALIB)
			return;

		if (get_dev_state() == E_DEV_SLEEP)
			new_state = E_DEV_WORK;
		else if (get_dev_state() == E_DEV_WORK)
			new_state = E_DEV_SLEEP;

		if (_is_power_press)
			set_dev_state(new_state);
		break;

	case E_DEV_CALIB:
		if (_is_mode_press && _is_power_press)
		{
			if (get_dev_state() == E_DEV_CALIB)
				set_dev_state(E_DEV_SLEEP);
			else
				set_dev_state(E_DEV_CALIB);
		}
		break;
	}

}

void change_illum_mode(void)
{
	u8 mode = get_ilum_mode();
	set_ilum_mode(mode + 1);
}


inline u8* get_pctrl_panel(void)
{
	return _inject;
}

inline u8 get_power_press(void)
{
	return _is_power_press;
}

inline u8 get_mode_press(void)
{
	return _is_mode_press;
}

inline void reset_mode_button(void)
{
	_is_mode_press = 0;
}

inline void reset_power_button(void)
{
	_is_power_press = 0;
}



