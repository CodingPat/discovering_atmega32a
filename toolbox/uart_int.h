/*#########################################
    Source code from atmega32A datasheet
  #########################################
*/

void UART_init( unsigned int ubrr);

void UART_transmitByte( unsigned char data );

unsigned char UART_receiveByte( void );

void UART_printString(const char myString[]);



