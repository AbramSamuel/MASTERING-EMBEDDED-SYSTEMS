
/*
 * CPU_CONFIGURATION.h
 *
 * Created: 12/22/2019 3:54:10 PM
 *  Author: Kirellos Emad Samir
 */ 


#ifndef CPU_CONFIGURATION_H_
#define CPU_CONFIGURATION_H_

#undef F_CPU /*Remove previous definition*/
#define F_CPU 16000000UL/*16 MegaHz(16 Million)*/
#include <util/delay.h>
#include <avr/interrupt.h>
//#include <avr/io.h> /*All registers are Pre-Defined here*/
#include "..\INCLUDES\ATMEGA32_REGISTERS.h"
#include "..\MCAL\DIO\DIO.h"

#endif /* CPU_CONFIGURATION_H_ */