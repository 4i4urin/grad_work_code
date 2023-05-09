/*
 * fft.h
 *
 *  Created on: 5 апр. 2023 г.
 *      Author: shishel
 */

#ifndef FFT_H_
#define FFT_H_

#include "color_musical_illum.h"

// for ping-pong buffer
#define FFT_DATA_POW2 (MEAS_POW2 - 1)
#define FFT_DATA_NUM  (1 << FFT_DATA_POW2)

#include "fft_table.h"


#define FFT_REVERS_SHIFT BITS_U16 - MEAS_POW2 // use uint16_t



t_complex* make_fft(const u8* pinput_arr, t_complex* fft_res);
u16* make_fft_abs(u16* abs_fft, const u8* pinput_arr);

u16 isqrt_newton(u32 val);

#endif /* FFT_H_ */
