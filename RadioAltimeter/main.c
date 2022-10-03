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
	uart_init();
	gost18977_init();
	
	checkCommandsFromBKU();
	sei();
	
    while (1)
    {
		checkCommandsFromBKU();
		
		if (flag.recMessageOK) { // ������ �������� � ����������� ����� ����� ������ ������� ���������
			if (flag.serviceability) PORTA |= 1<<2;
			else PORTA &= ~(1<<2);
			
			if (flag.PUI) PORTA |= 1<<3;
			else PORTA &= ~(1<<3);
			
			gost18977_sendWord(buffer_word);
		}

    }
	
}


/************************************************************************/
/*                          �������� �������                            */
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
	
	// ����� ������ ������� ���������� INT0, INT1 �� ������ ������
	// MCUCR &= ~(1<<ISC11) & (1<<ISC01);
	// MCUCR |= 1<<ISC10 | 1<<ISC00;
	// ����� ������ �������� ���������� INT2 �� ������� ������
	// MCUCSR &= ~(1<<ISC2);
	// �������� ������� ���������� INT0, INT1
	// GICR |= 1<<INT0 | 1<<INT1;	
}

void checkCommandsFromBKU() {
	if (PIND & 1<<2) tran_byte[1] |= 1<<0;	// ����. ���������
	else tran_byte[1] &= ~(1<<0);
	
	if (PIND & 1<<3) tran_byte[1] |= 1<<1;	// �������� ��
	else tran_byte[1] &= ~(1<<1);
	
	if (PIND & 1<<4) tran_byte[1] |= 1<<2;	// ������ �����
	else tran_byte[1] &= ~(1<<2);
}
//////////////////////////////////////////////////////////////////////////