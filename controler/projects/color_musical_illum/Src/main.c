#include "main.h"

#include "color_musical_illum.h"
#include "inits.h"
#include "led_mode.h"
#include "ws2815.h"


static void sleep(void);
static void calib_led(void);

char tx_buf[100] = { 0 };
e_device_state _dev_state = E_DEV_WORK;


int main(void)
{
	init_device();
	delay(1000000);

	set_dev_state(E_DEV_WORK);

	while (1)
	{
		switch (get_dev_state())
		{
		case E_DEV_WORK:
			coloor_music();
			break;

		case E_DEV_CALIB:
			// change number of leds
			reset_mode_button();
			reset_power_button();
			while (get_dev_state() != E_DEV_SLEEP)
				calib_led();
			break;

		case E_DEV_SLEEP:
			sleep();
			break;

		default:
			break;
		}
	}
}


void calib_led(void)
{

	if ( get_mode_press() )
	{
		delay(10000);
		if ( get_power_press() )
		{
			tx_str("SHIIIISH\r\n");
			set_dev_state(E_DEV_SLEEP);
			return;
		}
		u8 num_led = get_num_led();
		set_num_led(num_led + 1);
		reset_mode_button();
		sprintf(tx_buf, "ADD %d\r\n", get_num_led());
		tx_str(tx_buf);
	}

	if ( get_power_press() )
	{
		if ( get_mode_press() )
		{
			tx_str("2_SHIIIISH\r\n");
			set_dev_state(E_DEV_SLEEP);
			return;
		}
		u8 num_led = get_num_led();
		set_num_led(num_led - 1);
		reset_power_button();
		sprintf(tx_buf, "DELETE %d\r\n", get_num_led());
		tx_str(tx_buf);
		clear_led();
	}
	if (ws2815_is_ready())
		one_colore_full_led(get_pctrl_panel());
}


void sleep(void)
{
	//disinit_device();
	OFF_LED_POWER();
	while (get_dev_state() == E_DEV_SLEEP) { };
	ON_LED_POWER();
	//init_device();
	delay(1000000);
}



void set_dev_state(e_device_state state)
{
	switch (state)
	{
	case E_DEV_WORK:
	case E_DEV_SLEEP:
	case E_DEV_CALIB:
		break;

	default:
		return;
	}
	_dev_state = state;
	sprintf(tx_buf, "STATE = %d\r\n", state);
	tx_str(tx_buf);
}


inline e_device_state get_dev_state(void)
{
	return _dev_state;
}

// Задержка по попугаям
void delay(u32 del_val)
{
	while (del_val)
		del_val -= 1;
}
