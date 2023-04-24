/*
 * digital_pot.h
 *
 *  Created on: Mar 20, 2023
 *      Author: shishel
 */

#ifndef DIGITAL_POT_H_
#define DIGITAL_POT_H_

void send_res_dpot(u8 resistance, u8 add_ohm_byte);

u8 get_depot_res(void);


#define MAX_DPOT_RES  104 				// 104 kOhm
#define MID_DPOT_RES  (MAX_DPOT_RES >> 1) // 52  kOhm


#define ADD_200_OHM 	1
#define ADD_400_OHM 	2
#define ADD_600_OHM 	3
#define ADD_800_OHM 	4


#endif /* DIGITAL_POT_H_ */
