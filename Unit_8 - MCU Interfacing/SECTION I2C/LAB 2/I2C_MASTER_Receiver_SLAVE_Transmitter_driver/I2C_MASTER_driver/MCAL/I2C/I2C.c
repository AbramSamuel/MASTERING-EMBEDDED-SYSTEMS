/*
 * I2C.c
 *
 * Created: 10/21/2023 6:45:55 PM
 *  Author: ABRAM
 */ 

#include "I2C.h"
#define PRESCALER 1  //1 ,2,4,16,64

void I2C_INIT(unsigned long SCL_Clock)
{
	TWBR = (unsigned char) (((F_CPU/SCL_Clock)-16)/(2*PRESCALER));
	
	if (PRESCALER ==0)
	TWSR =0;
	
	else if (PRESCALER ==4)
	{
		TWSR =1;
	}
	else if (PRESCALER ==16)
	{
		TWSR =2;
	}
	else if (PRESCALER ==64)
	{
		TWSR =3;
	}
	
}
void I2C_STATR(void)
{

	TWCR =(1<<TWINT) | (1<<TWSTA) | (1<<TWEN) ;
	while (((TWCR &(1<<7))==0));                 // wait to finish
	while ((TWSR)!=0x08);                   //Start Condition has Been Transmitted
	
}
void I2C_WRITE(unsigned char cData)
{
	TWDR = cData;
	TWCR =(1<<TWINT) | (1<<TWEN) ;
	while ((TWCR & 0x80)==0);               //wait to finish
}

unsigned char I2C_READ(unsigned char ACK)
{
	TWCR =(1<<TWINT) | (1<<TWEA) | (1<<TWEN) ;
	while ((TWCR & 0x80)==0);               //wait to finish
	return TWDR;
}

void I2C_STOP()
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	
}