void UART_irq_init( unsigned int ubrr);

void UART_irq_transmitByte( unsigned char data );

unsigned char UART_irq_receiveByte( void );

void UART_irq_printString(const char myString[]);



