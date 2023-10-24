/*
 * I2C.h
 *
 * Created: 10/21/2023 6:46:07 PM
 *  Author: ABRAM
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "..\DIO\DIO.h"

void I2C_INIT(unsigned long SCL_Clock);
void I2C_STATR(void);
void I2C_WRITE(unsigned char cData);
unsigned char I2C_READ(unsigned char ACK);
void I2C_STOP();


#endif /* I2C_H_ */