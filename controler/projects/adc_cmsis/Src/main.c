#include "main.h"
#include <math.h>
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
u8 tim4_enable;



//  Передача строки по USART2 без DMA
void tx_str(const char *str)
{
	u16 i = 0;

	for (i = 0; i < strlen((char*)str); i++)
	{
		USART2->DR = str[i];								//передаём байт данных
		while ((USART2->SR & USART_SR_TC) == 0) {};			//ждём окончания передачи
	}
}


// ОТправка данных в юарт
void tx_char(const char ch)
{
	USART2->DR = ch;
	while ((USART2->SR & USART_SR_TC) == 0) {};
}


// Считываем значения с АЦП
u16 read_adc(void)
{
//	ADC1->CR2 |= ADC_CR2_SWSTART;
//	while ( !(ADC1->SR & ADC_SR_EOC) ) // wait finish of conversion
//		;
	// because of continuous mode
	return ADC1->DR;
}


// обработчик прерывания по юарт принимает пробелы и тд
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
	tim4_enable = 1;
}


void start_tim4_khz(u16 kHz)
{
	TIM4->ARR = TIM4_FREQ / (kHz * 1000); // set freq
	START_TIM4();
}


u8 reverse_8(u8 byte)
{
	byte = ( ((byte & 0xaa) >> 1) | ((byte & 0x55) << 1) );
	byte = ( ((byte & 0xcc) >> 2) | ((byte & 0x33) << 2) );
	return ((byte >> 4) | (byte << 4));
}


void send_dpot(u8 res_byte)
{
	t_dpot_send msg;
	msg.hdr.comm = E_DPOT_COM_WRITE;
	msg.hdr.ch_select = 0x03;
	msg.hdr.db_1 = 0x03;
	msg.hdr.db_2 = 0x00;
	msg.data = reverse_8(res_byte);
	spi1_write((u16*)&msg);
}

void spi1_write(u16* pdata)
{
	OFF_PA6();
	SPI1->DR =  *pdata;
	while ( !(SPI1->SR & SPI_SR_TXE) ) { };
	while ( SPI1->SR & SPI_SR_BSY) { };
	ON_PA6();
}



int main(void)
{
	// req max 14 kB memory (then fft work)
	init_device();

	delay(1000000);

	u8 volts[MEAS_NUM] = { 0 };
	u16 fft_abs[MEAS_NUM / 2] = { 0 };

	u8* pvolts = volts;
	tim4_enable = 0;

	char tx_buf[MAX_STR_SIZE] = { 0 };

	u16* pfft_abs = fft_abs;

	u16 stopwatch = 0;
	com_receive = 0;

    while (1)
    {
    	tx_str("Start_measrumrnts\r\n");
    	START_TIM3();
    	pvolts = make_meas_adc(pvolts, MEAS_NUM, 30);
    	stopwatch = take_tim3_val();
    	sprintf(tx_buf, "ADC meas time = %d.%d ms\n\n\r", stopwatch / 10,
    												 	  stopwatch % 10);
    	tx_str(tx_buf);

    	START_TIM3();
    	pfft_abs = make_fft_abs(pfft_abs, pvolts);
    	stopwatch = take_tim3_val();
    	sprintf(tx_buf, "FFT calc time = %d.%d ms\n\n\r", stopwatch / 10,
    													  stopwatch % 10);
    	tx_str(tx_buf);

    	wait_com_uart();
    	tx_str("\rADC meas:\r\n");
    	for (u16 i = 0; i < MEAS_NUM; i++)
    	{
    		sprintf(tx_buf, "%d\r\n", volts[i]);
    		tx_str(tx_buf);
    	}
    	wait_com_uart();
    	tx_str("\rFFT calc:\r\n");
    	for (u16 i = 0; i < MEAS_NUM / 2; i++)
    	{
    		sprintf(tx_buf, "%d\r\n", pfft_abs[i]);
    		tx_str(tx_buf);
    	}
    }
}


u16 take_tim3_val(void)
{
	STOP_TIM3();
	u16 res = TIM3->CNT;
	TIM3->CNT = 0;
	return res;
}


void wait_com_uart(void)
{
	while ( !com_receive) {};
	com_receive = 0;
}


u8* make_meas_adc(u8* parr, u16 size, u16 kHz)
{
	start_tim4_khz(kHz);
	for(u16 i = 0; i < size; i++)
	{
		while ( !tim4_enable) {};
		parr[i] = read_adc() >> 4;
		tim4_enable = 0;
	}
	STOP_TIM4();
	return parr;
}


// Задержка по попугаям
void delay(u32 del_val)
{
	while (del_val)
		del_val -= 1;
}
