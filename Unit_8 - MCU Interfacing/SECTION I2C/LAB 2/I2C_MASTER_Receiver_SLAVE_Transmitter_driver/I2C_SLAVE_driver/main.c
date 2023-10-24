/*
 * I2C_SLAVE_driver.c
 *
 * Created: 10/21/2023 6:44:49 PM
 * Author : ABRAM
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	unsigned char ch = 0;
	I2C_SET_ADDRESS(0b11010000);	//Enable slave at address 01101000 
    while (1) 
    {
		I2C_READ(1);		// Receive Byte and send ACK
		I2C_WRITE(ch++);		//SLA(1001100)+R(1)
    }
	return 0;
}

