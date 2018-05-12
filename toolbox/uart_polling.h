/*#########################################
    Source code from atmega32A datasheet
  #########################################
*/

void UART_polling_init( unsigned int ubrr);

void UART_polling_transmitByte( unsigned char data );

unsigned char UART_polling_receiveByte( void );

void UART_polling_printString(const char myString[]);




