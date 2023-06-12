/*
 * flash.c
 *
 *  Created on: 12 june 2023 г.
 *      Author: shishel
 */
#include "main.h"

static void flash_erase(u32 pageAddress);
static void Internal_Flash_Write(u16* data, u32 address);

void falsh_write(u16* data, u32 address)
{
	flash_erase(address);
	Internal_Flash_Write(data, address);
}


void flash_erase(u32 pageAddress)
{
	while (FLASH->SR & FLASH_SR_BSY);
	if (FLASH->SR & FLASH_SR_EOP) {
		FLASH->SR = FLASH_SR_EOP;
	}

	FLASH->CR |= FLASH_CR_PER;
	FLASH->AR = pageAddress;
	FLASH->CR |= FLASH_CR_STRT;
	while (!(FLASH->SR & FLASH_SR_EOP));
	FLASH->SR = FLASH_SR_EOP;
	FLASH->CR &= ~FLASH_CR_PER;
}


//data - указатель на записываемые данные
//address - адрес во flash
//count - количество записываемых байт, должно быть кратно 2
void Internal_Flash_Write(u16* data, u32 address)
{

	while (FLASH->SR & FLASH_SR_BSY);
	if (FLASH->SR & FLASH_SR_EOP) {
		FLASH->SR = FLASH_SR_EOP;
	}

	FLASH->CR |= FLASH_CR_PG;

	*(volatile unsigned short*)(address) = *data;
	while (!(FLASH->SR & FLASH_SR_EOP));
	FLASH->SR = FLASH_SR_EOP;

	FLASH->CR &= ~(FLASH_CR_PG);
}

u16* read_num_led(u16* pdata, u32 address)
{
	u32 data = 0;
	while (FLASH->SR & FLASH_SR_BSY);
	if (FLASH->SR & FLASH_SR_EOP) {
		FLASH->SR = FLASH_SR_EOP;
	}

	FLASH->CR |= FLASH_CR_PG;

	data = *(volatile unsigned short*)(address);
	//while (!(FLASH->SR & FLASH_SR_EOP));
	//FLASH->SR = FLASH_SR_EOP;
	FLASH->CR &= ~(FLASH_CR_PG);

	*pdata = (u16)data;
	return pdata;
}
