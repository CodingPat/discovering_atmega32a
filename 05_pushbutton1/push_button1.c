//=========================================================
// 
// keep button pressed to light led
//
//=========================================================



#include <avr/io.h>


#define LED PD6
#define BUTTON PD2


void init(){

	DDRD|=(1<<LED); // led pin = output mode
	
	DDRD&=~(1<<BUTTON); // button pin =input mode
	PORTD|=(1<<BUTTON); // button pin with internal push up resistor

}


int main(){
	init();

	while(1){
		
		if (!(PIND&(1<<BUTTON))){
		// if button pin is low, button is pressed
		// turn led on
			PORTD|=(1<<LED);
			
		}
		else{
		// if button pin is high, button is not pressed
		// turn led off
		
			PORTD&=~(1<<LED);
		}
			
	
	}

	return(0);
}
