/*
 * ADC.c
 *
 * Created: 11/4/2023 6:37:57 PM
 *  Author: ABRAM
 */ 

#include "ADC.h"

void ADC_INIT(ADC_VREF_type vref, ADC_SCALER_type scaler)
{
	//VREF
	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		
		case VERF_AVCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		
		case VREF_256V:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
		
	}
	
	//PRESCALER
	//ENABLE ADC
	SET_BIT(ADCSRA,ADEN);
	//enable all interrupts
	ADCSRA &= 0xF8;
	//select ADC prescaler
	ADCSRA |= scaler;	
	
	
}

Uint16t ADC_READ(ADC_CHANNEL_type CH)
{
	//SELECT CHANNEL
	ADMUX |=CH;
	
	//START CONVERSION
	SET_BIT(ADCSRA,ADSC);
	while(GET_BIT(ADCSRA,ADSC));
	return ADC;
}