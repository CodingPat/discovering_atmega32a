#include <avr/io.h>
#include <avr/power.h>
#include "../toolbox/uart_interrupt.h"

#define CPU_F 8000000 // clock speed 8Mhz
#define BAUD 4800


int main(void)
{

	
	clock_prescale_set(clock_div_1);// CPU 8Mhz
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

