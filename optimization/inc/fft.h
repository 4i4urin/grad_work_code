#ifndef _FFT_H_
#define _FFT_H_

#include "main.h"

#include "fft_table.h"

void fft(const t_complex* pin_vect, t_complex* res, u16 arr_size, u8 arr_size_pow2);
u16 reverse(u16 byte, u8 revers_shift);


t_complex fft_first_op(const t_complex*    const pfirst,  // A
					   const t_complex*    const psecond, // B
					   const t_complex_s8* const pw);     // W

t_complex fft_second_op(const t_complex* 	const pfirst,  // A
						const t_complex* 	const psecond, // B
						const t_complex_s8* const pw);	   // W


#endif /* _FFT_H_ */
