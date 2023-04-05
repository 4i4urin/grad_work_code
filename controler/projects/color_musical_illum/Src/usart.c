/*
 * usarts.c
 *
 *  Created on: Apr 05, 2023
 *      Author: shishel
 */
#include "color_musical_illum.h"
#include "usart.h"

static u8 com_receive = 0;


void tx_str(const char *str)
{
	u16 i = 0;

	for (i = 0; i < strlen((char*)str); i++)
	{
		USART3->DR = str[i];								//передаём байт данных
		while ((USART3->SR & USART_SR_TC) == 0) {};			//ждём окончания передачи
	}
}


void tx_char(const char ch)
{
	USART3->DR = ch;
	while ((USART3->SR & USART_SR_TC) == 0) {};
}


void wait_com_uart(void)
{
	while ( !com_receive) {};
	com_receive = 0;
}


// обработчик прерывания по юарт принимает пробелы и тд
void USART3_IRQHandler(void)
{
	if ((USART3->SR & USART_SR_RXNE)!=0)		//Прерывание по приёму данных?
	{
		//u8 pos = strlen((char*)rx_buf);			//Вычисляем позицию свободной ячейки
		u8 ch = 0;
		//rx_buf[pos] = USART2->DR; 			//Считываем содержимое регистра данных
		//tx_char(rx_buf[pos]);
		ch = USART3->DR;
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

