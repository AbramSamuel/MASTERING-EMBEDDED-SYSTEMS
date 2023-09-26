/*
 * STM32F103C6_EXTI_DRIVER.c
 *
 *  Created on: Sep 23, 2023
 *      Author: ABRAM
 */



#include "STM32F103xx6.h"
#include "STM32F103C6_EXTI_DRIVER.h"
#include "STM32F103C6_GPIO_DRIVER.h"



//================================================================
//							GERNERIC VARIABLES
//================================================================

void (* P_IRQ_CallBack[15])(void);

//================================================================
//							GERNERIC MACROS
//================================================================

#define AFIO_GPIO_EXTI_MAPPING(x)		   ((x==GPIOA)?0: \
		(x==GPIOB)?1: \
				(x==GPIOC)?2: \
						(x==GPIOD)?3:0)


//================================================================
//							GERNERIC FUNCTIONS
//================================================================


void NVIC_ENABLE(uint16_t IRQ)
{
	switch (IRQ) {
	case 0:
		NVIC_IRQ6_EXTI0_Enable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Enable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Enable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Enable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Enable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Enable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Enable;
		break;
	default:
		break;
	}
}



void NVIC_DISABLE(uint16_t IRQ)
{
	switch (IRQ) {
	case 0:
		NVIC_IRQ6_EXTI0_Disable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Disable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Disable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Disable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Disable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Disable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Disable;
		break;
	default:
		break;
	}


}
void UPDATE_EXTI(EXTI_PinConfig_t* EXTI_Config)
{
	//1-configure AF input to input floating
	GPIO_PinConfig_t PinCfg;
	//update the GPIO pin to be input floating
	PinCfg.GPIO_PinNumber=EXTI_Config->EXTI_Pin.GPIO_Pin;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(EXTI_Config->EXTI_Pin.EXTI_GPIO_Port, &PinCfg);

	//==================================================================

	//2-update AFIO to route between EXTI with port A,B,C,D

	uint8_t AFIO_EXTICR_index = EXTI_Config->EXTI_Pin.EXTI_InputLineNumber/4;

	uint8_t AFIO_EXTICR_position = (EXTI_Config->EXTI_Pin.EXTI_InputLineNumber%4)*4;

	//clear the 4 bits
	AFIO->EXTICR[AFIO_EXTICR_index] &=~(0xf<<AFIO_EXTICR_position);
	AFIO->EXTICR[AFIO_EXTICR_index] |=((AFIO_GPIO_EXTI_MAPPING(EXTI_Config->EXTI_Pin.EXTI_GPIO_Port)&0xf)<<AFIO_EXTICR_position);

	//==================================================================

	//3- update the trigger

	//reset rising and falling register
	EXTI->RTSR &=~(1<<EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);
	EXTI->FTSR &=~(1<<EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);

	if (EXTI_Config->trigger_status == EXTI_TRIGGER_RISING) {

		EXTI->RTSR |=(1<<EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);


	}
	else if (EXTI_Config->trigger_status == EXTI_TRIGGER_FALLING) {

		EXTI->FTSR |=(1<<EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);


	}

	else if (EXTI_Config->trigger_status == EXTI_TRIGGER_RISINGandFALLING) {

		EXTI->RTSR |=(1<<EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);
		EXTI->FTSR |=(1<<EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);

	}


	//==================================================================
	// 4- update IRQ handling  Callback

	P_IRQ_CallBack[EXTI_Config->EXTI_Pin.EXTI_InputLineNumber] = EXTI_Config->P_IRQ_CallBack;


	//==================================================================
	// 5- Enable / disable IRQ
	if (EXTI_Config->IRQ_EN == EXTI_IRQ_ENABLE)
	{
		EXTI->IMR |= (1<<EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);
		NVIC_ENABLE(EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);
	}
	else
	{
		EXTI->IMR &= ~(1<<EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);
		NVIC_DISABLE(EXTI_Config->EXTI_Pin.EXTI_InputLineNumber);


	}
}


//================================================================
//						APIs SUPORTED BY EXTI
//================================================================

/**================================================================
 * @Fn				-MCAL_EXTI_GPIO_DEINIT
 * @brief 			-Reset EXTI and NVIC corresponding IRQ MASK
 * @param [in] 		-none
 * @retval 			-none
 * Note				-none
 */
void MCAL_EXTI_GPIO_DEINIT(void)
{
	EXTI->IMR =    0x00000000;
	EXTI->EMR =    0x00000000;
	EXTI->RTSR =   0x00000000;
	EXTI->FTSR =   0x00000000;
	EXTI->SWIER =  0x00000000;
	//	This bit is set when the selected edge event arrives on the external interrupt line. This bit is
	//	cleared by writing a ‘1’ into the bit.
	EXTI->PR =     0xFFFFFFFF;

	//	disable EXTI IRQ from NVIC
	NVIC_IRQ6_EXTI0_Enable;
	NVIC_IRQ7_EXTI1_Enable;
	NVIC_IRQ8_EXTI2_Enable;
	NVIC_IRQ9_EXTI3_Enable;
	NVIC_IRQ10_EXTI4_Enable;
	NVIC_IRQ23_EXTI5_9_Enable;
	NVIC_IRQ40_EXTI10_15_Enable;


}

