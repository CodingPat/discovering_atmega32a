//===========================================================
//
// Press button to toggle led on/off
// With software debouncing
//
//===========================================================


#include <avr/io.h>
#include <util/delay.h>

#define LED PD6
#define BUTTON PD2
#define F_CPU 1000000 // 1Mhz
#define DEBOUNCE_TIME 500 // 500us


uint8_t button_was_pressed=0;
void init(){

	DDRD|=(1<<LED); // led pin = output mode
	
	DDRD&=~(1<<BUTTON); // button pin =input mode
	PORTD|=(1<<BUTTON); // button pin with internal push up resistor

}

uint8_t read_debounce(){
	
	if (!(PIND&(1<<BUTTON))){
		//if button pressed check again after a period of time
		_delay_us(DEBOUNCE_TIME);
		if (!(PIND&(1<<BUTTON))){
		//if button still pressed, button push is confirmed
		return(1);
		}

	}
	//button not pressed, return false
	return(0);
}

int main(){
	init();

	while(1){
		if (read_debounce()){
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
