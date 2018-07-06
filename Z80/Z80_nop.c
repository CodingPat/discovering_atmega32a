#define F_CPU 1000000
#define CPU_F 1000000 // Clock Speed
#define BAUD 4800

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "../toolbox/uart_interrupt.h"


#define P_RXD PD0 // UART receive
#define P_TXD PD1 // UART transmit

#define P_RST PD6  // RST

#define P_RD PD2 // INT0
#define P_CLK PD5 //OC1A


#define INITTIME 10000


uint8_t max_loops=50;
uint8_t nr_loops=0;


void init(){
	// address bus (low byte) - input mode
	DDRA=0x00;

	// data bus = PB port - output mode
	DDRB=0xFF;

	
	DDRD|=(1<<P_RST); // RST - output mode
	DDRD&=~(1<<P_RXD);// RXD - input mode
	DDRD|=(1<<P_TXD); // TXD - output mode

	DDRD&=~(1<<P_RD);// RD - input mode
	DDRD|=(1<<P_CLK); // CLK - output mode


	UART_init(CPU_F,BAUD);

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

	//output pin
	DDRD|=(1<<PD5);//OC1A	

	// ========================================
	// Initialize INT0 (RD)
	// ========================================
	
	MCUCR|=2;//xxxxxx10 = falling edge
	
	GICR|=(1<<INT0);// INT0=bit 6 of GICR, defined via <avr/io.h>
	sei();
	
	// ========================================
	// reset Z80 to initialize - waiting minimum 5 clock cycles
	// ========================================
	_delay_ms(INITTIME);
	
	
}


// Interrupt /RD signal
ISR(INT0_vect){
	nr_loops+=1;
}




int main(){
	uint8_t address_lo=0;
	uint8_t opcode=0;
	char address_lo_string[3];//hex value = 2 symbols + \0
	char opcode_string[3];//hex value = 2 symbols + \0
	init();
	
	//NOP opcode
	opcode=0x40;	
	PORTB=opcode;
	
	UART_printString("Providing NOP's - see memory adresses increasing\r\n");
	UART_printString("================================================\r\n");

		
		
	
	
	while(nr_loops<max_loops){
		address_lo=PORTA;
		UART_printString("Memory address : ");
		UART_printString(utoa(address_lo,address_lo_string,16));
		UART_printString(" - ");	
		UART_transmitByte(address_lo);
		UART_printString("Opcode : ");
		UART_printString(utoa(opcode,opcode_string,16));
		UART_printString(" - ");	
		UART_transmitByte(opcode);		
		UART_printString("\r\n");
		
	};

	return 0;
	
}
