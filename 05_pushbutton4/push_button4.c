//===========================================================
//	 
// 	Press button to toggle led on/off, while another led is flashing
// 	Real time using interrupt: button push is immediately detected 
//	
//
// 	Also use software debouncing
//
//===========================================================


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED_TOGGLE PD6
#define LED_FLASH PD5
#define BUTTON PD2
#define F_CPU 1000000 // 1Mhz
#define DEBOUNCE_TIME 500 // 500us
#define WAIT_TIME 1000 //2*100ms = 0,5hz flashing



void init(){

	DDRD|=(1<<LED_TOGGLE); // led pin = output mode
	DDRD|=(1<<LED_FLASH); // led pin = output mode

	DDRD&=~(1<<BUTTON); // button pin =input mode
	PORTD|=(1<<BUTTON); // button pin with internal push up resistor

	MCUCR|=2;//xxxxxx10 = falling edge
	
	GICR|=(1<<INT0);// INT0=bit 6 of GICR
	sei();
}


ISR(INT0_vect){
	// software debounce is not easy within interrupt	
	// _delay_ms(DEBOUNCE_TIME) gives malfunction
	// avoid using external function in interrupt routine ?
	// maybe timer interrupt could be implemented ?
	// also, interrupt routines should be kept as short as possible
	
	PORTD^=(1<<LED_TOGGLE);
	
}
		
int main(){
	init();

	while(1){
	_delay_ms(WAIT_TIME);
	PORTD^=(1<<LED_FLASH);	
	}

	return(0);
}
