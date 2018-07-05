//=============================================
// Flash led using internal interrupt timer0
//=============================================

#include <avr/io.h>

void init(){
	
	
	//CTC mode
	TCCR1B|=(1<<WGM12);
	
		
	//Waveform : toggle logic level	
	TCCR1A|=(1<<COM1A0);//pin OC1A
	//TCCR1A|=(1<<COM1B0);//pin OC1B
	
	//prescale clock /1024
	TCCR1B|=((1<<CS10)|(1<<CS12));
	
	
	// counter top value
	OCR1A=487;

	//output pin
	DDRD|=(1<<PD5);//OC1A	
	//DDRD|=(1<<PD4);//OC1B	


}

int main(){

	init();

	while(1){}

	return(0);

}
