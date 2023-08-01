/*
 * Task_2.c
 *
 * Created: 8/1/2023 4:46:31 PM
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
	
	//set bits 5,6,7 as output
	SETBIT(DDRD,5);
	SETBIT(DDRD,6);
	SETBIT(DDRD,7);
	
	unsigned char counter=0;
    while (1) 
    {
		
		if ((READBIT(PIND,0)) == 1)
		{
			counter++;
			switch(counter)
			{
				case 1:
					SETBIT(PORTD,5);
					_delay_ms(50);
					CLEARBIT(PORTD,6);
					CLEARBIT(PORTD,7);
					break;
				
				case 2:
					SETBIT(PORTD,5);
					_delay_ms(50);
					SETBIT(PORTD,6);
					_delay_ms(50);
					CLEARBIT(PORTD,7);
					break;
					
				case 3:
					SETBIT(PORTD,5);
					_delay_ms(50);
					SETBIT(PORTD,6);
					_delay_ms(50);
					SETBIT(PORTD,7);
					break;
					
				case 4:
					CLEARBIT(PORTD,7);
					break;
					
				case 5:
					CLEARBIT(PORTD,6);
					break;
					
				case 6:
					CLEARBIT(PORTD,5);
					break;
					
				default:
					PORTD=0x0;
					counter=0;
				
			}
			while(READBIT(PIND,0)==1);
		}
		_delay_ms(500);
    }
	
	
}

