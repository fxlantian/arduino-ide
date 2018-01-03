#include<stdio.h>
#include<string.h>

#include "uart.h"

#define baudrate 62500
static const char *uart_num = "/dev/ttyUSB0";

void parse_data(unsigned char *string, unsigned char *result)
{
	int index = 0;

	while(index < 8)
	{
		if(string[index] >= '0' && string[index] <= '9')
		{
			string[index] = string[index] - '0';
		}else{
			string[index] = string[index] - '7';
		}

		if(index % 2 == 0)
		{
			result[index / 2] = (string[index] & 0xF) << 4;
		}else{
			result[index / 2] = result[index / 2] | (string[index] & 0x0F);
		}

		index ++;
	}
    
    int i = 0;
	printf("result:");
    
	for(i = 0; i < 4; i ++)
	{
		printf("-%x-", result[i]);
	}
	printf("\n");
   
}

int main(int argc, char **argv)
{
    FILE *stim;
 
    int uart_fd = 0;

    unsigned char current_line[25];
	unsigned char addr[9];
	unsigned char data[9];

    int index = 0;
    int line_num = 0;
    unsigned int entries;

	stim = fopen(argv[1], "r");
    if (stim == NULL)
    {
        perror("can find file, open file failed \n");
    }

	uart_open(&uart_fd, uart_num);

    uart_init(uart_fd, baudrate);

	unsigned char result[5];
   
    /*    
	char start_string[9] = "FFFFFFFF";
	memset(result, 0, 4);
	parse_data(start_string, result);
	uart_tx(uart_fd, result, 4);
	uart_tx(uart_fd, result, 1);
    */

    sleep(1); 
    
    while(fgets(current_line, 25, stim) != NULL)
    {
        memset(addr, 0, 9);
		for(index = 0; index < 8; index ++)
		{
			addr[index] = current_line[index];
		}	
		printf("get addr :%s\n", addr);
        memset(result, 0, 5);
        parse_data(addr, result);

        uart_tx(uart_fd, result, 4);

        //usleep(10000);
        memset(data, 0, 9);
		for(index = 9; index < 17; index ++)
		{
			data[index - 9] = current_line[index];
		}	
		printf("get data :%s\n", data);
	    memset(result, 0, 5);       
        parse_data(data, result);
        uart_tx(uart_fd, result, 4);
        usleep(2000);
        printf("current line num is %d\n", line_num);
        /* 
        if(line_num % 9 == 0)
        {
            sleep(3);
        }
       */
		line_num ++;
    }
     
	unsigned char end_string[9] = "FFFFFFFF";
	unsigned char end[5];
    memset(end, 0, 5);
	parse_data(end_string, end);
	uart_tx(uart_fd, end, 4);
    sleep(5);
    fclose(stim);
   
	printf("line num is %d\n", line_num);
    return 0;
}
