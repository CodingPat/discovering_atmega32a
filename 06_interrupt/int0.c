//########################################################################### 
// led is flashing using busy waiting
// if button is pressed, led is immediately switched on (interrupt INT0).

//############################################################################


#define BUTTON INT0 // button connected to pin PD2=INT0
#define LED PD6 // led
#define FLASH_PERIOD 200 // half period for flashing

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


init(){
	
	// pins mode and pull-up resistor
	DDRD=0x00; // all pins PORTD input mode
	DDRD|=(1<<LED);// except output for led
	PORTD|=(1<<BUTTON);//internal pullup resistor
	
	
	//enables INT0 - toggle at low level
	GICR|=(1<<INT0); //general interrupt control register
	MCUCR&=~(1<<ISC01); //MCU control register (ISCx=sense control)
	MCUCR&=~(1<<ISC00);
	
	//enable interrupts
	sei();
}
	
	

ISR(EXT_INT0_vect){
	
		PORTD|=(1<<LED); //led on
				
}


int main(){

	init();

	while(1){
	
		PORTD^=(1<<LED); //flashing led on/off
		_delay_ms(FLASH_PERIOD);	
		
	};
	
	exit(0);
	
}
 

