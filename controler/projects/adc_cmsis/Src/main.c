#include <main.h>
/*
 * TODO:
 *
 * 1. add DMA on channel 0 ADC1
 * ---2. add output to uart
 * 3. add ADC for pots
 * 4. create protected while
 * 5. create timer for delays and protected delays
 */

/*
 * По теореме котельникова:
 * Если хотим различать частоты до 20кГц
 * должны опрашивать с частотой 40кГц
 */

u8 com_receive;
//u8 rx_buf[MAX_STR_SIZE];
u8 make_adc;

/**
  * @brief  Передача строки по USART2 без DMA
  * @param  *str - указатель на строку
  * @retval None
  */
void tx_str(char *str)
{
	u16 i;								//добавляем символ конца строки

	for (i = 0; i < strlen((char*)str); i++)
	{
		USART2->DR = str[i];								//передаём байт данных
		while ((USART2->SR & USART_SR_TC) == 0) {};			//ждём окончания передачи
	}
}

/**
  * @brief  Передача символа по USART2 без DMA
  * @param  ch - символ для передачи
  * @retval None
  */
void tx_char(char ch)
{
	USART2->DR = ch;
	while ((USART2->SR & USART_SR_TC) == 0) {};
}

/**
  * @brief  Считывание значения ацп
  * @param  None
  * @retval Значение АЦП
  */
u16 read_adc(void)
{
//	ADC1->CR2 |= ADC_CR2_SWSTART;
//	while ( !(ADC1->SR & ADC_SR_EOC) ) // wait finish of conversion
//		;
	// because of continuous mode
	return ADC1->DR;
}


/**
  * @brief  Обработчик прерывания по UART
  * @param  None
  * @retval None
  * cannot copy paste to terminal
  * space symbol is terminator
  */
void USART2_IRQHandler(void)
{
	if ((USART2->SR & USART_SR_RXNE)!=0)		//Прерывание по приёму данных?
	{
		//u8 pos = strlen((char*)rx_buf);			//Вычисляем позицию свободной ячейки
		u8 ch = 0;
		//rx_buf[pos] = USART2->DR; 			//Считываем содержимое регистра данных
		//tx_char(rx_buf[pos]);
		ch = USART2->DR;
		tx_char(ch);

		if (isspace(ch))							//Если это символ конца строки
		{
//			if (rx_buf[pos] == '\r')
//			{
//				rx_buf[pos + 1] = '\n';
//				tx_char('\n');
//			}
			com_receive = 1;					//- выставляем флаг приёма строки
			return;								//- и выходим
		}
	}
}

void TIM4_IRQHandler()
{
	TIM4->SR &= ~TIM_SR_UIF; // drop update flag
	make_adc = 1;
}

void start_tim4_khz(u16 kHz)
{
	TIM4->ARR = TIM4_FREQ / (kHz * 1000); // set freq
	START_TIM4();
}

void spi1_write(u8 data)
{
	SPI1->DR = data;
	while ( !(SPI1->SR & SPI_SR_TXE) ) { };
}


int main(void)
{
	init_clk();
	init_adc();
	init_usart2();
	init_tim4();
	init_spi();

	u16 some_arr[ARR_SIZE] = { 0 };
	u16* volts = some_arr;
	make_adc = 0;

	char tx_buf[MAX_STR_SIZE] = { 0 };
	//memset(rx_buf, 0, MAX_STR_SIZE);

	com_receive = 0;

    while (1)
    {

    	tx_str("Start_measrumrnts\r\n");
    	volts = make_meas(volts, ARR_SIZE, 40);
    	tx_str("Finish_mesrument\r\n");
    	while ( !com_receive) {};
    	com_receive = 0;
    	tx_char('\r');
    	for (u16 i = 0; i < ARR_SIZE; i++)
    	{
    		sprintf(tx_buf, "%d\r\n", volts[i]);
    		tx_str(tx_buf);
    	}
    }
}

u16* make_meas(u16* parr, u16 size, u16 kHz)
{
	start_tim4_khz(kHz);
	spi1_write(0x01);
	for(u16 i = 0; i < size; i++)
	{
		while ( !make_adc) {};
		parr[i] = read_adc();
		if (i == size / 2)
			spi1_write(0xFA);
		make_adc = 0;
	}
	STOP_TIM4();
	return parr;
}

/**
  * @brief  Задержка по попугаям
  * @param  del_val значение задержки в попугаях
  * @retval None
  */
void delay(u32 del_val)
{
	while (del_val)
		del_val -= 1;
}
