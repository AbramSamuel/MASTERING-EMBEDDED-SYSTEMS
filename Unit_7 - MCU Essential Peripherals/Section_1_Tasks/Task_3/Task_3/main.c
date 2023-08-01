/*
 * Task_3.c
 *
 * Created: 8/1/2023 5:54:41 PM
 * Author : ABRAM
 */ 

#include "Memory_Map.h"
#include "Utilities.h"
#define F_CPU 8000000UL
#include <util/delay.h>


int main(void)
{
	CLEARBIT(DDRD,0);
	CLEARBIT(PORTD,0);
	SETBIT(DDRD,4);
    while (1) 
    {
		if ((READBIT(PIND,0))== 1)
		{
			
			SETBIT(PORTD,4);
			_delay_ms(1000);
			CLEARBIT(PORTD,4);
			
		}
    }
}

