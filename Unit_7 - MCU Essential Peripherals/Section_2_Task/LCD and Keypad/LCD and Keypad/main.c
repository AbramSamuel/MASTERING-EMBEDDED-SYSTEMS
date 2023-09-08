/*
 * LCD and Keypad.c
 *
 * Created: 8/7/2023 6:24:50 PM
 * Author : ABRAM
 */ 

#include "HAL\LCD\lcd.h"
#include "HAL\KEYPAD\keypad.h"


int main(void)
{
    /* Replace with your application code */
	LCD_INIT();
	KEYPAD_INIT();
	
	char pressed_key;
    while (1) 
    {
		pressed_key = KEYPAD_GET_CHAR();
		
		switch(pressed_key)
		{
			case '?':
				LCD_clear_screen();
				break;
			case 'N':
				break;
			default:
				LCD_WRITE_CHAR(pressed_key);
		}
    }
}

