#include <avr/io.h>
#include "../toolbox/usart.h"

#define FSOC 1000000
#define BAUD 4800

int main(){
	USART_init(FSOC,BAUD);
	USART_printString("Hello World ! \r\n");
	while(1){
		USART_transmitByte(USART_receiveByte());
	}
	return 0;
}
