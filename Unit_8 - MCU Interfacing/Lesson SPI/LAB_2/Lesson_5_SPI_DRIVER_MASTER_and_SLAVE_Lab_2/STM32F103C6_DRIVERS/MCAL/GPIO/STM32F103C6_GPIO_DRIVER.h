/*
 * STM32_F103C6_GPIO_DRIVER.h
 *
 *  Created on: Sep 15, 2023
 *      Author: ABRAM
 */

#ifndef STM32_F103C6_GPIO_DRIVER_H_
#define STM32_F103C6_GPIO_DRIVER_H_

//includes

#include "STM32F103xx6.h"
#include "STM32F103C6_EXTI_DRIVER.h"
#include "STM32F103C6_GPIO_DRIVER.h"

//======================================================================

//-----------------------------
//User type definitions (structures)
//-----------------------------
typedef struct
{
	/*
	 * >> Specifies the GPIO Pins to be configured.
	 * >> This parameter must be a value of @ref GPIO_PINS_define
	 */
	uint16_t GPIO_PinNumber;

	/*
	 * >> Specifies the MODE of the GPIO Pins.
	 * >> This parameter must be a value of @ref GPIO_MODE_define
	 */
	uint8_t GPIO_PinMODE;

	/*
	 * >> Specifies the SPEED of the GPIO Pins.
	 * >> This parameter must be a value of @ref GPIO_SPEED_define
	 */
	uint8_t GPIO_PinSPEED;

}GPIO_PIN_Configuration_t;

//======================================================================

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref GPIO_PINS_define
#define GPIO_PIN_0					((uint16_t)0x0001)		/* PIN 00 selected */
#define GPIO_PIN_1					((uint16_t)0x0002)		/* PIN 01 selected */
#define GPIO_PIN_2					((uint16_t)0x0004)		/* PIN 02 selected */
#define GPIO_PIN_3					((uint16_t)0x0008)		/* PIN 03 selected */
#define GPIO_PIN_4					((uint16_t)0x0010)		/* PIN 04 selected */
#define GPIO_PIN_5					((uint16_t)0x0020)		/* PIN 05 selected */
#define GPIO_PIN_6					((uint16_t)0x0040)		/* PIN 06 selected */
#define GPIO_PIN_7					((uint16_t)0x0080)		/* PIN 07 selected */
#define GPIO_PIN_8					((uint16_t)0x0100)		/* PIN 08 selected */
#define GPIO_PIN_9					((uint16_t)0x0200)		/* PIN 09 selected */
#define GPIO_PIN_10					((uint16_t)0x0400)		/* PIN 10 selected */
#define GPIO_PIN_11					((uint16_t)0x0800)		/* PIN 11 selected */
#define GPIO_PIN_12					((uint16_t)0x1000)		/* PIN 12 selected */
#define GPIO_PIN_13					((uint16_t)0x2000)		/* PIN 13 selected */
#define GPIO_PIN_14					((uint16_t)0x4000)		/* PIN 14 selected */
#define GPIO_PIN_15					((uint16_t)0x8000)		/* PIN 15 selected */
#define GPIO_PIN_ALL				((uint16_t)0xFFFF)		/* All pins selected */

//@ref GPIO_MODE_define
/*
 * 0: Analog mode
 * 1: Floating input (reset state)
 * 2: Input with pull-up / pull-down
 * 3: Input with pull-down
 * 4: General purpose output push-pull
 * 5: General purpose output Open-drain
 * 6: Alternate function output Push-pull
 * 7: Alternate function output Open-drain
 * 8: Alternate function input
 */
#define GPIO_MODE_ANALOG				0x00000000u		/* Analog mode */
#define GPIO_MODE_INPUT_FLO				0x00000001u		/* Floating input */
#define GPIO_MODE_INPUT_PU				0x00000002u		/* Input with pull-up */
#define GPIO_MODE_INPUT_PD				0x00000003u		/* Input with pull-down */
#define GPIO_MODE_OUTPUT_PP				0x00000004u		/* General purpose output push-pull */
#define GPIO_MODE_OUTPUT_OD				0x00000005u		/* General purpose output Open-drain */
#define GPIO_MODE_OUTPUT_AF_PP			0x00000006u		/* Alternate function output Push-pull */
#define GPIO_MODE_OUTPUT_AF_OD			0x00000007u		/* Alternate function output Open-drain */
#define GPIO_MODE_INPUT_AF				0x00000008u		/* Alternate function input */

//@ref GPIO_SPEED_define
/*
 * 1: Output mode, max speed 10 MHz.
 * 2: Output mode, max speed 2 MHz.
 * 3: Output mode, max speed 50 MHz.
*/
#define GPIO_SPEED_10MHz				0x00000001u		/* Output mode, max speed 10 MHz. */
#define GPIO_SPEED_2MHz					0x00000002u		/* Output mode, max speed 02 MHz. */
#define GPIO_SPEED_50MHz				0x00000003u		/* Output mode, max speed 50 MHz. */

//@ref GPIO_PIN_state
#define GPIO_PIN_SET					1
#define GPIO_PIN_RESET					0

//@ref GPIO_PORT_state
#define GPIO_PORT_HIGH					0xFFFF
#define GPIO_PORT_LOW					0x0000

//@ref GPIO_LOCK_state
#define GPIO_LOCK_OK					0
#define GPIO_LOCK_ERROR					1

//======================================================================

/*
 * ======================================================================
 * 			APIs Supported by "MCAL GPIO DRIVER"
 * ======================================================================
 */

//Initialize & Reset APIs
void MCAL_GPIO_Init (GPIO_TypeDef *GPIOx, GPIO_PIN_Configuration_t *PIN_Config);
void MCAL_GPIO_DeInit (GPIO_TypeDef *GPIOx);

//Read APIs
uint8_t MCAL_GPIO_ReadPin (GPIO_TypeDef *GPIOx, uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort (GPIO_TypeDef *GPIOx);

//Write APIs
void MCAL_GPIO_WritePin (GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint8_t Value);
void MCAL_GPIO_WritePort (GPIO_TypeDef *GPIOx, uint16_t Value);

//Toggle APIs
void MCAL_GPIO_TogglePin (GPIO_TypeDef *GPIOx, uint16_t PinNumber);

//Lock APIs
uint8_t MCAL_GPIO_LockPin (GPIO_TypeDef *GPIOx, uint16_t PinNumber);


#endif /* STM32_F103C6_GPIO_DRIVER_H_ */
