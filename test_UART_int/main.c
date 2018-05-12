#include <avr/io.h>
#include "../toolbox/uart_int.h"

#define FOSC 1000000 // Clock Speed
#define BAUD 4800
#define MYUBRR FOSC/16/BAUD-1

extern char UART_Rx_char;
extern char UART_Tx_char;
 
int main(){

	UART_irq_init(MYUBRR);
	UART_irq_printString("Hello world !");
	
	while(1){	
		//if (UART_Rx_char!=0){
			//UART_Tx_char=UART_Rx_char;
			//UART_Rx_char=0;
			//UART_irq_transmitByte(UART_Tx_char);
			//UART_Tx_char=0;
			
			
		//}
		
	}
	return 0;
}
