/*
 * fft.c
 *
 *  Created on: 2 march. 2023 г.
 *      Author: shishel
 */
#include "fft.h"
//#include "fft_table.h"

static u16 reverse(u16 byte, const u8 revers_shift);
void fft(const t_complex* pin_vect, t_complex* res);
// tmp = A - B * W / 100
static t_complex fft_second_op(const t_complex* 	pfirst,  // A
							   const t_complex* 	psecond, // B
							   const t_complex_s8*  pw);	 // W
// tmp = A + B * W / 100
static t_complex fft_first_op(const t_complex*    pfirst,  // A
							  const t_complex*    psecond, // B
							  const t_complex_s8* pw);     // W


t_complex* make_fft(u8* pinput_arr, t_complex* res_arr)
{
	t_complex input_arr_cmplx[MEAS_NUM] = { 0 };
	for (u16 i = 0; i < MEAS_NUM; i++)
		input_arr_cmplx[i].re = pinput_arr[i];
	fft(input_arr_cmplx, res_arr);
	return res_arr;
}


// Square root of integer
u16 isqrt_newton(u32 val)
{
	// Zero yields zero
    // One yields one
	if (val <= 1)
		return val;

    // Initial estimate (must be too high)
	u32 x0 = val >> 1;

	// Update
	u32 x1 = (x0 + val / x0) >> 1;

	while (x1 < x0)	// Bound check
	{
		x0 = x1;
		x1 = (x0 + val / x0) >> 1;
	}
	return (u16)x0;
}


u16 isqrt_binary(u32 val)
{
	u32 res = 0;
	u32 M = 0;
	u32 R = val + 1;

    while (res != R - 1)
    {
        M = (res + R) >> 1;

		if (M * M <= val)
			res = M;
		else
			R = M;
	}

    return (u16)res;
}

u16 isqrt_linear(u32 val)
{
	u32 res = 0;
	u32 a = 1;
	u32 d = 3;

	while (a <= val)
	{
		a 	= a + d;	// (a + 1) ^ 2
		d 	= d + 2;
		res = res + 1;
	}

	return (u16)res;
}



void fft(const t_complex* pin_vect, t_complex* res)
{
	const t_complex_s8* pcplx_w;
	t_complex cplx_temp1 = {0, 0};
	t_complex cplx_temp2 = {0, 0};
	t_complex cplx_v1    = {0, 0};
	t_complex cplx_v2    = {0, 0};
	u16 base = 0, base_widlth = 0;
	u16 indx_1 = 0, indx_2 = 0;

    for (u8 step = 0; step < MEAS_POW2; step++)
    {
        base  = 1 << step;
        base_widlth = 1 << ( step + 1 );
        for (u16 group = 0; group < (MEAS_NUM >> (1 + step) ); group++ ) // inf loop
        {
            for (u16 group_size = 0; group_size < base; group_size++)
            {
                pcplx_w = fft_table(base * 2, group_size);
                indx_1  = (group * base_widlth) + group_size;
                indx_2  = indx_1 + base;

                if (!step)
                {
                    cplx_temp1.re = pin_vect[ reverse(indx_1, FFT_REVERS_SHIFT) ].re;
                    cplx_temp2.re = pin_vect[ reverse(indx_2, FFT_REVERS_SHIFT) ].re;
                    cplx_v1 = fft_first_op (&cplx_temp1, &cplx_temp2, pcplx_w);
                    cplx_v2 = fft_second_op(&cplx_temp1, &cplx_temp2, pcplx_w);
                } else
                {
	                cplx_v1 = fft_first_op (&res[indx_1], &res[indx_2], pcplx_w);
	                cplx_v2 = fft_second_op(&res[indx_1], &res[indx_2], pcplx_w);
                }

                res[indx_1] = cplx_v1;
                res[indx_2] = cplx_v2;
            }
        }
    }
}


// tmp = A + B * W / 100
t_complex fft_first_op(const t_complex*    pfirst,  // A
					   const t_complex*    psecond, // B
					   const t_complex_s8* pw)      // W
{
	t_complex tmp = {0, 0};
	tmp.re = ( (psecond->re * (s16)pw->re) - (psecond->im * (s16)pw->im) ) / 100;
	tmp.im = ( (psecond->re * (s16)pw->im) + (psecond->im * (s16)pw->re) ) / 100;
	tmp.re += pfirst->re;
	tmp.im += pfirst->im;
	return tmp;
}


// tmp = A - B * W
t_complex fft_second_op(const t_complex* 	pfirst,  // A
						const t_complex* 	psecond, // B
						const t_complex_s8* pw)	   // W
{
	t_complex tmp = {0, 0};
	tmp.re = ( (psecond->re * (s16)pw->re) - (psecond->im * (s16)pw->im) ) / 100;
	tmp.im = ( (psecond->re * (s16)pw->im) + (psecond->im * (s16)pw->re) ) / 100;
	tmp.re = pfirst->re - tmp.re;
	tmp.im = pfirst->im - tmp.im;
	return tmp;
}


u16 reverse(u16 byte, const u8 revers_shift)
{
	byte = ( ((byte & 0xaaaa) >> 1) | ((byte & 0x5555) << 1) );
	byte = ( ((byte & 0xcccc) >> 2) | ((byte & 0x3333) << 2) );
	byte = ( ((byte & 0xf0f0) >> 4) | ((byte & 0x0f0f) << 4) );
	return ( (byte >> 8) | (byte << 8) ) >> (revers_shift);
}

