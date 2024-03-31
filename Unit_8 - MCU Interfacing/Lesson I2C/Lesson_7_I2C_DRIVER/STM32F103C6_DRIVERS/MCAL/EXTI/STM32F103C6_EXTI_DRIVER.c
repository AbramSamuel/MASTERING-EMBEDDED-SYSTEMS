/*
 * STM32F103C6_EXTI_DRIVER.c
 *
 *  Created on: Sep 23, 2023
 *      Author: ABRAM
 */



#include "STM32F103xx6.h"
#include "STM32F103C6_EXTI_DRIVER.h"
#include "STM32F103C6_GPIO_DRIVER.h"


//-*-*-*-*-*-*-*-*-*-*-*-
//EXTI GPIO Mapping:
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	uint16_t 				EXTI_Input_Line_Number;		/* Interrupt line number 0 --> 15 (according to @ref EXTI_Input_Line_Number)*/
	GPIO_TypeDef*			EXTI_GPIO_PORT;				/* Interrupt PORT A,B,C,D */
	uint16_t				EXTI_GPIO_PIN;				/* Interrupt PIN number 0 --> 15 */
	uint8_t					IVT_IRQ_Number;				/* Interrupt number from IVT */
}EXTI_GPIO_Mapping_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//EXTI Configuration:
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	/* EXTI_PIN Specify the Interrupt line number & Interrupt PORT & Interrupt PIN number (EXTI GPIO Mapping)
	 * you must put it according to @ref EXTI_PIN_Define */
	EXTI_GPIO_Mapping_t		EXTI_PIN;

	/* EXTI_Trigger_Case Specfiy the Interrupt Trigger Case if it is Rising or Falling or Both
	 * you must put it according to @ref EXTI_Trigger_Case*/
	uint8_t					EXTI_Trigger_Case;

	/* EXTI_IRQ_EN enable & disable IRQ Mask in EXTI & NVIC
	 * you must put it according to @ref EXTI_IRQ_EN*/
	uint8_t					EXTI_IRQ_EN;

	/* PF_IRQ_CallBack this is a pointer to a function we need it executed when the interrupt occurred */
	void (* PF_IRQ_CallBack)(void);
}EXTI_Configuration_t;


//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref EXTI_Define

//@ref EXTI_Input_Line_Number
#define EXTI0				0
#define EXTI1				1
#define EXTI2				2
#define EXTI3				3
#define EXTI4				4
#define EXTI5				5
#define EXTI6				6
#define EXTI7				7
#define EXTI8				8
#define EXTI9				9
#define EXTI10				10
#define EXTI11				11
#define EXTI12				12
#define EXTI13				13
#define EXTI14				14
#define EXTI15				15


//==================================

//@ref EXTI_Trigger_Case
#define EXTI_Trigger_RISING						0
#define EXTI_Trigger_FALLING					1
#define EXTI_Trigger_RISING_AND_FALLING			2

//==================================

//@ref EXTI_IRQ_EN
#define EXTI_IRQ_ENABLE							1
#define EXTI_IRQ_DISABLE						0

//======================================================================

/*
 * ======================================================================
 * 			APIs Supported by "MCAL EXTI DRIVER"
 * ======================================================================
 */

void MCAL_EXTI_GPIO_Init(EXTI_Configuration_t *EXTI_CFG);
void MCAL_EXTI_GPIO_DeInit(void);

void MCAL_EXTI_GPIO_Update(EXTI_Configuration_t *EXTI_CFG);















