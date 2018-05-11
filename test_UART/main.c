#include <avr/io.h>
#include "../toolbox/uart.h"

#define FOSC 1000000 // Clock Speed
#define BAUD 4800
#define MYUBRR FOSC/16/BAUD-1

 
int main(){
	char myChar;
	UART_init(MYUBRR);

	UART_printString("Atmega32A system\r\n");
	UART_printString("================\r\n");
	UART_printString("Serial loopback ...\r\n");

	while(1){
		UART_transmitByte(UART_receiveByte());
	}

	return 0;
}
