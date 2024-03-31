/*
 * STM32_F103C6_GPIO_DRIVER.c
 *
 *  Created on: Sep 15, 2023
 *      Author: ABRAM
 */

#include "STM32F103C6_GPIO_DRIVER.h"


/**================================================================
 * @Fn			-Get_PIN_Position
 * @brief 		-get the position of the PIN in CRL & CRH because each pin is take 4 bit
 * @param [in] 	-PinNumber: Set PIN number according to @ref GPIO_PINs_define.
 * @retval 		-it return the position of the PIN
 * Note			-none
================================================================**/
uint8_t Get_PIN_Position(uint16_t PIN_Number)
{
	switch(PIN_Number)
	{
	case GPIO_PIN_0:
	case GPIO_PIN_8:
		return 0;
		break;

	case GPIO_PIN_1:
	case GPIO_PIN_9:
		return 4;
		break;

	case GPIO_PIN_2:
	case GPIO_PIN_10:
		return 8;
		break;

	case GPIO_PIN_3:
	case GPIO_PIN_11:
		return 12;
		break;

	case GPIO_PIN_4:
	case GPIO_PIN_12:
		return 16;
		break;

	case GPIO_PIN_5:
	case GPIO_PIN_13:
		return 20;
		break;

	case GPIO_PIN_6:
	case GPIO_PIN_14:
		return 24;
		break;

	case GPIO_PIN_7:
	case GPIO_PIN_15:
		return 28;
		break;
	}

	return 0;
}

/**================================================================
 * @Fn			-MCAL_GPIO_Init
 * @brief 		-Initializes the GPIOx PINy according to the specified parameters in the PIN_Config
 * @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant
 * @param [in] 	-PIN_Config: a pointer to GPIO_PIN_Configuration_t structure that contains
 * 							 the configuration information for the specified GPIO PIN
 * @retval 		-none
 * Note			-STM32F103C6 MCU has GPIO A,B,C,D,E Modules
 * 				 but LQFP48 Package has only GPIO A,B Part of C,D exported as external PINs from the MCU
================================================================**/
void MCAL_GPIO_Init (GPIO_TypeDef *GPIOx, GPIO_PIN_Configuration_t *PIN_Config)
{
	// Port configuration register low (GPIOx_CRL) configure PINs from 0 >> 7
	// Port configuration register high (GPIOx_CRH) configure PINs from 8 >> 15
	volatile uint32_t *Configuration_Register = NULL;
	volatile uint8_t pin_configuration;

	//check if Configuration_Register is CRL or CRH
	Configuration_Register = (PIN_Config->GPIO_PinNumber < GPIO_PIN_8)? &GPIOx->CRL : &GPIOx->CRH;

	//Reset CNF0[1:0] MODE0[1:0]
	(*Configuration_Register) &= ~(0xf << Get_PIN_Position(PIN_Config->GPIO_PinNumber));

	/*
	 * ------------------
	 * | CNF0	| MODE0	|
	 * ------------------
	 * |  3	| 2 | 1	| 0	|
	 * ------------------
	 */
	//check if PIN is O/P or I/P
	if((PIN_Config->GPIO_PinMODE == GPIO_MODE_OUTPUT_PP) || (PIN_Config->GPIO_PinMODE == GPIO_MODE_OUTPUT_OD) || (PIN_Config->GPIO_PinMODE == GPIO_MODE_OUTPUT_AF_PP) || (PIN_Config->GPIO_PinMODE == GPIO_MODE_OUTPUT_AF_OD))
	{
		/*
		 * 00: General purpose output push-pull		--> GPIO_MODE_OUTPUT_PP		>>	0x00000004u
		 * 01: General purpose output Open-drain	--> GPIO_MODE_OUTPUT_OD		>>	0x00000005u
		 * 10: Alternate function output Push-pull	--> GPIO_MODE_OUTPUT_AF_PP	>>	0x00000006u
		 * 11: Alternate function output Open-drain	--> GPIO_MODE_OUTPUT_AF_OD	>>	0x00000007u
		 */
		pin_configuration = ((((PIN_Config->GPIO_PinMODE - 4) << 2) | (PIN_Config->GPIO_PinSPEED)) & 0x0f);
	}
	else
	{
		/*
		 * 00: Analog mode			--> GPIO_MODE_ANALOG		>>	0x00000000u
		 * 01: Floating input		--> GPIO_MODE_INPUT_FLO		>>	0x00000001u
		 * 01: Alternative input	--> GPIO_MODE_INPUT_FLO
		 * 11: Input with PU or PD	--> GPIO_MODE_INPUT_PU
		 * 		PU: ODR --> 1
		 * 		PD: ODR --> 0
		 */
		//check if PIN is Analog or floating input
		if((PIN_Config->GPIO_PinMODE == GPIO_MODE_ANALOG) || (PIN_Config->GPIO_PinMODE == GPIO_MODE_INPUT_FLO))
		{
			pin_configuration = ((((PIN_Config->GPIO_PinMODE) << 2) | (0x0)) & 0x0f);
		}
		else if((PIN_Config->GPIO_PinMODE == GPIO_MODE_INPUT_AF)) //Alternative I/P
		{
			pin_configuration = ((((GPIO_MODE_INPUT_FLO) << 2) | (0x0)) & 0x0f);
		}
		else //input PU or PD
		{
			pin_configuration = ((((PIN_Config->GPIO_PinMODE) << 2) | (0x0)) & 0x0f);

			/*
			 * Table 20. Port bit configuration table
			 * input PU >> PxODR register = 1
			 * input PD >> PxODR register = 0
			 */
			if(PIN_Config->GPIO_PinMODE == GPIO_MODE_INPUT_PU) //I/P pull up
			{
				GPIOx->ODR |= ((uint32_t)(PIN_Config->GPIO_PinNumber));
			}
			else //I/P pull down
			{
				GPIOx->ODR &= ~((uint32_t)(PIN_Config->GPIO_PinNumber));
			}
		}
	}

	//Put the values of CNF & MODE in CRL or CRH
	(*Configuration_Register) |= (pin_configuration << Get_PIN_Position(PIN_Config->GPIO_PinNumber));
}

