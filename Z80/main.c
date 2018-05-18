#define F_CPU 1000000
#define CPU_F 1000000 // Clock Speed
#define BAUD 4800

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "../toolbox/uart_interrupt.h"


#define P_RXD PD0 // UART receive
#define P_TXD PD1 // UART transmit
#define P_CLK PD4 // clock signal
#define P_RST PD5 // reset signal
#define P_RD PD6  // read signal
#define P_WR PD7  // write signal

#define CLKDELAY 40 // 40ms lo + 40 ms hi = 80ms = 12.5hz
#define NRLOOPS 100 // number of loops before stopping 

//prototypes
void do_clock();


void init(){
	// address bus (low byte) = PA port
	DDRA=0x00;

	// data bus = PB port
	DDRB=0xFF;

	// uart rx/tx + signals = PD port

	DDRD=0b00110010; //WR-RD-RST-CLK-X-X-TXD-RXD
	
	UART_init(CPU_F,BAUD);


	// reset Z80 to initialize - waiting 5 clock cycles
	DDRD&=~(1<<P_RST);	
	for(int i=0;i<5;i++){
		do_clock();
	}
	DDRD|=(1<<P_RST);
}

void do_clock(){
	PORTD|=(1<<P_CLK);
	_delay_ms(CLKDELAY);
	PORTD&=~(1<<P_CLK);
	_delay_ms(CLKDELAY);
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

	//limit number of cycles
	for(int i=0;i<NRLOOPS;i++){
		do_clock();
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
		
	}
	
	while(1){};

	return 0;
	
}
