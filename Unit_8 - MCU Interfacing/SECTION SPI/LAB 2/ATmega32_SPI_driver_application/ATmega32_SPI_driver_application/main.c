/*
 * ATmega32_SPI_driver_application.c
 *
 * Created: 10/20/2023 2:05:32 PM
 * Author : ABRAM
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#define SS 4
#define MOSI 5
#define SCK 7


void SPI_Master_Init()
{
	/* Set MOSI, SCK and SS output*/
	DDRB |= (1 << MOSI) | (1 << SS) | (1 << SCK);
	
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR |= (1 << MSTR) | (1 << SPE) | (1 << SPR0);
}

void execute(unsigned char cmd , unsigned char data)
{
	PORTB &=~(1<<SS);
	SPDR = cmd;
	while (!(SPSR &(1<<SPIF)));
	SPDR = data;
	while (!(SPSR &(1<<SPIF)));
	PORTB |= (1<<SS);
	
	
}
int main(void)
{
	unsigned int counter =0;
	unsigned index =1; 
	SPI_Master_Init();
    execute(0x09,0xFF);
	execute(0x0A,0x0F);
	execute(0x0B,0x07);
	execute(0x0C,0x01);
    while (1) 
    {
		for (index =1 ; index<9;index++)
		{
			execute(index,counter++);
		}
		_delay_ms(1000);
    }
}

