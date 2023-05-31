#include "main.h"

#include "color_musical_illum.h"
#include "inits.h"


void sleep(void);


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
			while (get_dev_state() != E_DEV_WORK) { }
			break;

		case E_DEV_SLEEP:
			sleep();
			break;

		default:
			break;
		}
	}
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
	char* tx_buf[100];
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
