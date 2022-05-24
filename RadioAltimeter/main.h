/*
 * main.h
 *
 * Created: 16.05.2022 14:07:52
 *  Author: m.gasratov
 */ 


#ifndef MAIN_H_
#define MAIN_H_


#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/crc16.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "gost18977.h"


volatile struct {	// Структура служебных флагов
	uint8_t	recMessageOK	:1;			// Флаг успешного завершения приема сообщения
} flag = {0};


volatile uint8_t tran_byte[3];				// Массив отправляемых байт
volatile uint8_t rec_byte[7];				// Массив принимаемых байт
volatile uint8_t buffer_word[4];			// Буфер принятого слова по ГОСТ 18977

// Функция передачи байта по UART через прерывание
ISR (USART_UDRE_vect) {
	static volatile uint8_t counter = 0;
	static volatile uint8_t crc8 = 0xFF;
	if (counter < 2) {
		UDR = tran_byte[counter];
		crc8 = _crc8_ccitt_update(crc8, tran_byte[counter++]);
	} else {
		UDR = crc8;
		counter = 0;
		crc8 = 0xFF;
	}
}

// Функция приема байта по UART через прерывание
ISR (USART_RXC_vect) {
	static volatile uint8_t	counter = 0;
	static volatile uint8_t	crc8 = 0xFF;
	
	rec_byte[counter] = UDR;
	if (counter < 6) {
		if (counter == 0 && rec_byte[0] != 0x7E) return;
		crc8 = _crc8_ccitt_update(crc8, rec_byte[counter++]);
	} else {
		if (crc8 == rec_byte[6]) {
			for (uint8_t i=0; i<4; i++) buffer_word[i] = rec_byte[i+1];
		}
		counter = 0;
		crc8 = 0xFF;
	}
}


void ports_init();


#endif /* MAIN_H_ */