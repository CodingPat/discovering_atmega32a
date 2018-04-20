                                                       /* Blinker Demo */

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */

#define LEDDDR DDRD // which register must be set to output
#define LEDPORT PORTD // port to which LED is connected
#define LEDPIN PD6 // pin of the port conected to LED

int main(void) {

  // -------- Inits --------- //
	LEDDDR|=(1<<LEDPIN);            /* Data Direction Register D:
                                   set pin output enabled */

	LEDPORT=(1<<LEDPIN);          /* Turn on LED */
    							   
								   
  // ------ Event loop ------ //
  while (1) {

    // do nothing
    
  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}
