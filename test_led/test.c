//########################################################################### 
// led slowly flashing every 3 seconds with busy waiting delay. 
// button connected to interrupt0 (low triggering) makes led instantly flashing faster.
// no debouncing of button
//############################################################################


#define BUTTON INT0 // button connected to pin PD2=INT0
#define LED PD4 // led connected to pin PD4
#define WAIT 4000 // wait x ms between flashing
#define NR_FLASH 5 // number of flash
#define FLASH_SLOW 500 // half period for slowly flashing
#define FLASH_FAST 100 // half period for fast flashing

//UART parameters
#define F_CPU 1000000 //also used by delay functions
#define BAUD 4800

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../toolbox/uart_interrupt.h"


init(){
	
	// pins mode and pull-up resistor
	DDRD=0x00; // all pins PORTD input mode
	DDRD|=(1<<LED);// except output for led
	
}
	
	


int main(){
	init();
	PORTD|=(1<<LED); //led on
	while(1){};
	exit(0);
	
}
 

