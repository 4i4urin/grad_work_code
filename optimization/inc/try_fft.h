#ifndef TRY_FFT_H
#define TRY_FFT_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define u8 		uint8_t
#define u16 	uint16_t
#define u32 	uint32_t
#define u62 	uint64_t

#define s8 		int8_t
#define s16 	int16_t
#define s32  	int32_t
#define s64 	int32_t

#include "fft_table.h"

#define MEAS_POW2   12
#define MEAS_NUM 	(1 << MEAS_POW2)
#define REVERS_SHIFT 16 - MEAS_POW2 // use uint

#define PI			3.14159265358979323846264338327950288
#define ABS(x, y) 	sqrt(pow(x, 2) + pow(y, 2))

typedef enum _e_errors
{
	E_ERR_FILE_OPEN = 1,
	E_ERR_FILE_READ, 
	E_ERR_FILE_WRITE, 
	E_ERR_FILE_CLOSE,
	E_ERR_FFT_DIM
} e_errors;

typedef struct _t_complex
{
    s16 re; 
    s16 im;
} t_complex;

void show_array(u16* parr, u16 arr_size);
void out_array_file(u16* parr, u16 arr_size, const char* pfile_name);
t_complex* read_arr_file(t_complex* parr, u16 arr_size, char* pfile_name);
void exit_code(e_errors ex_code, const char* pmsg_to_usr);

u32 get_time_us(void);
// int gettimeofday(struct timeval *tv, struct timezone *tz);


// fft 
static void print_vector( const char *title, t_complex *x, int n);
void fft(const t_complex* pin_vect, t_complex* res);
u16 reverse(u16 byte);

t_complex fft_first_op(const t_complex*    const pfirst,  // A
					   const t_complex*    const psecond, // B
					   const t_complex_s8* const pw);     // W

t_complex fft_second_op(const t_complex* 	const pfirst,  // A
						const t_complex* 	const psecond, // B
						const t_complex_s8* const pw);	   // W

// sqrt
u16 isqrt_linear(u32 val);
u16 isqrt_binary(u32 val);
u16 isqrt_newton(u32 val);
u32 meas_sqrt_time(const t_complex* pcplx_arr, u16 (*pfsqrt)(u32));




#endif /* TRY_FFT_H */
