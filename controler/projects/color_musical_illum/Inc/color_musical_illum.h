/*
 * color_musical_illum.h
 *
 *  Created on: Mar 20, 2023
 *      Author: shihsel
 */

#ifndef COLOR_MUSICAL_ILLUM_H_
#define COLOR_MUSICAL_ILLUM_H_

#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "project_def.h"
#include "project_types.h"


#include "stm32f1xx.h"


void set_dev_state(e_device_state state);
e_device_state get_dev_state(void);

// just delay should be in whole project
void delay(u32 del_val);


#endif /* COLOR_MUSICAL_ILLUM_H_ */
