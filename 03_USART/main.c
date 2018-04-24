                                                       /* Blinker Demo */

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */
#include "../lib/usart.h"

#define FOSC 1000000
#define BAUD 19200

int main(void) {
	

	USART_init(FOSC,BAUD);
								   
  // ------ Event loop ------ //
  while (1) {

    // do nothing
    
  }                                                  /* End event loop */
  return 0;                            
}
