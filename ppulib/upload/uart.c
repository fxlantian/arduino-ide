/*
 * uart.c
 *
 *  Created on: 2016. 11. 14.
 *  Author : zhainaipeng 
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "uart.h"

#define SUCCESS 1
#define FAIL 0

int uart_open(int *uart_fd, const char *uart_num)
{
    int fd = 0;
    fd = open((char*)uart_num, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd < 0)
	{
		perror("open uart failed\n");
		return FAIL;
	}
	*uart_fd = fd;
	return SUCCESS;
}

int uart_init(int uart_fd, int baudrate) 
{
	struct termios2 tio;

	ioctl(uart_fd, TCGETS2, &tio);

    tio.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP| INLCR|IGNCR|ICRNL| IXON);
    tio.c_oflag &= ~OPOST;
	tio.c_lflag &= ~(ECHO|ECHONL|ICANON|ISIG|IEXTEN);
    tio.c_cflag &= ~CBAUD;
    tio.c_cflag |= BOTHER;
	tio.c_ispeed = 115200;
	tio.c_ospeed = 115200;
    // 100M   
//	tio.c_ispeed = 125000;
//	tio.c_ospeed = 125000;
    //120 M
//	tio.c_ispeed = 150000;
//	tio.c_ospeed = 150000;
    //130 M
//	tio.c_ispeed = 162500;
//	tio.c_ospeed = 162500;
	if(ioctl(uart_fd, TCSETS2, &tio) != 0)
	{
		perror("pcduino : ioctl failed\n");
		return FAIL;
	}

	return SUCCESS;
}

int uart_tx(int uart_fd, char* data, int size){
	int  tx_size = 0;

	tx_size= write(uart_fd, data, size);

	return tx_size;
}

int uart_tx_data(int uart_fd, int* data, int size)
{
	int tx_size = 0;

	tx_size = write(uart_fd, data, size);

	return tx_size;
}

void uart_close(int uart_fd){
	close(uart_fd);
}

