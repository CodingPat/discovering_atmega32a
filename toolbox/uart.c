/*#########################################
    Source code from atmega32A datasheet
  #########################################
*/

#ifndef _AVR_IO_H
#include <avr/io.h>                        /* Defines pins, ports, etc */
#endif

#include "uart.h"

void UART_init( unsigned int ubrr)
{
	/*Set baud rate */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data */
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
}

void UART_transmitByte( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
	UDR = data;
}


unsigned char UART_receiveByte( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) )
	;
	/* Get and return received data from buffer */
	return UDR;
}

void UART_printString(const char myString[]) {
  uint8_t i = 0;
  while (myString[i]) {
    UART_transmitByte(myString[i]);
    i++;
  }
}


