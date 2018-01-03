/*
 * uart.h
 *
 *  Created on: 2016. 11. 15
 *      Author: zhainaipeng
 */

#ifndef UART_H_
#define UART_H_

#include <asm/termios.h>

int uart_open(int *uart_fd, const char *uart_num);

int uart_init(int uart_fd, int baudrate);

int uart_tx(int uart_fd, char *data, int size);

int uart_tx_data(int uart_fd, int *data, int size);

void uart_close(int uart_fd);

#endif /* UART_H_ */