/**================================================================
 * @Fn			-MCAL_GPIO_DeInit
 * @brief 		-Reset All the GPIO Registers.
 * @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant
 * @retval 		-none
 * Note			-none
================================================================**/
void MCAL_GPIO_DeInit (GPIO_TypeDef *GPIOx)
{
	/*
	 * If MCU Dosen't Have Reset Controller:
	 * 		>> use the reset value of each register to reset the peripheral
	 * GPIOx->CRL =  0x44444444;
	 * GPIOx->CRH =  0x44444444;
	 * GPIOx->IDR; (Read Only)
	 * GPIOx->ODR  =  0x00000000;
	 * GPIOx->BSRR =  0x00000000;
	 * GPIOx->BRR =   0x00000000;
	 * GPIOx->LCKR =  0x00000000;
	 */
	/*
	 * APB2 peripheral reset register (RCC_APB2RSTR)
	 * IOPxRST: IO port x reset
	 * Set and cleared by software.
	 * 0: No effect
	 * 1: Reset IO port A
	 */

	//switch for the instant of GPIO
	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |=  (1 << 2);
		RCC->APB2RSTR &= ~(1 << 2);
	}
	else if(GPIOx == GPIOB)
	{
		RCC->APB2RSTR |=  (1 << 3);
		RCC->APB2RSTR &= ~(1 << 3);
	}
	else if(GPIOx == GPIOC)
	{
		RCC->APB2RSTR |=  (1 << 4);
		RCC->APB2RSTR &= ~(1 << 4);
	}
	else if(GPIOx == GPIOD)
	{
		RCC->APB2RSTR |=  (1 << 5);
		RCC->APB2RSTR &= ~(1 << 5);
	}
	else if(GPIOx == GPIOE)
	{
		RCC->APB2RSTR |=  (1 << 6);
		RCC->APB2RSTR &= ~(1 << 6);
	}
}

/**================================================================
 * @Fn			-MCAL_GPIO_ReadPin
 * @brief 		-Read Specific PIN.
 * @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant.
 * @param [in] 	-PinNumber: Set PIN number according to @ref GPIO_PINs_define.
 * @retval 		-the I/P PIN Value (Two Values based on @ref GPIO_PIN_state >> SET or RESET)
 * Note			-none
================================================================**/
uint8_t MCAL_GPIO_ReadPin (GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	//read from IDR register
	if((GPIOx->IDR & PinNumber) != (uint32_t)GPIO_PIN_RESET)
	{
		return GPIO_PIN_SET;
	}
	else
	{
		return GPIO_PIN_RESET;
	}
}

