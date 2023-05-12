/*
 * ws2815.c
 *
 *  Created on: May 12 2023 г.
 *      Author: shishel
 */
#include "main.h"
#include "ws2815.h"


static void ws2812b_send(void);
static u8 ws2812b_send_dma(void);


static u8 _buf_Led[BUF_LED_SIZE] = { 0 };
static u8 _flag_rdy = 0;

extern u8 _inject[4];


u8* get_buf_led_pointer(void)
{
	return _buf_Led;
}


void ws2812b_send(void) {
	ws2812b_send_dma();
	while (ws2812b_is_ready() == 0) { }
}

void ws2812b_buff_clear(void) {
	for (u16 i = DELAY_LEN; i < BUF_LED_SIZE - 1; i++)
		_buf_Led[i] = LOW;
	_buf_Led[BUF_LED_SIZE - 1] = 0;
}

u8 ws2812b_set(u8 posX, u8 Rpixel, u8 Gpixel,
		u8 Bpixel, u8 bright) {

	if (posX > LED_COUNT || posX < 0)
		return 1;
	if (Rpixel > 15 || Gpixel > 15 || Bpixel > 15)
		return 2;
	if (bright > 15)
		return 3;
	Rpixel |= (Rpixel != 0) ? (bright << 4) : 0;
	Gpixel |= (Gpixel != 0) ? (bright << 4) : 0;
	Bpixel |= (Bpixel != 0) ? (bright << 4) : 0;
	u16 i = 0;
	for (i = 0; i < 8; i++) {
		if (BIT_IS_SET(Rpixel,(7-i)) == 1) {
			_buf_Led[DELAY_LEN + posX * 24 + i + 8] = HIGH;
		} else {
			_buf_Led[DELAY_LEN + posX * 24 + i + 8] = LOW;
		}
		if (BIT_IS_SET(Gpixel,(7-i)) == 1) {
			_buf_Led[DELAY_LEN + posX * 24 + i + 0] = HIGH;
		} else {
			_buf_Led[DELAY_LEN + posX * 24 + i + 0] = LOW;
		}
		if (BIT_IS_SET(Bpixel,(7-i)) == 1) {
			_buf_Led[DELAY_LEN + posX * 24 + i + 16] = HIGH;
		} else {
			_buf_Led[DELAY_LEN + posX * 24 + i + 16] = LOW;
		}
	}
	return 0;
}

u8 ws2812b_send_dma(void) {
	if (_flag_rdy) //Если сейчас ни чего не передается
	{
		_flag_rdy = 0;

		//Настраиваем передачу данных
		DMA1_Channel5->CCR &= ~(DMA_CCR_EN); //Отключаем канал DMA
		DMA1_Channel5->CNDTR = BUF_LED_SIZE; //Устанавливаем количество данных

		TIM2->PSC = PSC_WS2812B - 1;
		TIM2->ARR = ARR_WS2812B;
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

u8 ws2812b_is_ready(void)
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
//Сюда попадаем после завершения формирования сигнала RES шины ws2812b
void TIM2_IRQHandler(void) {
	TIM2->SR = 0; //Сбрасываем все флаги прерываний
	TIM2->CR1 &= ~(TIM_CR1_CEN); //останавливаем таймер
	TIM2->DIER &= ~(TIM_DIER_UIE); //запрещаем прерывание таймера
	_flag_rdy = 1;
}


void one_colore_full_led(u8 Rpixel, u8 Gpixel, u8 Bpixel, u8 brigh)
{
	for (register u16 i = 0; i < BUF_LED_SIZE; i++)
		ws2812b_set(i, Rpixel, Gpixel, Bpixel, brigh);
	ws2812b_send_dma();
}



u8 calc_tail_len(u8 bright);


void one_colore_running(u8 Rpixel, u8 Gpixel, u8 Bpixel, u8 bright)
{

	u8 tail_len = calc_tail_len(bright);
	if (Rpixel > Gpixel)
		tail_len +=	(Rpixel > Bpixel) ? calc_tail_len(Rpixel) : calc_tail_len(Bpixel);
	else
		tail_len +=	(Gpixel > Bpixel) ?	calc_tail_len(Gpixel) : calc_tail_len(Bpixel);

	for (u8 i = 0; i < LED_COUNT + tail_len; i++) {

		ws2812b_set(i, Rpixel, Gpixel, Bpixel, bright);
		u8 Rpixel_tail = Rpixel, Gpixel_tail = Gpixel,
				Bpixel_tail = Bpixel, bright_tail = bright;
		for (u8 taile = i - 1;
				taile >= 0	&& (Rpixel_tail || Gpixel_tail || Bpixel_tail || bright_tail);
				taile--) {

			Rpixel_tail >>= 1;
			Gpixel_tail >>= 1;
			Bpixel_tail >>= 1;
			Rpixel_tail |= (Rpixel != 0) ? (bright_tail << 3) : 0;
			Gpixel_tail |= (Gpixel != 0) ? (bright_tail << 3) : 0;
			Bpixel_tail |= (Bpixel != 0) ? (bright_tail << 3) : 0;
			bright_tail >>= 1;
			ws2812b_set(taile, Rpixel_tail, Gpixel_tail, Bpixel_tail,
					bright_tail);
		}
		ws2812b_send();
		delay(100000);
	}
	ws2812b_buff_clear();
}


u8 calc_tail_len(u8 fourbin) {
	for (u8 offset = 3; offset > 0; offset--) {
		if ((fourbin >> offset) == 1)
			return offset + 1;
	}
	return fourbin;
}



