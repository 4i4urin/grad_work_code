#ifndef _MAIN_H_
#define _MAIN_H_

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

#define MEAS_POW2    12
#define MEAS_NUM 	 (1 << MEAS_POW2)
#define REVERS_SHIFT 16 - MEAS_POW2 // use uint16_t


typedef struct _t_complex
{
    s16 re; 
    s16 im;
} t_complex;


typedef struct _t_complex_s8
{
    s8 re;
    s8 im;
} t_complex_s8;


#endif /* _MAIN_H_ */
