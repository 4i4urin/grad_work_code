/*
 * usart.h
 *
 *  Created on: 5 апр. 2023 г.
 *      Author: Саня
 */

#ifndef USART_H_
#define USART_H_

void tx_str(const char *str);
void tx_char(const char ch);
void wait_com_uart(void);


#endif /* USART_H_ */