/**================================================================
 * @Fn			-MCAL_GPIO_ReadPort
 * @brief 		-Read Specific Port.
 * @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant.
 * @retval 		-the I/P PORT Value.
 * Note			-none
================================================================**/
uint16_t MCAL_GPIO_ReadPort (GPIO_TypeDef *GPIOx)
{
	return ((uint16_t)GPIOx->IDR);
}

/**================================================================
 * @Fn			-MCAL_GPIO_WritePin
 * @brief 		-Write a value on Specific PIN.
 * @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant.
 * @param [in] 	-PinNumber: Set PIN number according to @ref GPIO_PINs_define.
 * @param [in] 	-Value: The value that will write to PIN (Two Values based on @ref GPIO_PIN_state >> SET or RESET).
 * @retval 		-none
 * Note			-none
================================================================**/
void MCAL_GPIO_WritePin (GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint8_t Value)
{
	//we may write on ODR or on BSRR or BRR
	//check if we set or reset the pin
	/*
	 * BSRR >> Port Bit Set Reset Register
	 * Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
	 * These bits are write-only and can be accessed in Word mode only.
	 * 0: No action on the corresponding ODRx bit
	 * 1: Set the corresponding ODRx bit
	 */
	/*
	 * BRR >> Port Bit Reset Register
	 * Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
	 * These bits are write-only and can be accessed in Word mode only.
	 * 0: No action on the corresponding ODRx bit
	 * 1: Reset the corresponding ODRx bit
	 */
	if(Value == GPIO_PIN_SET)
	{
		GPIOx->BSRR = (uint32_t)PinNumber;
	}
	else if(Value == GPIO_PIN_RESET)
	{
		GPIOx->BRR = (uint32_t)PinNumber;
	}
}

/**================================================================
 * @Fn			-MCAL_GPIO_WritePort
 * @brief 		-Write a value on Specific PORT.
 * @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant.
 * @param [in] 	-Value: The value that will write to PORT.
 * @retval 		-none
 * Note			-none
================================================================**/
void MCAL_GPIO_WritePort (GPIO_TypeDef *GPIOx, uint16_t Value)
{
	GPIOx->ODR = (uint32_t)Value;
}

/**================================================================
 * @Fn			-MCAL_GPIO_TogglePin
 * @brief 		-Toggle Specific PIN.
 * @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant.
 * @param [in] 	-PinNumber: Set PIN number according to @ref GPIO_PINs_define.
 * @retval 		-none
 * Note			-none
================================================================**/
void MCAL_GPIO_TogglePin (GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	//Toggle bit
	GPIOx->ODR ^= PinNumber;
}

/**================================================================
 * @Fn			-MCAL_GPIO_LockPin
 * @brief 		-The locking mechanism allows the IO configuration to be frozen.
 * @param [in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant.
 * @param [in] 	-PinNumber: Set PIN number according to @ref GPIO_PINs_define.
 * @retval 		-it returns lock state according to @ref GPIO_LOCK_state (OK if pin config is locked else ERROR)
 * Note			-it is possible to modify the value of the port bit until the next reset.
================================================================**/
uint8_t MCAL_GPIO_LockPin (GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	/*
	 * Bit 16 LCKK[16]: Lock key
	 * This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	 * LOCK key writing sequence:
	 * 		>> Write 1
	 * 		>> Write 0
	 * 		>> Write 1
	 * 		>> Read 0
	 * 		>> Read 1 (this read is optional but confirms that the lock is active)
	 * Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	 * 		 Any error in the lock sequence will abort the lock
	 *----------------------------------------------------------------------------------------
	 * Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	 * These bits are read write but can only be written when the LCKK bit is 0.
	 * 0: Port configuration not locked
	 * 1: Port configuration locked
	 */

	//Set LCKK[16] & LCKy
	volatile uint32_t tmp = (1 << 16);
	tmp |= (uint32_t)PinNumber;

	GPIOx->LCKR = tmp;			//write 1 on LCKy & LCKK
	GPIOx->LCKR = PinNumber;	//write 0 on LCKK
	GPIOx->LCKR = tmp;			//write 1 on LCKK
	tmp = GPIOx->LCKR;			//read 0 from LCKK

	//check if lock if active or not
	// LCKK --> 1 --> lock active
	// LCKK --> 0 --> lock not active (error)
	if((GPIOx->LCKR & (1 << 16)) != 0)
	{
		return GPIO_LOCK_OK;
	}
	else
	{
		return GPIO_LOCK_ERROR;
	}
}











