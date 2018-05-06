/*#########################################
    Source code from atmega32A datasheet
  #########################################
*/

#include <avr/io.h>                        /* Defines pins, ports, etc */

#define FOSC 1000000 // Clock Speed
#define BAUD 4800
#define MYUBRR FOSC/16/BAUD-1




void USART_Init( unsigned int ubrr)
{
	/*Set baud rate */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data */
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
	UDR = data;
}


unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) )
	;
	/* Get and return received data from buffer */
	return UDR;
}


void main( void )
{
	USART_Init(MYUBRR);

	while(1){
			USART_Transmit(USART_Receive());
		}

}



