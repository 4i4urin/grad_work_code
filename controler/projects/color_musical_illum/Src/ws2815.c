/*
 * ws2815.c
 *
 *  Created on: May 12 2023 г.
 *      Author: shishel
 */
#include "main.h"
#include "ws2815.h"


static u8 _buf_Led[BUF_LED_SIZE] = { 0 };
static u8 _flag_rdy = 0;


u8* get_buf_led_pointer(void)
{
	return _buf_Led;
}


void ws2815_send(void) {
	ws2815_send_dma();
	while (ws2815_is_ready() == 0) { }
}


void ws2815_buff_clear(void) {
	for (u16 i = DELAY_LEN; i < BUF_LED_SIZE - 1; i++)
		_buf_Led[i] = LOW;
	_buf_Led[BUF_LED_SIZE - 1] = 0;
}

inline u8 ws2815_set_control(u8 posX, u8* pctrl)
{
	return ws2815_set(posX, pctrl[I_RED], pctrl[I_GREEN],
							pctrl[I_BLUE], pctrl[I_BRIGHT]);
}


u8 ws2815_set(u8 posX,
		u8 Rpixel, u8 Gpixel,
		u8 Bpixel, u8 bright) {

	if (posX > get_num_led())
		return 1;

	u8 limit = 0xFF;
	if (USE_BRIGHT)
		limit = 0xF;

	if (Rpixel > limit || Gpixel > limit || Bpixel > limit)
		return 2;
	if (bright > limit)
		return 3;

	if (USE_BRIGHT)
	{
		Rpixel |= (Rpixel != 0) ? (bright << 4) : 0;
		Gpixel |= (Gpixel != 0) ? (bright << 4) : 0;
		Bpixel |= (Bpixel != 0) ? (bright << 4) : 0;
	}
	u16 i = 0;
	for (i = 0; i < 8; i++)
	{
		const u16 pxl_pos = DELAY_LEN + posX * 24 + i;

		_buf_Led[pxl_pos + 8] = ( BIT_IS_SET(Rpixel,(7-i)) == 1)
							  ? HIGH : LOW;

		_buf_Led[pxl_pos + 0] = ( BIT_IS_SET(Gpixel,(7-i)) == 1)
							  ? HIGH : LOW;

		_buf_Led[pxl_pos + 16] = ( BIT_IS_SET(Bpixel,(7-i)) == 1)
							   ? HIGH : LOW;
	}
	return 0;
}

u8 ws2815_send_dma(void) {
	if (_flag_rdy) //Если сейчас ни чего не передается
	{
		_flag_rdy = 0;

		//Настраиваем передачу данных
		DMA1_Channel5->CCR &= ~(DMA_CCR_EN); //Отключаем канал DMA
		DMA1_Channel5->CNDTR = BUF_LED_SIZE; //Устанавливаем количество данных

		TIM2->PSC = PSC_WS2815 - 1;
		TIM2->ARR = ARR_WS2815;
		TIM2->CCR1 = 0;
		TIM2->CNT = 0;
		TIM2->CR1 |= TIM_CR1_CEN; //Запускаем таймер

		DMA1->IFCR = DMA_IFCR_CTEIF5 | DMA_IFCR_CHTIF5 | DMA_IFCR_CTCIF5
				| DMA_IFCR_CGIF5; //Очищаем все флаги прерываний DMA

		DMA1_Channel5->CCR |= DMA_CCR_TCIE; //прерывание завершения передачи

		//Включаем канал DMA, тем самым начинаем передачу данных
		DMA1_Channel5->CCR |= DMA_CCR_EN;
		return 0;
	} else {
		return 1;
	}
}

u8 ws2815_is_ready(void)
{
	return _flag_rdy;
}

//Прерывание от DMA
//Сюда заходим после завершения передачи данных
void DMA1_Channel5_IRQHandler(void) {
	DMA1_Channel5->CCR &= ~(DMA_CCR_EN); //Отключаем канал DMA

	DMA1->IFCR = DMA_IFCR_CTEIF5 | DMA_IFCR_CHTIF5 | DMA_IFCR_CTCIF5
			| DMA_IFCR_CGIF5;
	//Сбрасываем все флаги прерываний

	TIM2->SR &= ~(TIM_SR_UIF); //сбрасываем флаг прерывания
	TIM2->DIER |= TIM_DIER_UIE; //разрешаем прерывание таймера
	TIM2->CCR1 = 0;

}


//прерывание от таймера
//Сюда попадаем после завершения формирования сигнала RES шины ws2815
void TIM2_IRQHandler(void) {
	TIM2->SR = 0; //Сбрасываем все флаги прерываний
	TIM2->CR1 &= ~(TIM_CR1_CEN); //останавливаем таймер
	TIM2->DIER &= ~(TIM_DIER_UIE); //запрещаем прерывание таймера
	_flag_rdy = 1;
}
