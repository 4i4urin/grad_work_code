/*
 * digital_pot.h
 *
 *  Created on: Mar 20, 2023
 *      Author: shishel
 */

#ifndef DIGITAL_POT_H_
#define DIGITAL_POT_H_

void send_res_dpot(u8 res_byte);

#define MAX_DPOT_RES  104 				// 104 kOhm
#define MID_DPOT_RES  (MAX_DPOT_RES >> 1) // 52  kOhm


#endif /* DIGITAL_POT_H_ */
