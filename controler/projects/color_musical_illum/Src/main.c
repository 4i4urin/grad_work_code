#include "project_def.h"
#include "stm32f1xx.h"


#define ON_PB1() GPIOB->BSRR = GPIO_BSRR_BS1
#define OFF_PB1() GPIOB->BSRR = GPIO_BSRR_BR1

void delay(u32 del_val);

void init_gpio(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	GPIOB->CRL |= GPIO_CRL_MODE1;
	GPIOB->CRL &= ~(GPIO_CRL_CNF1);
}

int main(void)
{
	init_gpio();

	while (1)
	{
		ON_PB1();
		delay(100000);
		OFF_PB1();
		delay(100000);
	}
}



// Задержка по попугаям
void delay(u32 del_val)
{
	while (del_val)
		del_val -= 1;
}
