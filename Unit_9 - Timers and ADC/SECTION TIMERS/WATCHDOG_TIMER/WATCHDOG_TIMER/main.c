/*
 * WATCHDOG_TIMER.c
 *
 * Created: 10/28/2023 2:01:57 PM
 * Author : ABRAM
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SET_BIT(PORT, BIT)			PORT |= (1<< BIT)
#define RESET_BIT(PORT, BIT)		PORT &= ~(1<<BIT)
#define TOG_BIT(PORT, BIT)			PORT ^= (1<<BIT)
#define GET_BIT(PORT, BIT)			PORT & (1<<BIT)

#define LED_DDR	 DDRD
#define LED_PORT PORTD

void WDT_OFF()
{
	WDTCR |= (1<<WDTOE) | (1<<WDE);
	WDTCR = 0x00;
}

void WDT_ON()
{
	WDTCR |= (1<<WDE) | (1<<WDP0) | (1<<WDP1) | (1<<WDP2); //Typical Time-out 2.2s

}

int main(void)
{
    /* Replace with your application code */
	
	SET_BIT(LED_DDR,6); //PIN 6 as output
    while (1) 
    {
		WDT_ON();
		_delay_ms(2000);
		TOG_BIT(LED_PORT,6);
		WDT_OFF();
		
    }
}

