#include <avr/io.h>
#include "usart.h"

void USART_init(int fosc,int baud)
{
	
	unsigned int ubrr;	

	/*Set baud rate */
	ubrr=fosc/16/baud-1;
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)(ubrr);
	
/*Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);

	/* Set frame format: 8data, 1stop bit */
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
}


