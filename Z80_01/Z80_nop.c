#define F_CPU 1000000
#define CPU_F 1000000 // Clock Speed
#define BAUD 4800

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



#define INITTIME 10000

uint8_t do_read=0;
uint8_t max_loops=50;
uint8_t nr_loops=0;


void init_ports(){
	
	// address bus (low byte) - input mode
	DDRA=0x00;

	// data bus = PB port - output mode
	DDRB=0xFF;

	
	DDRD|=(1<<P_RST); // RST - output mode
	DDRD&=~(1<<P_RXD);// RXD - input mode
	DDRD|=(1<<P_TXD); // TXD - output mode

	DDRD&=~(1<<P_RD);// RD - input mode
	DDRD|=(1<<P_CLK); // CLK/OC1A - output mode

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
	OCR1A=487;
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
	_delay_ms(INITTIME);
	PORTD|=(1<<P_RST);

}



// Interrupt /RD signal
ISR(INT0_vect){
	UART_printString("@R\r\n");
	
}




int main(){
	//NOP opcode
	uint8_t opcode=0x00;	

	init_ports();	
	PORTB=opcode;
	
	UART_init(CPU_F,BAUD);	
	
	_delay_ms(2000);//give some time to write to UART
	UART_printString("Resetting Z80 ....\r\n");
	
	
		
	init_clock();
	reset();
	UART_printString("Providing NOP's ....\r\n");
	
		
	init_read();


	
		
	while(1){}

	return 0;
	
}
