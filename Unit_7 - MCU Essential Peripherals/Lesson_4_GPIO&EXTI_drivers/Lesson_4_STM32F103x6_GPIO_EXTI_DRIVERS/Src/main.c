/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include "STM32F103xx6.h"
#include "STM32F103C6_EXTI_DRIVER.h"
#include "STM32F103C6_GPIO_DRIVER.h"


unsigned int IRQ_Flag ;

void EXTI9_callback()
{
	IRQ_Flag= 1;
	LCD_WRITE_STRING("IRQ EXTI9 IS HAPPENED _|-");
	wait(1000);


}
int main(void)
{
	//enable clock
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();

	LCD_INIT();
	LCD_clear_screen();
	EXTI_PinConfig_t EXTI_CFG;
	EXTI_CFG.EXTI_Pin= EXTI9PB9;
	EXTI_CFG.trigger_status = EXTI_TRIGGER_RISING;
	EXTI_CFG.P_IRQ_CallBack = EXTI9_callback;
	EXTI_CFG.IRQ_EN = EXTI_IRQ_ENABLE;
	MCAL_EXTI_GPIO_INIT(&EXTI_CFG);

	IRQ_Flag =1;
/* Loop forever */
	while(1)
	{
		if (IRQ_Flag) {
			LCD_clear_screen();
			IRQ_Flag =0;
		}

		wait(1000);
	}


}
