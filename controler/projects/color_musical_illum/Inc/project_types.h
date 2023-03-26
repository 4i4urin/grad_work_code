/*
 * project_types.h
 *
 *  Created on: Mar 20, 2023
 *      Author: shishel
 */

#ifndef PROJECT_TYPES_H_
#define PROJECT_TYPES_H_


#pragma pack(push, 1)

// spi transmit to Dpot data structure
typedef enum _e_dpot_comm
{
	E_DPOT_COM_NONE = 0x00,
	E_DPOT_COM_WRITE = 0x01,
	E_DPOT_COM_SHUTD = 0x02,
	E_DPOT_COM_NONE_2 = 0x03
} e_dpot_comm;


typedef struct _t_dpot_hdr
{
	u8 		 	    	 : 2; // don't care bits
	e_dpot_comm 	comm : 2; // command bits
	u8 	  				 : 2; // don't care bits
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


#endif /* PROJECT_TYPES_H_ */
