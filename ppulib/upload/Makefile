CC = gcc

run2 : uart_load.o uart.o
	cc -o run  uart_load.o uart.o

uart_load.o : parse_stim.c uart.h
	cc -c parse_stim.c -o uart_load.o

uart.o : uart.c uart.h
	cc -c uart.c -o uart.o

clean:
	rm -f *.o run
