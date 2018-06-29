#include <avr/io.h>
#include <util/delay.h>

#define LED PD6
#define BUTTON PD2

uint8_t button_was_pressed=0;
void init(){

	DDRD|=(1<<LED); // led pin = output mode
	
	DDRD&=~(1<<BUTTON); // button pin =input mode
	PORTD|=(1<<BUTTON); // button pin with internal push up resistor

}


int main(){
	init();

	while(1){
		if (!(PIND&(1<<BUTTON))){
			if (!button_was_pressed){
				button_was_pressed=1;
				PORTD^=(1<<LED);
			}
			
		}
		else{
				button_was_pressed=0;
		}
			
	
	}

	return(0);
}
