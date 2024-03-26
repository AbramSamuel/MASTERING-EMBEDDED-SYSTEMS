/*
 * STM32F103C6_RCC_DRIVER.c
 *
 *  Created on: Oct 3, 2023
 *      Author: ABRAM
 */

#include "STM32F103C6_RCC_DRIVER.h"


//Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
//Set and cleared by software to control the division factor of the APB low-speed clock
//(PCLK1).
//Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
//0xx: HCLK not divided
//100: HCLK divided by 2
//101: HCLK divided by 4
//110: HCLK divided by 8
//111: HCLK divided by 16


const uint8_t APBprescaler_Table[8] = {0, 0, 0, 0, 1, 2, 3, 4};
const uint8_t AHBprescaler_Table[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

uint32_t MCAL_RCC_GetSYSCLKFreq(void)
{
	switch((RCC->CFGR >> 2) & 0b11)
	{
	case 0:
		return HSI_RC_CLK;
		break;

	case 1:
		return HSE_CLK;		//we should know the frequency of the external clock --> To Do
		break;

	case 2:
		return 16000000;	//we should calculate PLLCLK and PLLMUL to get this value --> To Do
		break;
	}

//	Bits 3:2 SWS: System clock switch status
//	Set and cleared by hardware to indicate which clock source is used as system clock.
//	00: HSI oscillator used as system clock
//	01: HSE oscillator used as system clock
//	10: PLL used as system clock
//	11: not applicable
}

uint32_t MCAL_RCC_GetHCLKFreq(void)
{
	return MCAL_RCC_GetSYSCLKFreq() >> AHBprescaler_Table[((RCC->CFGR >> 4) & 0xF)];

//	Bits 7:4 HPRE: AHB prescaler
//	Set and cleared by software to control the division factor of the AHB clock.
//	0xxx: SYSCLK not divided
//	1000: SYSCLK divided by 2
//	1001: SYSCLK divided by 4
//	1010: SYSCLK divided by 8
//	1011: SYSCLK divided by 16
//	1100: SYSCLK divided by 64
//	1101: SYSCLK divided by 128
//	1110: SYSCLK divided by 256
//	1111: SYSCLK divided by 512
}

uint32_t MCAL_RCC_GetPCLK1Freq(void)
{
	return (MCAL_RCC_GetHCLKFreq() >> APBprescaler_Table[((RCC->CFGR >> 8) & (0b111))]);

//	Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
//	Set and cleared by software to control the division factor of the APB low-speed clock
//	(PCLK1).
//	Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
//	0xx: HCLK not divided
//	100: HCLK divided by 2
//	101: HCLK divided by 4
//	110: HCLK divided by 8
//	111: HCLK divided by 16
}

uint32_t MCAL_RCC_GetPCLK2Freq(void)
{
	return (MCAL_RCC_GetHCLKFreq() >> APBprescaler_Table[((RCC->CFGR >> 11) & (0b111))]);

//	Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
//	Set and cleared by software to control the division factor of the APB high-speed clock
//	(PCLK2).
//	0xx: HCLK not divided
//	100: HCLK divided by 2
//	101: HCLK divided by 4
//	110: HCLK divided by 8
//	111: HCLK divided by 16
}
