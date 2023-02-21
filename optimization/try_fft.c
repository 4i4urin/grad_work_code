#include "inc/try_fft.h"

// todo:
// 1. fft is mirrored use it
// 2. rework abs to isqrt use binary search or Newton alg kind of strange
// 3. calc sempling time
// 4. reformat projct
// 5. make fft analysis


int main(void)
{
	t_complex adc_vals[MEAS_NUM] = { 0 };
	t_complex res_fft[MEAS_NUM]  = { 0 };

	if ( read_arr_file(adc_vals, MEAS_NUM, "music.txt") == NULL )
		exit_code(E_ERR_FILE_READ, "ERROR: file read");

	u32 start_time = get_time_us();
	fft(adc_vals, res_fft);
	printf("fft time = %d\n\n", get_time_us() - start_time);

	// print_vector("fft", res_fft, 64);
	u16 res_abs[MEAS_NUM] = { 0 };

    u16 (*pfsqrt)(u32) = sqrt;
    printf("sqrt math    = %d\n\n", meas_sqrt_time(res_fft, pfsqrt));
    printf("isqrt_newton = %d\n\n", meas_sqrt_time(res_fft, isqrt_newton));
    printf("isqrt_linear = %d\n\n", meas_sqrt_time(res_fft, isqrt_linear));
    printf("isqrt_binary = %d\n\n", meas_sqrt_time(res_fft, isqrt_binary));
    for (u16 i = 0; i < MEAS_NUM / 2; i++)
		res_abs[i] = isqrt_binary( res_fft[i].re * res_fft[i].re
								 + res_fft[i].im * res_fft[i].im );

    // printf("fft time = %d\nabs[MEAS/2] time = %d\ntime sum = %d\n", 
    		// calc_time_us, calcabs_time_us, calc_time_us + calcabs_time_us);
    // show_array(res_abs, MEAS_NUM / 2);
    out_array_file(res_abs, MEAS_NUM / 2, "res_fft_c.txt");

	return 0;
}

u32 get_time_us(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (1000000 * tv.tv_sec + tv.tv_usec);
}


u32 meas_sqrt_time(const t_complex* pcplx_arr, u16 (*pfsqrt)(u32))
{
	u16 sqrt_res[MEAS_NUM] = { 0 };
	// printf("sqrt_val = %d\n", (u16) pfsqrt( pcplx_arr[1].re * pcplx_arr[1].re 
    // 					    		+ pcplx_arr[1].im * pcplx_arr[1].im));

	u32 start_time = get_time_us();
    for (u16 i = 0; i < MEAS_NUM / 2; i++)
    	sqrt_res[i] = (u16) pfsqrt( pcplx_arr[i].re * pcplx_arr[i].re 
    				+ pcplx_arr[i].im * pcplx_arr[i].im);

    return get_time_us() - start_time;
}

void fft(const t_complex* pin_vect, t_complex* res)
{
	const t_complex_s8* pcplx_w;
	t_complex cplx_temp1 = {0, 0};
	t_complex cplx_temp2 = {0, 0};
	t_complex cplx_v1    = {0, 0};
	t_complex cplx_v2    = {0, 0};
	u16 n_base = 0, n_base_widlth = 0;
	u16 indx_1 = 0, indx_2 = 0;

    for (u8 step = 0; step < MEAS_POW2; step++)
    {
        n_base  = 1 << step;
        n_base_widlth = 1 << ( step + 1 );
        for (u16 group = 0; group < (MEAS_NUM >> (1 + step) ); group++ ) // inf loop
        {
            for (u16 group_size = 0; group_size < n_base; group_size++)
            {   
                pcplx_w = fft_table(n_base * 2, group_size, MEAS_NUM);                
                indx_1  = (group * n_base_widlth) + group_size;
                indx_2  = indx_1 + n_base;

                if (!step)
                {
                    cplx_temp1.re = pin_vect[ reverse(indx_1) ].re;
                    cplx_temp2.re = pin_vect[ reverse(indx_2) ].re;
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


u16 reverse(u16 byte)
{
	byte = ( ((byte & 0xaaaa) >> 1) | ((byte & 0x5555) << 1) );
	byte = ( ((byte & 0xcccc) >> 2) | ((byte & 0x3333) << 2) );
	byte = ( ((byte & 0xf0f0) >> 4) | ((byte & 0x0f0f) << 4) );
	return ( (byte >> 8) | (byte << 8) ) >> (REVERS_SHIFT);
}


/* Print a vector of complexes as ordered pairs. */
static void print_vector( const char *title, t_complex *x, int n)
{
    int i;
    printf("%s (dim = %d):\n", title, n);

    for(i = 0; i < n; i++ ) 
        printf(" %5d,\t%5d\n", x[i].re, x[i].im);

    putchar('\n');
    return;
}


void exit_code(e_errors ex_code, const char* pmsg_to_usr)
{
	printf("%s\n", pmsg_to_usr);
	exit(ex_code);
}


void show_array(u16* parr, u16 arr_size)
{
	for (u16 i = 0; i < arr_size; i++)
		printf("%d\n", parr[i]);
}


t_complex* read_arr_file(t_complex* parr, u16 arr_size, char* pfile_name)
{
	FILE* f = fopen(pfile_name, "r");

	if (f == NULL)
		exit_code(E_ERR_FILE_OPEN, "ERROR: file open");

	for (u16 i = 0; i < arr_size; i++)
	{
		parr[i].im = 0;
		if (fscanf(f, "%hd", &parr[i].re) == EOF)
			return NULL;
		parr[i].re >>= 4;
	}

	if ( fclose(f) )
		exit_code(E_ERR_FILE_CLOSE, "ERROR: file close");

	return parr;
}


void out_array_file(u16* parr, u16 arr_size, const char* pfile_name)
{
	FILE* f = fopen(pfile_name, "w");

	if (f == NULL)
		exit_code(E_ERR_FILE_OPEN, "ERROR: file open");

	for (u16 i = 0; i < arr_size; i++)
		fprintf(f, "%hd\n", parr[i]);

	if ( fclose(f) )
		exit_code(E_ERR_FILE_CLOSE, "ERROR: file close");
}
