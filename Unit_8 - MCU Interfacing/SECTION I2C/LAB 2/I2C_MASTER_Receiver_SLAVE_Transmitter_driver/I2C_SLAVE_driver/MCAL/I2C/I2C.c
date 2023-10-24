/*
 * I2C.c
 *
 * Created: 10/21/2023 6:45:55 PM
 *  Author: ABRAM
 */ 

#include "I2C.h"
#define PRESCALER 1  //1 ,2,4,16,64

void I2C_SET_ADDRESS(unsigned char address)
{
	TWAR = address;
}
unsigned char I2C_READ(unsigned char ACK)
{
	unsigned char x=0;
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while ((TWCR & 0x80)==0);               //wait to finish

	
}

void I2C_WRITE(unsigned char cData)
{
	TWDR = cData;
	TWCR =(1<<TWINT)|(1<<TWEN) ;
	while ((TWCR & 0x80)==0);               //wait to finish
}
