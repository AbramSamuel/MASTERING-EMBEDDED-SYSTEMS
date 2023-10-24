/*
 * I2C.h
 *
 * Created: 10/21/2023 6:46:07 PM
 *  Author: ABRAM
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "..\DIO\DIO.h"
#include "..\DIO\DIO_CONFIG.h"

void I2C_SET_ADDRESS(unsigned char address);
unsigned char I2C_READ(unsigned char ACK);
void I2C_WRITE(unsigned char cData);


#endif /* I2C_H_ */