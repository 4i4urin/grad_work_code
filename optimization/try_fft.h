#ifndef TRY_FFT_H
#define TRY_FFT_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define u8 		uint8_t
#define u16 	uint16_t
#define u32 	uint32_t
#define u62 	uint64_t

#define s8 		int8_t
#define s16 	int16_t
#define s32  	int32_t
#define s64 	int32_t

#define MEAS_NUM 4096

typedef enum _e_errors
{
	E_ERR_FILE_OPEN = 1,
	E_ERR_FILE_READ, 
	E_ERR_FILE_WRITE, 
	E_ERR_FILE_CLOSE
} e_errors;


void show_array(u16* parr, u16 arr_size);
u16* read_arr_file(u16* parr, u16 arr_size, char* pfile_name);
void exit_code(e_errors ex_code, const char* pmsg_to_usr);

#endif /* TRY_FFT_H */
