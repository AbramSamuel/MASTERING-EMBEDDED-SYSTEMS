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
	unsigned char ch =0;
	I2C_INIT(0x48);
    while (1) 
    {
		_delay_ms(500);
		I2C_STATR();					//Transmit Start Condition
		I2C_WRITE(0b11010000+0);		//Transmit  SLA + W(0)
		while ((TWSR) != 0x18);         //SLA + W(0) has been transmitted and ACK has been Received
		I2C_WRITE(ch++);				// Transmit Data
		while(TWSR != 0x28);			//Data has been transmitted and ACK has been Received
		I2C_STOP();						//Transmit Stop condition
    }
}

