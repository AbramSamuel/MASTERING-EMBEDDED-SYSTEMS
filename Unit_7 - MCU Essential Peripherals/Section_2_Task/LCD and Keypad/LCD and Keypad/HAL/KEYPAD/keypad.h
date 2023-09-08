/*
 * keypad.h
 *
 * Created: 8/8/2023 2:34:37 PM
 *  Author: ABRAM
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#define KEYPAD_PORT				PORTD
#define DataDir_KEYPAD_PORT		DDRD
#define KEYPAD_PIN				PIND


#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7


void KEYPAD_INIT();
char KEYPAD_GET_CHAR();

#endif /* KEYPAD_H_ */