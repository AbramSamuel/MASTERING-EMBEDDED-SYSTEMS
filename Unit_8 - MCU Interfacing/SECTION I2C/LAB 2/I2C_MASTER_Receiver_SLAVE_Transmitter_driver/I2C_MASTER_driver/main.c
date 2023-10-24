/*
 * I2C_MASTER_driver.c
 *
 * Created: 10/21/2023 6:44:09 PM
 * Author : ABRAM
 */ 

#include "MCAL/I2C/I2C.h"


int main(void)
{
    /* Replace with your application code */
	unsigned char ch;
	DDRA = 0xFF;
	I2C_INIT(0x48);
    while (1) 
    {
		_delay_ms(1000);
		I2C_STATR();					//Transmit Start Condition
		I2C_WRITE(0b11010000+1);		//Transmit  SLA + R(1)
		ch =I2C_READ(0);				//read the last byte and send NACK		
		I2C_STOP();						//Transmit Stop condition
		PORTA = ch;
    }
}

