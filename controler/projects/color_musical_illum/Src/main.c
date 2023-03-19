#include "color_musical_illum.h"
#include "inits.h"
#include "digital_pot.h"


int main(void)
{
	init_device();

	while (1)
	{
		ON_PB1();
		send_dpot(0xFF);
		delay(1000000);
		OFF_PB1();
		send_dpot(0x01);
		delay(1000000);
	}
}


// Задержка по попугаям
void delay(u32 del_val)
{
	while (del_val)
		del_val -= 1;
}
