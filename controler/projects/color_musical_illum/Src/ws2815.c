/*
 * ws2815.c
 *
 *  Created on: May 12 2023 г.
 *      Author: shishel
 */
#include "main.h"
#include "ws2815.h"
#include "usart.h"


//static void ws2815_send(void);
static u8 ws2815_send_dma(void);

static u16 sum_arr(u16* pstart, u16 size);
static u16 init_freq_band(t_freq_led* pfreq_band, u16* pfft_abs, char* tx_buf);


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


u8 ws2815_set(u8 posX, u8 Rpixel, u8 Gpixel,
		u8 Bpixel, u8 bright) {

	if (posX > LED_COUNT)
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


void one_colore_full_led(u8 Rpixel, u8 Gpixel, u8 Bpixel, u8 brigh)
{
	for (register u16 i = 0; i < LED_COUNT; i++)
		ws2815_set(i, Rpixel, Gpixel, Bpixel, brigh);
	ws2815_send_dma();
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

		ws2815_set(i, Rpixel, Gpixel, Bpixel, bright);
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
			ws2815_set(taile, Rpixel_tail, Gpixel_tail, Bpixel_tail,
					bright_tail);
		}
		ws2815_send();
		delay(100000);
	}
	ws2815_buff_clear();
}


u8 calc_tail_len(u8 fourbin) {
	for (u8 offset = 3; offset > 0; offset--) {
		if ((fourbin >> offset) == 1)
			return offset + 1;
	}
	return fourbin;
}


void freq_led_mode(u16* pfft_abs, char* tx_buf)
{
//	u16 led_sum = (u16) FFT_ABS_DATA_NUM / LED_COUNT;
//	u16 sum_abs = 0;
//
//	for (register u16 i = 0; i < LED_COUNT; i++)
//	{
//		sum_abs = sum_arr(pfft_abs + (i * led_sum), led_sum);
////		sprintf(tx_buf, "%d\r\n", sum_abs);
////		tx_str(tx_buf);
//		if (sum_abs > 25)
//			ws2815_set(i, 2, 3, 8, 8);
//		else
//			ws2815_set(i, 0, 0, 0, 0);
//	}
//	ws2815_send_dma();

	t_freq_led freq_band[NUM_BAND] = { 0 };
	u8 turnon_border = init_freq_band(freq_band, pfft_abs, tx_buf) / LED_COUNT;
	u8 led_pos = 0;
	u8 led_pos_start = 0;
	for (u8 i = 0; i < NUM_BAND; i++)
	{
		u8 counts_per_LED = freq_band[i].size_freq / freq_band[i].num_led;
		for ( ; led_pos < freq_band[i].num_led + led_pos_start; led_pos++)
		{
//			sprintf(tx_buf, "%2d:\t%d\r\n", led_pos,
//					(sum_arr(freq_band[i].p_freq_arr, counts_per_LED) > turnon_border) ? 1 : 0);
//			tx_str(tx_buf);
			if (sum_arr(freq_band[i].p_freq_arr, counts_per_LED) > turnon_border)
				ws2815_set(led_pos, 7, 0, 3, 7);
			else
				ws2815_set(led_pos, 0, 0, 0, 0);
			freq_band[i].p_freq_arr += counts_per_LED;
		}
		led_pos_start = led_pos;
	}
	ws2815_send_dma();
}


u16 init_freq_band(t_freq_led* pfreq_band, u16* pfft_abs, char* tx_buf)
{
	u16 abs_sum = 0;
	u16 band_width[NUM_BAND] = { 0 };
	// fix me
	band_width[0] = FREQ_LIM_1 / SINGLE_SAMPLE_RATE;
	band_width[1] = FREQ_LIM_2 / SINGLE_SAMPLE_RATE;
	band_width[2] = FREQ_LIM_3 / SINGLE_SAMPLE_RATE;
	band_width[3] = FREQ_LIM_4 / SINGLE_SAMPLE_RATE;
	band_width[3] = (band_width[3] > FFT_ABS_DATA_NUM) ? FFT_ABS_DATA_NUM
													   : band_width[3];

	u8 num_led_in_band = LED_COUNT / NUM_BAND;
	u8 num_led_mod = LED_COUNT % NUM_BAND;

	pfreq_band[0].num_led = num_led_in_band;
	pfreq_band[0].p_freq_arr = pfft_abs;
	pfreq_band[0].size_freq = band_width[0];
	pfreq_band[0].sum_freq = sum_arr(pfreq_band[0].p_freq_arr, pfreq_band[0].size_freq);

	abs_sum += pfreq_band[0].sum_freq;

	sprintf(tx_buf, "%d; %p; %d;\t%d\r\n", pfreq_band[0].num_led, pfreq_band[0].p_freq_arr,
					pfreq_band[0].size_freq, pfreq_band[0].sum_freq);
	tx_str(tx_buf);

	for (u8 i = 1; i < NUM_BAND; i++)
	{
		pfreq_band[i].num_led = (i == 1) ? num_led_in_band + num_led_mod : num_led_in_band;
		pfreq_band[i].p_freq_arr = pfft_abs + pfreq_band[i - 1].size_freq;
		pfreq_band[i].size_freq = band_width[i] - band_width[i - 1];
		pfreq_band[i].sum_freq = sum_arr(pfreq_band[i].p_freq_arr, pfreq_band[i].size_freq);

		abs_sum += pfreq_band[i].sum_freq;
		sprintf(tx_buf, "%d; %p; %d;\t%d\r\n", pfreq_band[i].num_led, pfreq_band[i].p_freq_arr,
				pfreq_band[i].size_freq, pfreq_band[i].sum_freq);
		tx_str(tx_buf);
	}
	return abs_sum;
}


u16 sum_arr(u16* pstart, u16 size)
{
	u16 sum = 0;
	for (u16 i = 0; i < size; i++)
		sum += pstart[i];
	return sum;
}



