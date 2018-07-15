#define F_CPU 8000000 // Atmega32a clock Speed
#define BAUD 19200 // UART speed
#define F_Z80 1 // 1hz

#if F_Z80==1
	#define VAL_OCR1A 1953
#elif F_Z80==5
	#define VAL_OCR1A 391
#elif F_Z80==10
	#define VAL_OCR1A 195
#elif F_Z80==50
	#define VAL_OCR1A 39
#else // default F_Z80 1hz
	#define VAL_OCR1A 1953
#endif

//10 clocks cycles to initialize CPU
#define RESET_TIME 1/F_Z80*10*1000 


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "../toolbox/uart_interrupt.h"


#define P_RXD PD0 // UART receive
#define P_TXD PD1 // UART transmit
#define P_RD PD2 // INT0
#define P_CLK PD5 //OC1A
#define P_RST PD6  // RST
#define P_WAIT PC7 // Z80 WAIT



//global variables
volatile uint8_t do_read=0;
volatile uint8_t address_lo=0;

void init_ports(){
	
	// address bus (low byte) - input mode
	DDRA=0x00;
	

	// data bus = PB port - output mode
	DDRB=0xFF;

	// signals
		
	DDRD|=(1<<P_RST); // RST - output mode
	DDRD&=~(1<<P_RXD);// RXD - input mode
	DDRD|=(1<<P_TXD); // TXD - output mode

	DDRD&=~(1<<P_RD);// Z80 /RD - input mode
	DDRD|=(1<<P_CLK); // CLK-OC1A - output mode

	DDRC|=(1<<P_WAIT);// Z80 /WAIT
	PORTC|=(1<<P_WAIT); 

}

void init_clock()
{
	
	// ========================================
	//  Init timer1
	// ========================================
	//CTC mode
	TCCR1B|=(1<<WGM12);
	
		
	//Waveform : toggle logic level	
	TCCR1A|=(1<<COM1A0);//pin OC1A
	//TCCR1A|=(1<<COM1B0);//pin OC1B
	
	//prescale clock /1024
	TCCR1B|=((1<<CS10)|(1<<CS12));
	
	
	// counter top value
	OCR1A=VAL_OCR1A;
}

void init_read()
{	
	
	// ========================================
	// Initialize INT0 (RD)
	// ========================================
	
	MCUCR|=2;//xxxxxx10 = falling edge
	
	GICR|=(1<<INT0);// INT0=bit 6 of GICR, defined via <avr/io.h>
	sei();
	
	
	
}

void reset(){
	// ========================================
	// reset Z80 to initialize - waiting minimum 5 clock cycles
	// ========================================
	
	PORTD&=~(1<<P_RST);
	_delay_ms(RESET_TIME);
	PORTD|=(1<<P_RST);

}



// Interrupt /RD signal
ISR(INT0_vect){
	PORTC&=~(1<<P_WAIT);//let Z80 wait until data ready
	address_lo=PINA;	
	do_read=1;
	
}




int main(){
	//NOP opcode
	uint8_t opcode=0x00;	
	char address_lo_string[3];//hex value = 2 symbols + \0
	uint8_t mem_value=0;	
	char mem_value_string[3];

	init_ports();
	UART_init(F_CPU,BAUD);
	_delay_ms(1);//give some time to UART to get ready before transmitting
	
	PORTB=opcode;
	
	init_clock();
	init_read();

	UART_printString("Resetting Z80 ....\r\n");
	reset();

	
	UART_printString("Providing nop's ....\r\n");
		
	while(1){
		
		if (do_read){
			mem_value=opcode;
			UART_printString("Read@ 0x");
			UART_printString(utoa(address_lo,address_lo_string,16));
			UART_printString(" value 0x");
			UART_printString(utoa(mem_value,mem_value_string,16));
			UART_printString("\r\n");
			
			do_read=0;
			PORTC|=(1<<P_WAIT);//data ready for Z80
	
		}
		//_delay_ms(400);//give some time
	
	}

	return 0;
	
}
