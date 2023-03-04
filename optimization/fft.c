#include "inc/fft.h"


void fft(const t_complex* pin_vect, t_complex* res, u16 arr_size, u8 arr_size_pow2)
{
	const t_complex_s8* pcplx_w;
	t_complex cplx_temp1 = {0, 0};
	t_complex cplx_temp2 = {0, 0};
	t_complex cplx_v1    = {0, 0};
	t_complex cplx_v2    = {0, 0};
	u16 n_base = 0, n_base_widlth = 0;
	u16 indx_1 = 0, indx_2 = 0;
	u8 shift_rev = 16 - arr_size_pow2; // beacuse of use u16 in alg

    for (u8 step = 0; step < arr_size_pow2; step++)
    {
        n_base  = 1 << step;
        n_base_widlth = 1 << ( step + 1 );
        for (u16 group = 0; group < (arr_size >> (1 + step) ); group++ ) // inf loop
        {
            for (u16 group_size = 0; group_size < n_base; group_size++)
            {   
                pcplx_w = fft_table(n_base * 2, group_size, arr_size);                
                indx_1  = (group * n_base_widlth) + group_size;
                indx_2  = indx_1 + n_base;

                if (!step)
                {
                    cplx_temp1.re = pin_vect[ reverse(indx_1, REVERS_SHIFT) ].re;
                    cplx_temp2.re = pin_vect[ reverse(indx_2, REVERS_SHIFT) ].re;
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
t_complex fft_first_op(const t_complex*    const pfirst,  // A
					   const t_complex*    const psecond, // B
					   const t_complex_s8* const pw)      // W
{
	t_complex tmp = {0, 0};
	tmp.re = ( (psecond->re * (s16)pw->re) - (psecond->im * (s16)pw->im) ) / 100;
	tmp.im = ( (psecond->re * (s16)pw->im) + (psecond->im * (s16)pw->re) ) / 100;
	tmp.re += pfirst->re;
	tmp.im += pfirst->im;
	return tmp;
}


// tmp = A - B * W
t_complex fft_second_op(const t_complex* 	const pfirst,  // A
						const t_complex* 	const psecond, // B
						const t_complex_s8* const pw)	   // W
{
	t_complex tmp = {0, 0};
	tmp.re = ( (psecond->re * (s16)pw->re) - (psecond->im * (s16)pw->im) ) / 100;
	tmp.im = ( (psecond->re * (s16)pw->im) + (psecond->im * (s16)pw->re) ) / 100;
	tmp.re = pfirst->re - tmp.re;
	tmp.im = pfirst->im - tmp.im;
	return tmp;
}


u16 reverse(u16 byte, u8 revers_shift)
{
	byte = ( ((byte & 0xaaaa) >> 1) | ((byte & 0x5555) << 1) );
	byte = ( ((byte & 0xcccc) >> 2) | ((byte & 0x3333) << 2) );
	byte = ( ((byte & 0xf0f0) >> 4) | ((byte & 0x0f0f) << 4) );
	return ( (byte >> 8) | (byte << 8) ) >> (revers_shift);
}
