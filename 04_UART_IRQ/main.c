#include <avr/io.h>
#include "../toolbox/uart_interrupt.h"

#define CPU_F 1000000 // Clock Speed
#define BAUD 4800


int main(void)
{
	UART_init(CPU_F,BAUD);
	
	UART_printString("Atmega32A system\r\n");
	UART_printString("==================================\r\n");
	UART_printString("Serial loopback with interrupt mode ...\r\n");

	for(;;) {
		/* Echo the received character */
		UART_transmitByte(UART_receiveByte());
	}
	return 0;
}

