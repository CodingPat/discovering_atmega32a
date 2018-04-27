// Based on code examples from the ATmega32A datasheet
// and on code examples from book avr programming by Elliot Williams
// source code : https://github.com/hexagon5un/AVR-Programming

/* init USART */
void USART_init(uint16_t f_cpu,uint16_t baud);

/* transmit byte */
void USART_transmitByte(unsigned char data);

/* receive byte */
unsigned char USART_receiveByte(void);

/* flush buffer */
void USART_flush(void);

/* print string */
void USART_printString(const char myString[]);

/* read string */
void USART_readString(char myString[], uint8_t maxLength);


/* print integer byte converted to ASCII decimal number */
void USART_printInt8(uint8_t byte);

/* print integer word converted to ASCII decimal number */
void USART_printInt16(uint16_t byte);

/* print byte to ASCII binary number */
void USART_printBinaryByte(uint8_t byte);

/* convert nibble(4bits) to hex */
char USART_nibbleToHexCharacter(uint8_t nibble);

/* print byte to ASCII hex number */
void printHexByte(uint8_t byte);

/* get ASCII converted to integer(byte) */
uint8_t USART_getInt8(void);



