/*
 * ADC_driver.c
 *
 * Created: 11/4/2023 6:35:11 PM
 * Author : ABRAM
 */ 

#include ".\HAL\LCD\lcd.h"
#include ".\MCAL\ADC\ADC.h"
#include ".\MCAL\DIO\DIO.h"


int main(void)
{
	
    
    Uint16t data;
    Uint16t pre_value;
	

    ADC_INIT(VERF_AVCC , ADC_SCALER_64);
    LCD_INIT();			/* Initialization of LCD */
    LCD_GOTO_XY(1,0);
    LCD_WRITE_STRING("ADC value :    ");	/* Write string on 1st line of LCD */
    LCD_GOTO_XY(2,0);
    LCD_WRITE_STRING("Per value :    %");	/* Write string on 1st line of LCD */
    

    while(1)
    {
	    
	    LCD_GOTO_XY(1,12);				// LCD16x2 cursor position
	    data=ADC_READ(CH_7);			// Read ADC channel 0
	    LCD_DISPLAY_NUMBER(data);
	    if(data < 1000)
	    {
		    LCD_GOTO_XY(1,15);
		    LCD_WRITE_CHAR(' ');
	    }
	    
	    LCD_GOTO_XY(2,12);
	    pre_value = ((Uint32t)ADC_READ(CH_7) / 1023.0) * 100.0;
	    LCD_DISPLAY_NUMBER(pre_value);
	    if(pre_value < 100)
	    {
		    LCD_GOTO_XY(2,14);
		    LCD_WRITE_CHAR(' ');
	    }
    }
    return 0;
}

