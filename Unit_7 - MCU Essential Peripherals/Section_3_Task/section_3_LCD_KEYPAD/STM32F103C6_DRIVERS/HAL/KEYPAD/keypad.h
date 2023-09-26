/*
 * keypad.h
 *
 * Created: 8/8/2023 2:34:37 PM
 *  Author: ABRAM
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define F_CPU 1000000UL

#include "../../../STM32F103C6_DRIVERS/MCAL/GPIO/STM32F103C6_GPIO_DRIVER.h"

#include "../../../STM32F103C6_DRIVERS/INCLUDE/STM32F103xx6.h"


#define KEYPAD_PORT				GPIOB


#define R0 GPIO_PIN_0
#define R1 GPIO_PIN_1
#define R2 GPIO_PIN_3
#define R3 GPIO_PIN_4
#define C0 GPIO_PIN_5
#define C1 GPIO_PIN_6
#define C2 GPIO_PIN_7
#define C3 GPIO_PIN_8


void KEYPAD_INIT();
char KEYPAD_GET_KEY();

#endif /* KEYPAD_H_ */
