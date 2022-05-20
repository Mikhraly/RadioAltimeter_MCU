/*
 * gost18977.c
 *
 * Created: 20.05.2022 9:16:43
 *  Author: m.gasratov
 */ 

#include "gost18977.h"

#define DELAY_US (1000000UL/(2*GOST18977_BOAD))


void gost18977_sendByte(uint8_t byte) {
	for (uint8_t bit = 0; bit < 8; bit++) {
		if (byte & 1<<bit) sendPositivePulse();
		else sendNegativePulse();
	}
}

void sendPositivePulse() {
	PORT_DATA |= (1 << PIN_DATA_A);
	_delay_us(DELAY_US);
	PORT_DATA &= ~(1 << PIN_DATA_A);
	_delay_us(DELAY_US);
}

void sendNegativePulse() {
	PORT_DATA |= (1 << PIN_DATA_B);
	_delay_us(DELAY_US);
	PORT_DATA &= ~(1 << PIN_DATA_B);
	_delay_us(DELAY_US);
}