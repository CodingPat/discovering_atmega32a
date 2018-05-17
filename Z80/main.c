#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "../toolbox/uart_interrupt.h"

#define F_CPU 1000000
#define CPU_F 1000000 // Clock Speed
#define BAUD 4800

#define P_RXD PD0 // UART receive
#define P_TXD PD1 // UART transmit
#define P_CLK PD4 // clock signal
#define P_RST PD5 // reset signal
#define P_RD PD6  // read signal
#define P_WR PD7  // write signal

#define CLKDELAY 40

void init(){
	// address bus (low byte) = PA port
	DDRA=0x00;

	// data bus = PB port
	DDRB=0xFF;

	// uart rx/tx + signals = PD port

	DDRD=0b00110010; //WR-RD-RST-CLK-X-X-TXD-RXD
	
	UART_init(CPU_F,BAUD);


	// waiting some clock cycles to let Z80 initialize
	for(int i=0;i<5;i++){
		do_clock();
	}

}

void do_clock(){
	PORTD|=(1<<P_CLK);
	_delay_ms(CLKDELAY);
	PORTD&=~(1<<P_CLK);
	_delay_ms(CLKDELAY);
}





int main(){
	uint8_t address=0;
	init();
	
	//NOP opcode
	PORTB=0x00;
	
	UART_printString("Providing NOP's - see memory adresses increasing\r\n");
	UART_printString("================================================\r\n");

	//first 50 cycles
	for(int i=0;i<20;i++){
		do_clock();
		address=PORTA;
		UART_printString("Memory address : ");
		UART_transmitByte(utoa(address));	
		UART_printString("\r\n");
		
	}
	
	while(1){};

	return 0;
	
}
