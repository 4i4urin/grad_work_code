/*
 * digital_pot.c
 *
 *  Created on: Mar 20, 2023
 *      Author: shishel
 */
#include "color_musical_illum.h"
#include "digital_pot.h"


static u8 reverse_8(u8 byte);
static void spi1_write(u16* pdata);

u8 _dpot_resist = 0;


u8 reverse_8(u8 byte)
{
	byte = ( ((byte & 0xaa) >> 1) | ((byte & 0x55) << 1) );
	byte = ( ((byte & 0xcc) >> 2) | ((byte & 0x33) << 2) );
	return ((byte >> 4) | (byte << 4));
}


void send_res_dpot(u8 resistance_kohm, u8 add_ohm_byte)
{
	if (resistance_kohm > MAX_DPOT_RES)
		resistance_kohm = MAX_DPOT_RES;
	if (add_ohm_byte > ADD_800_OHM)
		add_ohm_byte = ADD_800_OHM;

	_dpot_resist = resistance_kohm;
	t_dpot_send msg;
	msg.hdr.comm	  = E_DPOT_COM_WRITE;
	msg.hdr.ch_select = (resistance_kohm <= MID_DPOT_RES)
					    ? E_DPOT_CS_RANGE_LOW
					    : E_DPOT_CS_RANGE_HIGH;
	resistance_kohm = (resistance_kohm <= MID_DPOT_RES)
				 ? resistance_kohm
				 : resistance_kohm - MID_DPOT_RES;

	u8 res_byte = (resistance_kohm * 0xFF / MID_DPOT_RES) + add_ohm_byte;

	msg.data = reverse_8(res_byte);
	spi1_write((u16*)&msg);
}


u8 get_depot_res(void)
{
	return _dpot_resist;
}


void spi1_write(u16* pdata)
{
	OFF_PB4();
	SPI1->DR = *pdata;
	while ( !(SPI1->SR & SPI_SR_TXE) ) { };
	while ( SPI1->SR & SPI_SR_BSY) { };
	ON_PB4();
}
