#include <avr/io.h>
#include "usart.h"

// Based on code examples from the ATmega32A datasheet
// and on code examples from book avr programming by Elliot Williams
// source code : https://github.com/hexagon5un/AVR-Programming


void USART_init(uint16_t f_cpu,uint16_t baud)
{
	
	unsigned int ubrr;	

	/*Set baud rate */
	ubrr=f_cpu/16/baud-1;
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)(ubrr);
	
/*Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);

	/* Set frame format: 8data, 1stop bit */
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
}


void USART_transmitByte( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
	UDR = data;
}

unsigned char USART_receiveByte( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) )
	;
	/* Get and return received data from buffer */
	return UDR;
}

void USART_flush( void )
{
	unsigned char dummy;
	while ( UCSRA & (1<<RXC) ) dummy = UDR;
}


//====================================================
// Sending / receiving strings
//====================================================
void USART_printString(const char myString[]) {
  uint8_t i = 0;
  while (myString[i]) {
    USART_transmitByte(myString[i]);
    i++;
  }
}

void USART_readString(char myString[], uint8_t maxLength) {
  char response;
  uint8_t i;
  i = 0;
  while (i < (maxLength - 1)) {                   /* prevent over-runs */
    response = USART_receiveByte();
    if (response == '\r') {                     /* enter marks the end */
      break;
    }
    else {
      myString[i] = response;                       /* add in a letter */
      i++;
    }
  }
  myString[i] = 0;                          /* terminal NULL character */
}

//====================================================
// Sending / receiving numbers
//====================================================


void USART_printInt8(uint8_t byte) {
              /* Converts a byte to a string of decimal text, sends it */
  USART_transmitByte('0' + (byte / 100));                        /* Hundreds */
  USART_transmitByte('0' + ((byte / 10) % 10));                      /* Tens */
  USART_transmitByte('0' + (byte % 10));                             /* Ones */
}

void printInt16(uint16_t word) {
  USART_transmitByte('0' + (word / 10000));                 /* Ten-thousands */
  USART_transmitByte('0' + ((word / 1000) % 10));               /* Thousands */
  USART_transmitByte('0' + ((word / 100) % 10));                 /* Hundreds */
  USART_transmitByte('0' + ((word / 10) % 10));                      /* Tens */
  USART_transmitByte('0' + (word % 10));                             /* Ones */
}

void USART_printBinaryByte(uint8_t byte) {
                       /* Prints out a byte as a series of 1's and 0's */
  uint8_t bit;
  for (bit = 7; bit < 255; bit--) {
    if (bit_is_set(byte, bit))
      USART_transmitByte('1');
    else
      USART_transmitByte('0');
  }
}

char nibbleToHexCharacter(uint8_t nibble) {
                                   /* Converts 4 bits into hexadecimal */
  if (nibble < 10) {
    return ('0' + nibble);
  }
  else {
    return ('A' + nibble - 10);
  }
}

void USART_printHexByte(uint8_t byte) {
                        /* Prints a byte as its hexadecimal equivalent */
  uint8_t nibble;
  nibble = (byte & 0b11110000) >> 4;
  USART_transmitByte(nibbleToHexCharacter(nibble));
  nibble = byte & 0b00001111;
  USART_transmitByte(nibbleToHexCharacter(nibble));
}

uint8_t USART_getInt8(void) {
  // Gets a numerical 0-255 from the serial port.
  // Converts from string to number.
  char hundreds = '0';
  char tens = '0';
  char ones = '0';
  char thisChar = '0';
  do {                                                   /* shift over */
    hundreds = tens;
    tens = ones;
    ones = thisChar;
    thisChar = USART_receiveByte();                   /* get a new character */    
  } while (thisChar != '\r');                     /* until type return */
  return (100 * (hundreds - '0') + 10 * (tens - '0') + ones - '0');
}
