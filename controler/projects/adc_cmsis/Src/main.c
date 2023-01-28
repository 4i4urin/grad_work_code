#include <main.h>
/*
 * TODO:
 *
 * 1. add DMA on channel 0 ADC1
 * 2. add output to uart
 * 3. add ADC for pots
 * 4. create protected while
 * 5. create timer for delays and protected delays
 */


int main(void)
{
	init_clk();
	init_adc();

	u16 volts[ARR_SIZE] = { 0 };

    while (1)
    {
    	for (u8 i = 0; i < ARR_SIZE; i++)
    	{
    		volts[i] = (read_adc() * VDRAIN) >> 12;;
    		delay(DEL_VAL);
    	}
    }
}

u16 read_adc(void)
{
	ADC1->CR2 |= ADC_CR2_SWSTART;
	while ( !(ADC1->SR & ADC_SR_EOC) ) // wait finish of conversion
		;
	return ADC1->DR;
}

void delay(u32 del_val)
{
	while (del_val)
		del_val -= 1;
}

