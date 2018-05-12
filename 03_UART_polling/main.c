#include <avr/io.h>
#include "../toolbox/uart_polling.h"

#define FOSC 1000000 // Clock Speed
#define BAUD 4800
#define MYUBRR FOSC/16/BAUD-1

 
int main(){
	char myChar;
	UART_polling_init(MYUBRR);

	UART_polling_printString("Atmega32A system\r\n");
	UART_polling_printString("================\r\n");
	UART_polling_printString("Serial loopback with polling ...\r\n");

	while(1){
		UART_polling_transmitByte(UART_polling_receiveByte());
	}

	return 0;
}
