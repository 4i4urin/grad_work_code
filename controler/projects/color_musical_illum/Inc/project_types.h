/*
 * project_types.h
 *
 *  Created on: Mar 20, 2023
 *      Author: shishel
 */

#ifndef PROJECT_TYPES_H_
#define PROJECT_TYPES_H_


#pragma pack(push, 1)


typedef enum _e_device_state
{
	E_DEV_WORK   = 0x00,
	E_DEV_SLEEP  = 0x01,
	E_DEV_CALIB  = 0x02
} e_device_state;


// spi transmit to Dpot data structure
typedef enum _e_dpot_comm
{
	E_DPOT_COM_NONE = 0x00,
	E_DPOT_COM_WRITE = 0x01,
	E_DPOT_COM_SHUTD = 0x02,
	E_DPOT_COM_NONE_2 = 0x03
} e_dpot_comm;


typedef enum _e_dpot_chip_sel
{
	E_DPOT_CS_RANGE_LOW  = 0x01,  // 0x01 - from 0 to 52k Ohm
	E_DPOT_CS_RANGE_HIGH  = 0x03  // 0x03 - from 52 kOhm to 104 kOhm
} e_dpot_chip_sel;


typedef struct _t_dpot_hdr
{
	u8 		 	    	 	  : 2; // don't care bits
	e_dpot_comm 		 comm : 2; // command bits
	u8 	  				 	  : 2; // don't care bits
	e_dpot_chip_sel ch_select : 2; // channel select
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
