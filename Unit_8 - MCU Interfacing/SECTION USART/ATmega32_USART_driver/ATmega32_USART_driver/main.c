/*
 * ATmega32_USART_driver.c
 *
 * Created: 10/17/2023 7:35:48 PM
 * Author : ABRAM
 */ 

#define F_CPU 8000000UL
#include "MCAL/USART/USART.h"
#include "MCAL/DIO/DIO.h"
#include "HAL/LCD/lcd.h"

int main(void)
{
	u8 x[100];
	DIO_setPortDirection(PORTA,DIO_PIN_INPUT);

	LCD_INIT();
	USART_INIT();
	LCD_WRITE_STRING("USART TR");
	LCD_GOTO_XY(0,0);
	USART_SEND_STRING("ABRAM");
	
    /* Replace with your application code */
    while (1) 
    {
		USART_RECEIVE_STRING(x);
		LCD_WRITE_STRING(x);
			}
}

