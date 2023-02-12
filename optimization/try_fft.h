#ifndef TRY_FFT_H
#define TRY_FFT_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#define u8 		uint8_t
#define u16 	uint16_t
#define u32 	uint32_t
#define u62 	uint64_t

#define s8 		int8_t
#define s16 	int16_t
#define s32  	int32_t
#define s64 	int32_t

#define MEAS_NUM 	4096

#define PI	3.14159265358979323846264338327950288

typedef enum _e_errors
{
	E_ERR_FILE_OPEN = 1,
	E_ERR_FILE_READ, 
	E_ERR_FILE_WRITE, 
	E_ERR_FILE_CLOSE,
	E_ERR_FFT_DIM
} e_errors;

typedef struct
{
    s32 Re; 
    s32 Im;
} complex;

void show_array(s32* parr, u16 arr_size);
void out_array_file(s32* parr, u16 arr_size, const char* pfile_name);
complex* read_arr_file(complex* parr, u16 arr_size, char* pfile_name);
void exit_code(e_errors ex_code, const char* pmsg_to_usr);
u16 reverse(u16 byte);

// fft 
static void print_vector( const char *title, complex *x, int n);
void fft( complex *v, int n, complex *tmp );
s32 abs_2(s32 x, s32 y);

#endif /* TRY_FFT_H */
