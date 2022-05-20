/*
 * UART.h
 *
 */ 


#ifndef UART_H_
#define UART_H_


#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>

#define	BAUD	115200UL				// Скорость обмена по UART
#define SPEED	(F_CPU/(BAUD*16)-1)		// Константа для записи в регистр скорости передачи UART

void	uart_init();
uint8_t	uart_receiveByte();
void	uart_transmitByte(uint8_t);


#endif /* UART_H_ */