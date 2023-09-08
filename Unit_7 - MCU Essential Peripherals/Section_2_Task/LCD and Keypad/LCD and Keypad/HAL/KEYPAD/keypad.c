/*
 * keypad.c
 *
 * Created: 8/8/2023 2:34:58 PM
 *  Author: ABRAM
 */ 

#include "keypad.h"


int KEYPAD_Row[] = {R0, R1, R2, R3}; //rows of the keypad
int KEYPAD_Col[] = {C0, C1, C2, C3};//columns
	
void KEYPAD_INIT()
{
	//rows as input
	DataDir_KEYPAD_PORT &=~((1<<R0) | ( 1<<R1) | (1<<R2) | (1<<R3));
	//columns as output
	DataDir_KEYPAD_PORT |=((1<<C0) | (1<<C1) |( 1<<C2) |(1<<C3));
	
	KEYPAD_PORT =0xFF;
}
char KEYPAD_GET_CHAR()
{
	unsigned int i,j;
	for (i=0 ; i<4;i++)
	{
		KEYPAD_PORT |=((1<<KEYPAD_Col[0]) | (1<<KEYPAD_Col[1]) | (1<<KEYPAD_Col[2]) | (1<<KEYPAD_Col[3]));
		
		KEYPAD_PORT &= ~(1<<KEYPAD_Col[i]);
		
		for (j=0;j<4;j++)
		{
			if (!(KEYPAD_PIN &(1<<KEYPAD_Row[j]))) //check if the key is pressed 
			{
				while (!(KEYPAD_PIN &(1<<KEYPAD_Row[j]))); //wait for key to  be released (single press)
				
				switch(i)
				{
					case 0:
					if(j==0) return '7';
					else if(j==1) return '4';
					else if(j==2)	return '1';
					else if(j==3) return '?';
					break;
					
					case 1:
					if(j==0) return '8';
					else if(j==1) return '5';
					else if(j==2)	return '2';
					else if(j==3) return '0';
					break;
					
					case 2:
					if(j==0) return '9';
					else if(j==1) return '6';
					else if(j==2)	return '3';
					else if(j==3) return '=';
					break;
					
					case 3:
					if(j==0) return '/';
					else if(j==1) return '*';
					else if(j==2)	return '-';
					else if(j==3) return '+';
					break;
				}
			}
			
		}
		
	}
	return 'N';
}