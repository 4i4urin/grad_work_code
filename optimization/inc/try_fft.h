#ifndef _TRY_FFT_H_
#define _TRY_FFT_H_

#include "main.h"

// #include "fft_table.h"
// #include "fft.h"

#define ABS(x, y) 	sqrt(pow(x, 2) + pow(y, 2))

typedef enum _e_errors
{
	E_ERR_FILE_OPEN = 1,
	E_ERR_FILE_READ, 
	E_ERR_FILE_WRITE, 
	E_ERR_FILE_CLOSE,
	E_ERR_FFT_DIM
} e_errors;


void show_array(u16* parr, u16 arr_size);
void out_array_file(u16* parr, u16 arr_size, const char* pfile_name);
t_complex* read_arr_file(t_complex* parr, u16 arr_size, char* pfile_name);
void exit_code(e_errors ex_code, const char* pmsg_to_usr);


// fft
void fft(const t_complex* pin_vect, t_complex* res, u16 arr_size, u8 arr_size_pow2);

u32 get_time_us(void);

static void print_vector( const char *title, t_complex *x, int n);

// sqrt
u16 isqrt_linear(u32 val);
u16 isqrt_binary(u32 val);
u16 isqrt_newton(u32 val);
u32 meas_sqrt_time(const t_complex* pcplx_arr, u16 (*pfsqrt)(u32));

#endif /* _TRY_FFT_H_ */
