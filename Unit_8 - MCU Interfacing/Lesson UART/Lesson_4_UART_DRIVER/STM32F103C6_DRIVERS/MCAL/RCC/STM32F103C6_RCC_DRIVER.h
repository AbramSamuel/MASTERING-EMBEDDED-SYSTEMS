/*
 * STM32F103C6_RCC_DRIVER.h
 *
 *  Created on: Oct 3, 2023
 *      Author: ABRAM
 */

#ifndef MCAL_RCC_STM32F103C6_RCC_DRIVER_H_
#define MCAL_RCC_STM32F103C6_RCC_DRIVER_H_

#include "STM32F103xx6.h"
#include "STM32F103C6_GPIO_DRIVER.h"


#define HSI_RC_CLK			(uint32_t)8000000
#define HSE_CLK				(uint32_t)16000000

/*
 * ======================================================================
 * 			APIs Supported by "MCAL RCC DRIVER"
 * ======================================================================
 */

uint32_t MCAL_RCC_GetSYSCLKFreq(void);

uint32_t MCAL_RCC_GetHCLKFreq(void);

uint32_t MCAL_RCC_GetPCLK1Freq(void);

uint32_t MCAL_RCC_GetPCLK2Freq(void);


#endif /* MCAL_RCC_STM32F103C6_RCC_DRIVER_H_ */
