/*
 * flash.h
 *
 *  Created on: 12 june 2023 г.
 *      Author: shishel
 */

#ifndef FLASH_H_
#define FLASH_H_


#define __FLSH_NUMLED_ADDRESS__ 	0x0801FC00


void falsh_write(u16* data, u32 address);
u16* read_num_led(u16* pdata, u32 address);

#endif /* FLASH_H_ */
