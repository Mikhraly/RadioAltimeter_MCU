/*
 * gost18977.h
 *
 * Created: 20.05.2022 9:17:03
 *  Author: m.gasratov
 */ 


#ifndef GOST18977_H_
#define GOST18977_H_


#include <avr/io.h>
#include <util/delay.h>

#define GOST18977_BOAD 100000UL
#define PORT_DATA PORTA
#define PIN_DATA_A 0
#define PIN_DATA_B 1

void gost18977_sendByte(uint8_t byte);


#endif /* GOST18977_H_ */