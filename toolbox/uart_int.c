/*##################################################
    Simple UART TX/RX interrupt mode (without buffer)
  ##################################################
*/

#ifndef _AVR_IO_H
#include <avr/io.h>                        /* Defines pins, ports, etc */
#endif

#ifndef _AVR_INTERRUPT_H
#include <avr/interrupt.h>
#endif

#include "../toolbox/uart_int.h"


char UART_Rx_char=0; // declare variable char received (defined extern in .h)
char UART_Tx_char=0; // declare variable char received (defined extern in .h)


void UART_irq_init( unsigned int ubrr)
{
	/*Set baud rate */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	/*Enable receiver,transmitter,interrupt RX*/
	
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
	
	/* Set frame format: 8data */
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
	
	/* enable interrupts */
	sei();
}

ISR(USART_RXC_vect){
	//IRQ = byte received
	UART_Rx_char=UDR;
}

ISR(USART_UDRE_vect){
	//UDR=UART_Tx_char;
	// IRQ = data register empty
	//if data to transmit
	//if (UART_Tx_char!=0) {
	//	UDR=UART_Tx_char;
	//}
	// or disable interrupt to transmit
	//else {
	//	UCSRB&=~(1<UDRIE);
	//}
}



void UART_irq_transmitByte( unsigned char data )
{
	UDR = data;
	UCSRB|=(1<<UDRIE);
}

 

void UART_irq_printString(const char myString[]) {
  uint8_t i = 0;
  while (myString[i]) {
    UART_irq_transmitByte(myString[i]);
    i++;
  }
}



