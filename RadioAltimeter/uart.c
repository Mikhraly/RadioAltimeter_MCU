/*
 * UART.c
 *
 */ 

#include "uart.h"

void uart_init() {
	UCSRB = (1<<TXEN|1<<RXEN);					// �������� ���������� � ��������
	
	UCSRB = 1<<UDRIE;							// �������� ���������� �� ������������ �������� ������ (��� ��������)
	//UCSRB = 1<<TXCIE;							// �������� ���������� �� ���������� ��������
	UCSRB = 1<<RXCIE;							// �������� ���������� �� ���������� ������
	
	UCSRC = (1<<UCSZ1|1<<UCSZ0);				// ������ ������� - 8 ���, 1 ����-���, �������� �� �������� ���
	UBRRL = (uint8_t)(SPEED & 0xFF);			// �������� �������� �������� BAUD
	UBRRH = (uint8_t)(SPEED >> 8);				// ���������� � ������� �������� �������� UART ��������� SPEED
}

uint8_t uart_receiveByte() {
	while ( !(UCSRA & (1<<RXC)) );				// �������� ������� �����
	return UDR;									// ����������� ��������� �����
}

void uart_transmitByte(uint8_t byte) {
	while ( !(UCSRA & (1<<UDRE)) );				// �������� ���������� UART � ��������
	UDR = byte;									// ������ � ������� UDR ����� ������ �������� ������� ��������
}

