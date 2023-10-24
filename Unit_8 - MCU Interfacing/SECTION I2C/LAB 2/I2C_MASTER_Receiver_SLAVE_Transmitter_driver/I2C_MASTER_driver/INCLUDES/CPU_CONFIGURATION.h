
/*
 * CPU_CONFIGURATION.h
 *
 * Created: 10/21/2023 6:46:07 PM
 *  Author: ABRAM
 */ 


#ifndef CPU_CONFIGURATION_H_
#define CPU_CONFIGURATION_H_

#undef F_CPU /*Remove previous definition*/
#define F_CPU 8000000UL/*8 MegaHz(8 Million)*/
#include <util/delay.h>
#include <avr/interrupt.h>
//#include <avr/io.h> /*All registers are Pre-Defined here*/

#endif /* CPU_CONFIGURATION_H_ */