/*
 * DIO.c
 *
 * Created: 10/17/2023 7:39:32 PM
 *  Author: ABRAM
 */ 

/* MCAL */
#include "DIO.h"

/* PINS APIS*/

void DIO_setPinDirection(u8 PortId, u8 PinId , u8 PinDirection )

{
	if ( (PortId<=3) && (PinId<=7) && ((PinDirection == DIO_PIN_OUTPUT ) || (PinDirection == DIO_PIN_INPUT)) )
	{
		switch (PortId)  // DIO PORTA
		{
			case 0 :
			if (DIO_PIN_OUTPUT == PinDirection)
			{
				SETBIT(DDRA,PinId);
			}
			else
			{
				CLEARBIT(DDRA,PinId);
			}
			break ;
			
			case 1 : // DIO PORTB
			if (DIO_PIN_OUTPUT == PinDirection)
			{
				SETBIT(DDRB,PinId);
			}
			else
			{
				CLEARBIT(DDRB,PinId);
			}
			break ;
			
			case 2 : // DIO PORTC
			if (DIO_PIN_OUTPUT == PinDirection)
			{
				SETBIT(DDRC,PinId);
			}
			else
			{
				CLEARBIT(DDRC,PinId);
			}
			break ;
			
			case 3 : // DIO PORTD
			if (DIO_PIN_OUTPUT == PinDirection)
			{
				SETBIT(DDRD,PinId);
			}
			else
			{
				CLEARBIT(DDRD,PinId);
			}
			break ;
		}
	}
}

void DIO_setPinValue(u8 PortId, u8 PinId , u8 PinValue)

{
	if ( (PortId<=3) && (PinId<=7) && ((PinValue == DIO_PIN_HIGH ) || (PinValue == DIO_PIN_LOW)) )
	{
		switch (PortId)
		{
			case 0 : // DIO_PORTA
			if (DIO_PIN_HIGH==PinValue)
			{
				SETBIT(PORTA,PinId);
			}
			else
			{
				CLEARBIT(PORTA,PinId) ;
			}
			break ;
			
			case 1 : // DIO_PORTB
			if (DIO_PIN_HIGH==PinValue)
			{
				SETBIT(PORTB,PinId);
			}
			else
			{
				CLEARBIT(PORTB,PinId) ;
			}
			break ;
			
			case 2 : // DIO_PORTC
			if (DIO_PIN_HIGH==PinValue)
			{
				SETBIT(PORTC,PinId);
			}
			else
			{
				CLEARBIT(PORTC,PinId) ;
			}
			break ;
			
			case 3 : // DIO_PORTD
			if (DIO_PIN_HIGH==PinValue)
			{
				SETBIT(PORTD,PinId);
			}
			else
			{
				CLEARBIT(PORTD,PinId) ;
			}
			break ;
		}
	}
}

void DIO_getPinValue(u8 PortId, u8 PinId , u8* PinValue)

{
	if ( (PortId<=3) && (PinId<=7) && (PinValue != NULL ) )
	{
		
		switch (PortId)
		{
			case 0 : // DIO_PORTA
			if ( DIO_PIN_HIGH == READBIT(PINA,PinId) )
			{
				*PinValue = DIO_PIN_HIGH ;
			}
			else
			{
				*PinValue = DIO_PIN_LOW;
			}
			break ;
			
			
			case 1 : // DIO_PORTB
			if ( DIO_PIN_HIGH == READBIT(PINB,PinId) )
			{
				*PinValue = DIO_PIN_HIGH ;
			}
			else
			{
				*PinValue = DIO_PIN_LOW;
			}
			break ;
			
			
			
			case 2 : // DIO_PORTC
			if ( DIO_PIN_HIGH == READBIT(PINC,PinId) )
			{
				*PinValue = DIO_PIN_HIGH ;
			}
			else
			{
				*PinValue = DIO_PIN_LOW;
			}
			break ;
			
			
			
			case 3 : // DIO_PORTD
			if ( DIO_PIN_HIGH == READBIT(PIND,PinId) )
			{
				*PinValue = DIO_PIN_HIGH ;
			}
			else
			{
				*PinValue = DIO_PIN_LOW ;
			}
			break ;
		}
		
	}
}

