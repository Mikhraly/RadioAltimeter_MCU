/*
 * gost18977.h
 *
 * Created: 20.05.2022 9:17:03
 *  Author: m.gasratov
 */ 


#ifndef GOST18977_H_
#define GOST18977_H_


#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define GOST18977_BOAD 48000UL
#define DDR_DATA DDRA
#define PORT_DATA PORTA
#define PIN_DATA_A 0
#define PIN_DATA_B 1

inline void gost18977_init() {
	DDR_DATA |= 1<<PIN_DATA_A | 1<<PIN_DATA_B;
}

void gost18977_sendWord(uint8_t *buffer);


#endif /* GOST18977_H_ */