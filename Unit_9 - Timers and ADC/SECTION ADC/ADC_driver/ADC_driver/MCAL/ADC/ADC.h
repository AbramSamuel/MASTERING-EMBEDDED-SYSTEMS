/*
 * ADC.h
 *
 * Created: 11/4/2023 6:38:07 PM
 *  Author: ABRAM
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "..\..\UTILITIES\BIT_MATH.h"
#include "..\..\UTILITIES\CPU_CONFIGURATION.h"
#include "..\..\UTILITIES\STD_TYPES.h"

#define VREF		50000
#define RESOLUTION	1024
typedef enum
 {
	 VREF_AREF,
	 VERF_AVCC,
	 VREF_256V
	
}ADC_VREF_type;

typedef enum
{
	ADC_SCALER_2,
	ADC_SCALER_4,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128
}ADC_SCALER_type;

typedef enum
{
	CH_0=0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7
	
	}ADC_CHANNEL_type;


void ADC_INIT(ADC_VREF_type vref, ADC_SCALER_type scaler);

Uint16t ADC_READ(ADC_CHANNEL_type CH);


#endif /* ADC_H_ */