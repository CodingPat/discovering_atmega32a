                                                       /* Blinker Demo */

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */
#include "../toolbox/usart.h"

#define F_CPU 1000000
#define BAUD 19200

int main(void) {
	
	char serialCharacter;
	USART_init(F_CPU,BAUD);
	USART_printString("Hello World!\r\n");
								   
  // ------ Event loop ------ //
  while (1) {
		
		// get a character from terminal
		serialCharacter = USART_receiveByte();

		// echo character to terminal
		USART_printString("Character received : ");
    USART_transmitByte(serialCharacter);
		USART_printString("\r\n"); /*carriage return + line feed*/
		
		
    
  }                                                  /* End event loop */
  return 0;                            
}
