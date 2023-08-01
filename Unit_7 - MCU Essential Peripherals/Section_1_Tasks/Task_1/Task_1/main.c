/*
 * Section_1_task_1.c
 *
 * Created: 7/31/2023 6:33:05 PM
 * Author : ABRAM
 */ 

#include "Memory_Map.h"
#include "Utilities.h"
#define F_CPU 8000000UL
#include <util/delay.h>



int main(void)
{
		 SETBIT(DDRD,5);
		 SETBIT(DDRD,6);
		 SETBIT(DDRD,7);

    while (1) 
    {
		
		SETBIT(PORTD,5);
		_delay_ms(500);
		SETBIT(PORTD,6);
		_delay_ms(500);
		SETBIT(PORTD,7);
		_delay_ms(500);
		CLEARBIT(PORTD,7);
		_delay_ms(500);
		CLEARBIT(PORTD,6);
		_delay_ms(500);
		CLEARBIT(PORTD,5);
		_delay_ms(500);
		
    }
}

