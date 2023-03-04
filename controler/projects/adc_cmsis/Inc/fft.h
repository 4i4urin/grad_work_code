/*
 * fft.h
 *
 *  Created on: 2 march. 2023 г.
 *      Author: shishel
 */

#ifndef FFT_H_
#define FFT_H_

#include "my_types.h"
//#include "main.h"
//#include "fft_table.h"

#define FFT_REVERS_SHIFT BITS_U16 - MEAS_POW2 // use uint16_t

void fft(const t_complex* pin_vect, t_complex* res, u16 arr_size, u8 arr_size_pow2);

// tmp = A + B * W / 100
t_complex fft_first_op(const t_complex*    pfirst,  // A
					   const t_complex*    psecond, // B
					   const t_complex_s8* pw);     // W

// tmp = A - B * W
t_complex fft_second_op(const t_complex* 	pfirst,  // A
						const t_complex* 	psecond, // B
						const t_complex_s8* pw);	 // W


#endif /* FFT_H_ */
