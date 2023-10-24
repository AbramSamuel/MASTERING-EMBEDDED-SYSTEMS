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
	DDRA= 0xFF;
	I2C_SET_ADDRESS(0b11010000);	//Enable slave at address 01101000 and Don't accept general call
    while (1) 
    {
		PORTA = I2C_READ(1);		// Receive Byte and send ACK
    }
	return 0;
}

