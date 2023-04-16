/*
 * fft.c
 *
 *  Created on: 5 апр. 2023 г.
 *      Author: shishel
 */
#include "fft.h"


static u16 reverse(u16 byte);
void fft(const u8* pin_vect, t_complex* res);
static const t_complex_s8* fft_table(t_complex_s8* return_val,
									 const u16 base,
									 const u16 group_size
									 );

t_complex* make_fft(const u8* pinput_arr, t_complex* fft_res)
{
	fft(pinput_arr, fft_res);
	return fft_res;
}


// req FFT_DATA_NUM * 4 byte memory
u16* make_fft_abs(u16* abs_fft, const u8* pinput_arr)
{
	t_complex fft_res[FFT_DATA_NUM] = { 0 };
	fft(pinput_arr, fft_res);
	for (u16 i = 0; i < FFT_DATA_NUM << 1; i++)
		abs_fft[i] = (u16) isqrt_newton( fft_res[i].re * fft_res[i].re
	    						       + fft_res[i].im * fft_res[i].im);
	return abs_fft;
}


// Square root of integer
u16 isqrt_newton(const u32 val)
{
	// Zero yields zero
    // One yields one
	if (val <= 1)
		return (u16) val;

    // Initial estimate (must be too high)
	register u32 x0 = val >> 1;

	// Update
	register u32 x1 = (x0 + val / x0) >> 1;

	while (x1 < x0)	// Bound check
	{
		x0 = x1;
		x1 = (x0 + val / x0) >> 1;
	}
	return (u16) x0;
}


void fft(const u8* pin_vect, t_complex* res)
{
	const t_complex_s8* pcplx_w;
	t_complex_s8 cplx_w = {0, 0};

	t_complex cplx_v1 	= {0, 0};
	t_complex cplx_v2 	= {0, 0};

	const t_complex* pres_indx_1;
	const t_complex* pres_indx_2;

	s16 butterfly_mult_re = 0;
	s16 butterfly_mult_im = 0;

	s16 svolt_1 = 0, svolt_2 = 0;
	u16 base = 0, base_widlth = 0;

	register u16 indx_1 = 0, indx_2 = 0;
	// circle for step = 0 move values from pin_vect to res
	for (u16 group = 0; group < FFT_DATA_NUM >> 1 ; group++ ) // inf loop
	{
		indx_1 = (group * 2);
        indx_2 = indx_1 + 1;
        // for this part pcplx_w always the same = {64 , 0} or {1, 0} cos(0) sin(0)
        svolt_1 = pin_vect[ reverse(indx_1) ];
        svolt_2 = pin_vect[ reverse(indx_2) ];
        cplx_v1.re = svolt_1 + svolt_2; // first op
        cplx_v2.re = svolt_1 - svolt_2; // second op
        res[indx_1] = cplx_v1;// it make fft faster
        res[indx_2] = cplx_v2;
	}

    for (u8 step = 1; step < FFT_DATA_POW2; step++)
    {
        base  = 1 << step;
        base_widlth = 1 << ( step + 1 );
        for (u16 group = 0; group < (FFT_DATA_NUM >> (1 + step) ); group++ ) // inf loop
        {
            for (u16 group_size = 0; group_size < base; group_size++)
            {
                indx_1 = (group * base_widlth) + group_size;
                indx_2 = indx_1 + base;

//            	Can be changed to
//            	pcplx_w.re     =  cos(PI * group_size / base) * 100;
//            	pcplx_w.im     = -sin(PI * group_size / base) * 100;
            	pcplx_w = fft_table(&cplx_w, base << 1, group_size);

            	pres_indx_1 = res + indx_1; // A
            	pres_indx_2 = res + indx_2; // B
            	// B * W / 64
            	butterfly_mult_re = ( (pres_indx_2->re * (s16)pcplx_w->re) - (pres_indx_2->im * (s16)pcplx_w->im) ) >> 6;
            	butterfly_mult_im = ( (pres_indx_2->re * (s16)pcplx_w->im) + (pres_indx_2->im * (s16)pcplx_w->re) ) >> 6;
            	// tmp = A + B * W / 64
            	cplx_v1.re = pres_indx_1->re + butterfly_mult_re;
            	cplx_v1.im = pres_indx_1->im + butterfly_mult_im;
            	// tmp = A - B * W / 64
            	cplx_v2.re = pres_indx_1->re - butterfly_mult_re;
            	cplx_v2.im = pres_indx_1->im - butterfly_mult_im;

                res[indx_1] = cplx_v1;
                res[indx_2] = cplx_v2;
            }
        }
    }
}

// can be speed up
u16 reverse(u16 byte)
{
	byte = ( ((byte & 0xaaaa) >> 1) | ((byte & 0x5555) << 1) );
	byte = ( ((byte & 0xcccc) >> 2) | ((byte & 0x3333) << 2) );
	byte = ( ((byte & 0xf0f0) >> 4) | ((byte & 0x0f0f) << 4) );
	return ( (byte >> 8) | (byte << 8) ) >> (FFT_REVERS_SHIFT);
}

// can be speed up
const t_complex_s8* fft_table(t_complex_s8* return_val, const u16 base, const u16 group_size)
{
	const u16 index_fft_arr = group_size * (FFT_DATA_NUM / base);
	if (index_fft_arr < (FFT_DATA_NUM >> 2))
	{
		const t_complex_s8* from_table = &table_fft_arr[index_fft_arr];
		return_val->re = from_table->re;
		return_val->im = from_table->im;
	}
	else if (index_fft_arr >= (FFT_DATA_NUM >> 2))
	{
		const t_complex_s8* from_table = &table_fft_arr[index_fft_arr - (FFT_DATA_NUM >> 2)];
		return_val->re = from_table->im;
		return_val->im = -from_table->re;
	}
	return return_val;
}



