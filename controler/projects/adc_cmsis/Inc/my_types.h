/*
 * my_types.h
 *
 *  Created on: 2 march 2023 г.
 *      Author: shishel
 */

#ifndef MY_TYPES_H_
#define MY_TYPES_H_

#include <stdint.h>

#define MEAS_POW2    6
#define MEAS_NUM 	 (1 << MEAS_POW2) // Number of ADC measurements
//- Coding defines -----------------------------------------------------------

#define u8 		uint8_t
#define u16 	uint16_t
#define u32		uint32_t

#define s8 		int8_t
#define s16		int16_t
#define s32		int32_t

#define BITS_U16 	16
#define BITS_U8 	8

//----------------------------------------------------------------------------

void delay(u32 del_val);

#pragma pack(push, 1)

// spi transmit to Dpot data structure
typedef enum _e_dpot_comm
{
	E_DPOT_COM_NONE = 0x00,
	E_DPOT_COM_SHUTD = 0x01,
	E_DPOT_COM_WRITE = 0x02,
	E_DPOT_COM_NONE_2 = 0x03
} e_dpot_comm;


typedef struct _t_dpot_hdr
{
	u8 		 	    db_1 : 2; // don't care bits
	e_dpot_comm 	comm : 2; // command bits
	u8 	  			db_2 : 2; // don't care bits
	u8  	   ch_select : 2;// channel select
} t_dpot_hdr;


typedef struct _t_dpot_send
{
	t_dpot_hdr  hdr;
	u8 			data;
} t_dpot_send;


#pragma pack(pop)

// types for fft
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

#endif /* MY_TYPES_H_ */
