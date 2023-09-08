/*
 * lcd.c
 *
 * Created: 8/7/2023 6:44:15 PM
 *  Author: ABRAM
 */ 

#include "lcd.h"



void LCD_KICK()
{
	CLEARBIT(LCD_CTRL,EN);
	_delay_ms(50);
	SETBIT(LCD_CTRL,EN);
}

void LCD_CHECK_ISBUSY()
{
	DataDir_LCD_Port &= ~(0xFF<<DATA_shift);
	 SETBIT(LCD_CTRL,RW); //read mode
	 CLEARBIT(LCD_CTRL,RS);
	 LCD_KICK();
	DataDir_LCD_Port |= (0xFF<<DATA_shift);
	 CLEARBIT(LCD_CTRL,RW);//write
	
}



void LCD_INIT()
{
	_delay_ms(20);
	DataDir_LCD_CTRL |= (1<<EN | 1<<RS | 1<<RW);
	LCD_CTRL &= ~ (1<<EN | 1<<RS | 1<<RW);
	DataDir_LCD_Port = 0xFF;
	_delay_ms(15);
	LCD_clear_screen();
	#ifdef EIGHT_BIT_MODE
	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	#endif
	#ifdef FOUR_BIT_MODE
		//LCD_WRITE_COMMAND(0x02);		/* send for 4 bit initialization of LCD  */
		//LCD_WRITE_COMMAND(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
		//LCD_WRITE_COMMAND(0x0c);              /* Display on cursor off*/
		//LCD_WRITE_COMMAND(0x06);              /* Increment cursor (shift cursor to right)*/
		//LCD_WRITE_COMMAND(0x01);
	LCD_WRITE_COMMAND(0x02);
	LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
	#endif
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);	
}




void LCD_WRITE_COMMAND(unsigned char command)
{
	
	#ifdef EIGHT_BIT_MODE
		LCD_CHECK_ISBUSY();
		LCD_Port = command;
		LCD_CTRL &= ~(1<<RS |1<<RW);
		_delay_ms(1);
		LCD_KICK();

	#endif
	
	#ifdef FOUR_BIT_MODE
		LCD_CHECK_ISBUSY();
		LCD_Port =(LCD_Port & 0x0F) | (command & 0xF0);
		LCD_CTRL &= ~((1<<RS) |(1<<RW));
		LCD_KICK();
		LCD_Port =(LCD_Port & 0x0F) | (command <<4);
		LCD_CTRL &= ~((1<<RS )|(1<<RW));
		LCD_KICK();

	#endif
	
}
void LCD_WRITE_CHAR(unsigned char character)
{
	
	#ifdef EIGHT_BIT_MODE
		LCD_CHECK_ISBUSY();

		SETBIT(LCD_CTRL,RS);
		LCD_Port = character;
		CLEARBIT(LCD_CTRL,RW);
		SETBIT(LCD_CTRL,RS);
		LCD_KICK();

	#endif
	
	#ifdef FOUR_BIT_MODE
		//LCD_CHECK_ISBUSY();

		LCD_Port =(LCD_Port & 0x0F) | (character & 0xF0);
		SETBIT(LCD_CTRL,RS);
		CLEARBIT(LCD_CTRL,RW);
		_delay_ms(1);
		LCD_KICK();
		LCD_Port =(LCD_Port & 0x0F) | (character<<4);
		SETBIT(LCD_CTRL,RS);
		CLEARBIT(LCD_CTRL,RW);
		_delay_ms(1);
		LCD_KICK();
#endif
	
}
void LCD_WRITE_STRING(char* string)
{
	unsigned int count =0;
	while(*string >0)
	{
		count++;
		LCD_WRITE_CHAR(*string++);
		if (count==16)
		{
			LCD_GOTO_XY(1,0);
		}
		else if (count==32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(0,0);
			count =0;
		}
	}
}

void LCD_clear_screen()
{
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
	
}
void LCD_GOTO_XY(unsigned char line, unsigned char position)
{
	if (line == 0)
	{
		if(position <16 && position>=0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW+position);
		}
	}
	else if (line==1)
	{
		if (position <16 && position>=0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW+position);
		}
	}
}

void LCD_DISPLAY_NUMBER(unsigned int number)
{
	char str[7];
	printf(str,"d",number);
	LCD_WRITE_STRING(str);
	
}


void LCD_DISPLAY_REAL_NUMBER(double number)
{

	char str[16];
	char* sign=(number<0) ? "-":"";//sign of the number
	float val =(number<0) ? -number:number;
	
	int integer_part= val;
	float fraction_part =integer_part-val; 
	int fraction_convert = fraction_part *100000;
	printf(str,"%s%d.%04d",sign,integer_part,fraction_convert);
	
	LCD_WRITE_STRING(str);
	 
}