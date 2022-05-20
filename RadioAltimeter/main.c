/*
 * RadioAltimeter.c
 *
 * Created: 16.05.2022 13:20:07
 * Author : m.gasratov
 */ 

#include "main.h"


int main(void)
{
	ports_init();
	
    while (1)
    {
		
		uint8_t gost18977_word[4];
		asm("cli");
		for (uint8_t i=0; i<4; i++) gost18977_word[i] = buffer[i];
		asm("sei");
		for (uint8_t i=0; i<4; i++) gost18977_sendByte(gost18977_word[i]);
		
    }
}


/************************************************************************/
/*                          Описания функций                            */
/************************************************************************/
void ports_init() {
	DDRA = 0b00001111;
	PORTA = 0b11110000;
	
	DDRB = 0;
	PORTB = 0xFF;
	
	DDRC = 0;
	PORTC = 0xFF;
	
	DDRD = 0;
	PORTD = 0xFF;
}
//////////////////////////////////////////////////////////////////////////