#define B_CLOCK  PD5  // horloge
#define B_RESET  PD6  // réinitialisation
#define B_RD     PD2   // lecture
#define B_WR     PD3   // écriture

#define BITS_ADDR  8  // nombre de bits d'adresse
#define CLKDELAY   40  // delai horloge

#define F_CPU 8000000 // Atmega32a clock Speed
#define BAUD 19200 // UART speed


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "../toolbox/uart_interrupt.h"




// Bus d'adresse
//                   bit      0   1   2   3   4   5   6   7   
int pinsAddress[BITS_ADDR] = {PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7};

// Bus de données
//               bit   0   1   2   3   4   5   6   7
int pinsData[8]     = {PB0,PB1,PB2,PB3,PB4,PB5,PB6,PB7};

// Variable pour la routine d'interruption
volatile int doread=0;

// Variable pour la routine d'interruption
volatile int dowrite=0;

// Routine d'interruption

ISR(INT0_vect){
  doread=1;
}

// Routine d'interruption
ISR(INT1_vect) {
  dowrite=1;
}


// Fonction horloge
void doClock(unsigned int n) {
  for(int i=0; i<n; i++) {
    PORTD|=(1<<B_CLOCK); 
    _delay_ms(CLKDELAY);
    PORTD&=~(1<<B_CLOCK);
    _delay_ms(CLKDELAY);
  }
}

// Réinitialisation
void doReset() {
    PORTD&=~(1<<B_RESET);
	doClock(5);
    PORTD|=(1<<B_RESET);
}

// Lecture de l'adresse
unsigned int getaddr() {
  unsigned int addr = 0;

  for(int pin=0; pin<BITS_ADDR; pin++) {
      if(PORTA&(1<<pinsAddress[pin]))
        addr |= (1 << pin);
  }
  
  return addr;
}

// Définition des bits de données
void setData(unsigned char data) {
  for( int pin = 0; pin < 8; pin++ )
    DDRB|=(1<<pinsData[pin]);

  for(int pin=0; pin<8; pin++) {
    if(data & 1)
      PORTB|=(1<<pinsData[pin]);
    else
      PORTB&=~(1<<pinsData[pin]);
    data >>= 1;
  }
}



void init_read()
{	
	
	// ========================================
	// Initialize INT0
	// ========================================
	// MCUCR xxxxxx10 = INT0 falling edge
	MCUCR&=~(1<<0);	
	MCUCR|=(1<<1);
	

	GICR|=(1<<INT0);// INT0=bit 6 of GICR, defined via <avr/io.h>
	sei();
	

}

void init_write()
{
	// ========================================
	// Initialize INT1
	// ========================================
	// MCUCR xxxx10xx = INT1 falling edge

	MCUCR&=~(1<<2);	
	MCUCR|=(1<<3);
	

	GICR|=(1<<INT1);// INT0=bit 7 of GICR, defined via <avr/io.h>
	sei();
	

}

// Lecture des  bits de données
unsigned char getData() {
  //_delay_ms(10);
  unsigned char data = 0;
  for(int pin=0; pin<8; pin++) {
    if(PORTB&(1<<pinsData[pin])) {
      data |= (1 << pin);
    }
  }
  return data;
}

// Configuration
void setup() {
  PORTD|=(1<<B_CLOCK);
  PORTD|=(1<<B_RESET);
	PORTD&=~(1<<B_RD);
	PORTD&=~(1<<B_WR);	
  
  // Tout le bus de données en entrée par défaut
  // On le met en sortie juste avant écriture
  for( int pin = 0; pin < 8; pin++ )
    DDRB&=~(1<<pinsData[pin]);

  // Tout le bus d'adresse en entrée
  for( int pin = 0; pin<BITS_ADDR; pin++ )
    DDRA&=~(1<<(pinsAddress[pin]));

  // Activation moniteur série
  UART_init(F_CPU,BAUD);
  _delay_ms(25);

  // Reset du Z80
  UART_printString("Reset Z80");
  doReset();
  _delay_ms(10);


  // On attache les interruptions
  // Un changement d'état haut vers bas appelle nos routines
  initRead();
  initWrite();
}

// Mémoire pour notre Z80
unsigned char mem[] = {
  0xc3, 0x04, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x00, 0x00
};

/*
unsigned char mmem[] = {
  0x31, 0x40, 0x00, 0x3a, 0x1a, 0x00, 0x3c, 0x32, 0x1a, 0x00, 0x00, 0x00, 0xf5, 0x00, 0xf1, 0x00,
  0xcd, 0x16, 0x00, 0xc3, 0x03, 0x00, 0x00, 0x00, 0x00, 0xc9, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
*/


int main(){
// Boucle principale
	while(1) {
		unsigned int addr;
		char hex_byte_string[3];



		if(doread) {
		  // Récupération de l'adresse
		  addr = getaddr();
		  // Affichage
		  UART_printString("Adresse: 0x");
		  if(addr < 0x10)   UART_printString("0");
		  if(addr < 0x100)  UART_printString("0");
		  if(addr < 0x1000) UART_printString("0");

			utoa(addr,hex_byte_string,16);
		  UART_printString(hex_byte_string);

		  // Si l'adresse est valide (dans les 64 octets de mémoire)
		  if(addr >= 0 && addr < sizeof(mem)) {
		    // On "pousse" les données correspondante sur le bus
		    setData(mem[addr]);
		    // Et on affiche le tout
		    UART_printString(" [0x");
		    if(mem[addr] < 0x10)   UART_printString("0");
		    
				utoa(mem[addr],hex_byte_string,16);
			  UART_printString(hex_byte_string);

		    UART_printString("]");
		  } else {
		    // Nous sommes hors de l'espace mémoire émulé
		    // On renvoi 0x00, l'instruction NOP
		    setData(0x00);
		    UART_printString(" !!!!!");
		  }
		  // On confirme la prise en charge
		  doread=0;
		} else if(dowrite) {
		  // Récupération de l'adresse
		  addr = getaddr();
		  // Affichage
		  UART_printString("Adresse: 0x");
		  if(addr < 0x10)   UART_printString("0");
		  if(addr < 0x100)  UART_printString("0");
		  if(addr < 0x1000) UART_printString("0");
		  
			utoa(addr,hex_byte_string,16);
		  UART_printString(hex_byte_string);

		  // Si l'adresse est valide (dans les 64 octets de mémoire)
		  if(addr >= 0 && addr < sizeof(mem)) {
		    // On "place" les données correspondante du bus en mémoire
		    mem[addr] = getData();
		    // Et on affiche le tout
		    UART_printString(" [0x");
		    if(mem[addr] < 0x10)   UART_printString("0");
		    
				utoa(mem[addr],hex_byte_string,16);
			  UART_printString(hex_byte_string);

				UART_printString("] W \r\n");
		  } else {
		    // Nous sommes hors de l'espace mémoire émulé
		    UART_printString(" !!!!! W");
		  }
		  // On confirme la prise en charge
		  dowrite=0;
		}

		// Impulsion horloge
		doClock(1);
		// bus de données en entrée
		for( int pin = 0; pin < 8; pin++ )
		  DDRB&=~(1<<pinsData[pin]);  // input
	}
	
	return(0);
}
