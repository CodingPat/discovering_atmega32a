                                                    /* Blinker Demo */

#include <avr/io.h>
#include <util/delay.h>

#define LED      PD6
#define LED_DDR  DDRD
#define LED_PORT PORTD

#define DELAYTIME 500


int main(void) {

  // Init
  LED_DDR|=(1<<LED);                      /* set LED pin for output */
  LED_PORT|=(1<<LED);
	
  // Mainloop
  while (1) {

    _delay_ms(DELAYTIME);
    LED_PORT^=(1<<LED);
  }
  return 0;                                          /* end mainloop */
}
