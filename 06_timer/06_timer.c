//=============================================
// Flash led using internal interrupt timer0
//=============================================

#include <avr/io.h>

void init(){
	
	//output pin
	DDRD|=(1<<PD5);//OC1A	

	//Frequence 1hz
	OCR1AL=487;
	OCR1AH=0;
	TCCR1B|=(1<<CS12)|(1<<CS10);
	TCCR1B&=~(1<<CS11);
	//CTC mode
	TCCR1B|=(1<<WGM12);
	TCCR1B&=~(1<<WGM13);
	TCCR1A&=~(1<<WGM11);
	TCCR1A&=~(1<<WGM10);
	
	//Waveform : toggle logic level	
	TCCR1A|=(1<<COM1A0);
	TCCR1A&=~(1<<COM1A1);
	

}

int main(){

	while(1){}

	return(0);

}
