/*
 * ATmega32_SPI_SLAVE_driver.c
 *
 * Created: 10/19/2023 9:40:42 PM
 * Author : ABRAM
 */ 

#define  F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define  SS		4
#define  MOSI	5
#define  MISO   6
#define	 SCK	7


void SPI_MASTER_INIT()
{
	DDRB |= (1<<SS) | (1<<MOSI) | (1<<SCK);
	DDRB &= ~(MISO);
	SPCR |= (1<<SPE) | (1<<MSTR) |(1<<SPR0);
	
	
}

unsigned char SPI_MASTER_SEND(unsigned char data)
{
	SPDR = data;
	while(!(SPSR &(1<<SPIF)));
	return SPDR;
	
}


int main(void)
{
	unsigned char x;
	DDRA = 0xFF;
	SPI_MASTER_INIT();

	for (x =255 ;x>0;x--)
	{
		_delay_ms(500);
		PORTA = SPI_MASTER_SEND(x);
	}
}