/**================================================================
 * @Fn				-MCAL_EXTI_GPIO_INIT
 * @brief 			-Initialize EXTI from specific GPIO PIN ,also specifying the MASK TRRIGER and IRQ CallBack function
 * @param [in] 		-EXTI_config set @ref EXTI_define , @ref EXTI_trigger_define and @ref EXTI_IRQ_define
 * @retval 			-none
 * Note				-STM32F103C6 MCU has GPIO A,B,C,D,E modules
 * 					 -LQFP48 package has only GPIO A,B part of C/D as external pins
 * 					 -Also mandatory to enable RCC clock for AFIO and the corresponding GPIO
 */

void MCAL_EXTI_GPIO_INIT(EXTI_PinConfig_t* EXTI_Config)

{
	UPDATE_EXTI(EXTI_Config);
}



/**================================================================
 * @Fn				-MCAL_EXTI_GPIO_INIT
 * @brief 			-Initialize EXTI from specific GPIO PIN ,also specifying the MASK TRRIGER and IRQ CallBack function
 * @param [in] 		-EXTI_config set @ref EXTI_define , @ref EXTI_trigger_define and @ref EXTI_IRQ_define
 * @retval 			-none
 * Note				-STM32F103C6 MCU has GPIO A,B,C,D,E modules
 * 					 -LQFP48 package has only GPIO A,B part of C/D as external pins
 * 					 -Also mandatory to enable RCC clock for AFIO and the corresponding GPIO
 */
void MCAL_EXTI_GPIO_UPDATE(EXTI_PinConfig_t* EXTI_Config)

{
	UPDATE_EXTI(EXTI_Config);
}




//================================================================
//							ISR FUNCTIONS
//================================================================

void EXTI0_IRQHandler(void)
{
	//clear Pending register (EXTI_PR)
	//This bit is cleared by writing a ‘1’ into the bit.
	EXTI->PR = 1<<0;
	P_IRQ_CallBack[0]();

}

void EXTI1_IRQHandler(void)
{
	//clear Pending register (EXTI_PR)
	//This bit is cleared by writing a ‘1’ into the bit.
	EXTI->PR |= 1<<1;
	P_IRQ_CallBack[1]();

}


void EXTI2_IRQHandler(void)
{
	//clear Pending register (EXTI_PR)
	//This bit is cleared by writing a ‘1’ into the bit.
	EXTI->PR |= 1<<2;
	P_IRQ_CallBack[2]();

}

void EXTI3_IRQHandler(void)
{
	//clear Pending register (EXTI_PR)
	//This bit is cleared by writing a ‘1’ into the bit.
	EXTI->PR |= 1<<3;
	P_IRQ_CallBack[3]();

}

void EXTI4_IRQHandler(void)
{
	//clear Pending register (EXTI_PR)
	//This bit is cleared by writing a ‘1’ into the bit.
	EXTI->PR |= 1<<4;
	P_IRQ_CallBack[4]();

}

void EXTI5_9_IRQHandler(void)
{
	//clear Pending register (EXTI_PR)
	//This bit is cleared by writing a ‘1’ into the bit.
	if(	EXTI->PR & 1<<5) 	{EXTI->PR |= 1<<5 ; P_IRQ_CallBack[5]();}
	if(	EXTI->PR & 1<<6) 	{EXTI->PR |= 1<<6 ; P_IRQ_CallBack[6]();}
	if(	EXTI->PR & 1<<7) 	{EXTI->PR |= 1<<7 ; P_IRQ_CallBack[7]();}
	if(	EXTI->PR & 1<<8) 	{EXTI->PR |= 1<<8 ; P_IRQ_CallBack[8]();}
	if(	EXTI->PR & 1<<9) 	{EXTI->PR |= 1<<9 ; P_IRQ_CallBack[9]();}


}

void EXTI10_15_IRQHandler(void)
{
	//clear Pending register (EXTI_PR)
	//This bit is cleared by writing a ‘1’ into the bit.
	if(	EXTI->PR & 1<<10) 	{EXTI->PR |= 1<<10 ; P_IRQ_CallBack[10]();}
	if(	EXTI->PR & 1<<11) 	{EXTI->PR |= 1<<11 ; P_IRQ_CallBack[11]();}
	if(	EXTI->PR & 1<<12) 	{EXTI->PR |= 1<<12 ; P_IRQ_CallBack[12]();}
	if(	EXTI->PR & 1<<13) 	{EXTI->PR |= 1<<13 ; P_IRQ_CallBack[13]();}
	if(	EXTI->PR & 1<<14) 	{EXTI->PR |= 1<<14 ; P_IRQ_CallBack[14]();}
	if(	EXTI->PR & 1<<14) 	{EXTI->PR |= 1<<15 ; P_IRQ_CallBack[15]();}


}
























