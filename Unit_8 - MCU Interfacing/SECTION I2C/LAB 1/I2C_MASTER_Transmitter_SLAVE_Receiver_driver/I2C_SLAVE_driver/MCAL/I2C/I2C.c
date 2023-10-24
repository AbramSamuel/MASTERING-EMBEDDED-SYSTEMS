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
	while ((TWCR & 1<<7) == 0);
	while ((TWSR) != 0x60) x = TWSR;             // own SLA+W(0) has been transmitted and ACK has been returned
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while ((TWCR & 1<<7) == 0);
	while ((TWSR) != 0x80) x = TWSR;          // Data has been transmitted and ACK has been returned
	return TWDR;

	
}