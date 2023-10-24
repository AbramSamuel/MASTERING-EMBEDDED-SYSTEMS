/*
 * USART.c
 *
 * Created: 10/17/2023 7:39:47 PM
 *  Author: ABRAM
 */ 
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART.h"




void USART_INIT()
{
	//CONFIGURATIONS
	//1-frame
	//NO parity initial value by default
	// 8 bits data is initial value by default
	
	//2-Baudrate
	 UBRRL= 51;	
	 CLEARBIT(UCSRA,U2X);
	 
	//3-Enable 
	SETBIT(UCSRB,RXEN);
	SETBIT(UCSRB,TXEN);
}


void USART_SEND(u8 data)
{
	while (!(READBIT(UCSRA,UDRE)));
	UDR = data;
	
}
u8 USART_RECEIVE(void)
{
	while (!(READBIT(UCSRA,RXC)));
	
	return UDR;
	
}


void USART_SEND_NUMBER_U32(u32 num)
{
	u8 *p = &num;
	USART_SEND(p[0]);
	USART_SEND(p[1]);
	USART_SEND(p[2]);
	USART_SEND(p[3]);
}


u32 USART_RECEIVE_NUMBER_U32(void)
{
	
	u32 num;
	u8* p = &num;
	p[0] = USART_RECEIVE();
	p[1] = USART_RECEIVE();
	p[2] = USART_RECEIVE();
	p[3] = USART_RECEIVE();
	return num;
	
}

void USART_SEND_STRING(u8*str)
{
	u8 i ;
	for (i=0 ; i<str[i];i++)
	{
		USART_SEND(str[i]);
	}
	USART_SEND(DefaultStop);
}



void USART_RECEIVE_STRING(u8*buff)
{
u8 i;
	i=0;
	buff[i]=USART_RECEIVE();
	while(buff[i] != DefaultStop)
	{
		i++;
		buff[i]=USART_RECEIVE();
	}
	
	buff[i] = '\0';
}