void DIO_togglePinValue(u8 PortId, u8 PinId)

{
	
	if ( (PortId<=3) && (PinId<=7) )
	{
		switch (PortId )
		{
			case 0 : // DIO_PORTA
			
			TOGGLEBIT(PORTA,PinId) ;
			
			break ;
			
			case 1 : // DIO_PORTB
			
			TOGGLEBIT(PORTB,PinId) ;
			
			break ;
			
			case 2 : // DIO_PORTC
			
			TOGGLEBIT(PORTC,PinId) ;
			
			break ;
			
			case 3 : // DIO_PORTD
			
			TOGGLEBIT(PORTD,PinId) ;
			
			break ;
		}
	}
	
}

/* PORTS APIS*/
void DIO_setPortDirection(u8 PortId , u8 PortDirection )

{
	if ( (PortId<=3) && ( (DIO_PORT_INPUT == PortDirection) || (DIO_PORT_OUTPUT == PortDirection) ) )
	{
		switch (PortId)
		{
			case 0 : // PORTA
			if (DIO_PORT_OUTPUT == PortDirection)
			{
				DDRA = 0xff ;
			}
			else
			{
				DDRA = 0x00 ;
			}
			break ;
			
			case 1: // PORTB
			if (DIO_PORT_OUTPUT == PortDirection)
			{
				DDRB= 0xff ;
			}
			else
			{
				DDRB = 0x00 ;
			}
			break ;
			
			case 2 : // PORTC
			if (DIO_PORT_OUTPUT == PortDirection)
			{
				DDRC = 0xff ;
			}
			else
			{
				DDRC = 0x00 ;
			}
			break ;
			
			case 3 : // PORTD
			if (DIO_PORT_OUTPUT == PortDirection)
			{
				DDRD = 0xff ;
			}
			else
			{
				DDRD = 0x00 ;
			}
			break ;
		}
	}
	
}

void DIO_setPortValue(u8 PortId , u8 PortValue)

{
	if (PortId<=3)
	{
		switch (PortId)
		{
			case 0 : // PORTA
			PORTA = PortValue ;
			break ;
			
			case 1 : // PORTB
			PORTB = PortValue ;
			break ;
			
			case 2 : // PORTC
			PORTC = PortValue ;
			break ;
			
			case 3 : // PORTD
			PORTD = PortValue ;
			break ;
		}
	}
}

void DIO_getPortValue(u8 PortId , u8* PortValue)

{
	if ( (PortId<=3) && (PortValue != NULL) )
	{
		switch (PortId)
		{
			case 0 : // PORTA
			*PortValue = PINA ;
			break ;

			case 1 : // PORTB
			*PortValue = PINB ;
			break ;

			case 2 : // PORTC
			*PortValue = PINC ;
			break ;

			case 3 : // PORTD
			*PortValue = PIND ;
			break ;

		}
	}
}

void DIO_togglePortValue(u8 PortId )

{
	if (PortId<=3)
	{
		switch (PortId)
		{
			case 0 : // PORTA
			PORTA = ~PORTA ;
			break;
			
			case 1 : // PORTB
			PORTB = ~PORTB ;
			break;
			
			case 2 : // PORTC
			PORTC = ~PORTC ;
			break;
			
			case 3 : // PORTD
			PORTD = ~PORTD ;
			break;
		}
	}
}

void DIO_setInputPinResistance (u8 PortId, u8 PinId)

{
	if ( (PortId<=3) && (PinId<=7) )
	{
		switch (PortId)
		{
			case 0 :
			SETBIT(PORTA,PinId);
			break ;

			case 1 :
			SETBIT(PORTB,PinId);
			break ;

			case 2 :
			SETBIT(PORTC,PinId);
			break ;

			case 3 :
			SETBIT(PORTD,PinId);
			break ;
		}
	}
}

void DIO_setInputPortResistance (u8 PortId)

{
	if ( PortId<=3 )
	{
		switch (PortId)
		{
			
			case 0 :
			PORTA = 0xff ;
			break ;
			
			case 1 :
			PORTB = 0xff ;
			break ;
			
			case 2 :
			PORTC = 0xff ;
			break ;
			
			case 3 :
			PORTD = 0xff ;
			break ;
		}
	}
}