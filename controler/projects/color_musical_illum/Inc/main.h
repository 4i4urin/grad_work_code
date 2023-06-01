/*
 * main.h
 *
 *  Created on: May 10 2023
 *      Author: shishel
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <string.h>
#include <ctype.h>
#include <stdio.h>


#include "project_def.h"
#include "project_types.h"


#include "stm32f1xx.h"


void set_dev_state(e_device_state state);
e_device_state get_dev_state(void);

u8* get_pctrl_panel(void);

u8 get_num_led(void);
void set_num_led(u8 number);


u8 get_power_press(void);
u8 get_mode_press(void);
void reset_mode_button(void);
void reset_power_button(void);


// just delay should be in whole project
void delay(u32 del_val);

#endif /* MAIN_H_ */
