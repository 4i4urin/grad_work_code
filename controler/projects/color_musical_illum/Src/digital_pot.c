/*
 * digital_pot.c
 *
 *  Created on: Mar 20, 2023
 *      Author: shishel
 */
#include "color_musical_illum.h"


static u8 reverse_8(u8 byte);
static void spi1_write(u16* pdata);


u8 reverse_8(u8 byte)
{
	byte = ( ((byte & 0xaa) >> 1) | ((byte & 0x55) << 1) );
	byte = ( ((byte & 0xcc) >> 2) | ((byte & 0x33) << 2) );
	return ((byte >> 4) | (byte << 4));
}


void send_dpot(u8 res_byte)
{
	t_dpot_send msg;
	msg.hdr.comm = E_DPOT_COM_WRITE;
	msg.hdr.ch_select = 0x03;
	msg.hdr.db_1 = 0x03;
	msg.hdr.db_2 = 0x00;
	msg.data = reverse_8(res_byte);
	spi1_write((u16*)&msg);
}

void spi1_write(u16* pdata)
{
	OFF_PB4();
	SPI1->DR =  *pdata;
	while ( !(SPI1->SR & SPI_SR_TXE) ) { };
	while ( SPI1->SR & SPI_SR_BSY) { };
	ON_PB4();
}
