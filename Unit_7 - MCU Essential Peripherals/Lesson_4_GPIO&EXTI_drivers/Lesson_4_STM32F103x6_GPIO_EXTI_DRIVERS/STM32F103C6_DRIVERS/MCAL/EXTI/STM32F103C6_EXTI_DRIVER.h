/*
 * STM32F103C6_EXTI_DRIVER.h
 *
 *  Created on: Sep 23, 2023
 *      Author: ABRAM
 */

#ifndef MCAL_EXTI_STM32F103C6_EXTI_DRIVER_H_
#define MCAL_EXTI_STM32F103C6_EXTI_DRIVER_H_

#include "STM32F103xx6.h"
#include "STM32F103C6_GPIO_DRIVER.h"

typedef struct
{
	uint16_t 		EXTI_InputLineNumber;
	GPIO_TypeDef*	EXTI_GPIO_Port;
	uint16_t		GPIO_Pin;
	uint8_t 		IVT_IRQ_Number;
}EXTI_GPIO_mapping_t;


typedef struct
{
	EXTI_GPIO_mapping_t EXTI_Pin;           //specifies EXTI GPIO  mapping
									        //this parameter must be set based on @ref EXTI_define

	uint8_t				trigger_status;		//specifies EXTI trigger case (FALLING , RISING or FALLING and RISING )
											//this parameter must be based on @ref EXTI_trigger_define


	uint8_t				IRQ_EN;				//enable or disable EXTI IRQ(that will enable the IRQ MASK and also NVIC interrupt)
											//the parameter must be based on @ref EXTI_IRQ_define

	void(*P_IRQ_CallBack)(void);			//set the C function (ISR) once the IRQ happen
}EXTI_PinConfig_t;




//================================
//Macros Configuration References
//================================

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





//================================

//@ref EXTI_define

//EXTI0
#define    EXTI0PA0                                     (EXTI_GPIO_mapping_t){EXTI0,GPIOA,GPIO_PIN_0,EXTI0_IQR}
#define    EXTI0PB0                                     (EXTI_GPIO_mapping_t){EXTI0,GPIOB,GPIO_PIN_0,EXTI0_IQR}
#define    EXTI0PC0                                     (EXTI_GPIO_mapping_t){EXTI0,GPIOC,GPIO_PIN_0,EXTI0_IQR}
#define    EXTI0PD0                                     (EXTI_GPIO_mapping_t){EXTI0,GPIOD,GPIO_PIN_0,EXTI0_IQR}


//EXTI1
#define    EXTI1PA1                                     (EXTI_GPIO_mapping_t){EXTI1,GPIOA,GPIO_PIN_1,EXTI1_IQR}
#define    EXTI1PB1                                     (EXTI_GPIO_mapping_t){EXTI1,GPIOB,GPIO_PIN_1,EXTI1_IQR}
#define    EXTI1PC1                                     (EXTI_GPIO_mapping_t){EXTI1,GPIOC,GPIO_PIN_1,EXTI1_IQR}
#define    EXTI1PD1                                     (EXTI_GPIO_mapping_t){EXTI1,GPIOD,GPIO_PIN_1,EXTI1_IQR}


//EXTI2
#define    EXTI2PA2                                     (EXTI_GPIO_mapping_t){EXTI2,GPIOA,GPIO_PIN_2,EXTI2_IQR}
#define    EXTI2PB2                                     (EXTI_GPIO_mapping_t){EXTI2,GPIOB,GPIO_PIN_2,EXTI2_IQR}
#define    EXTI2PC2                                     (EXTI_GPIO_mapping_t){EXTI2,GPIOC,GPIO_PIN_2,EXTI2_IQR}
#define    EXTI2PD2                                     (EXTI_GPIO_mapping_t){EXTI2,GPIOD,GPIO_PIN_2,EXTI2_IQR}


//EXTI3
#define    EXTI3PA3                                     (EXTI_GPIO_mapping_t){EXTI3,GPIOA,GPIO_PIN_3,EXTI3_IQR}
#define    EXTI3PB3                                     (EXTI_GPIO_mapping_t){EXTI3,GPIOB,GPIO_PIN_3,EXTI3_IQR}
#define    EXTI3PC3                                     (EXTI_GPIO_mapping_t){EXTI3,GPIOC,GPIO_PIN_3,EXTI3_IQR}
#define    EXTI3PD3                                     (EXTI_GPIO_mapping_t){EXTI3,GPIOD,GPIO_PIN_3,EXTI3_IQR}


//EXTI4
#define    EXTI4PA4                                     (EXTI_GPIO_mapping_t){EXTI4,GPIOA,GPIO_PIN_4,EXTI4_IQR}
#define    EXTI4PB4                                     (EXTI_GPIO_mapping_t){EXTI4,GPIOB,GPIO_PIN_4,EXTI4_IQR}
#define    EXTI4PC4                                     (EXTI_GPIO_mapping_t){EXTI4,GPIOC,GPIO_PIN_4,EXTI4_IQR}
#define    EXTI4PD4                                     (EXTI_GPIO_mapping_t){EXTI4,GPIOD,GPIO_PIN_4,EXTI4_IQR}


//EXTI5
#define    EXTI5PA5                                     (EXTI_GPIO_mapping_t){EXTI5,GPIOA,GPIO_PIN_5,EXTI5_IQR}
#define    EXTI5PB5                                     (EXTI_GPIO_mapping_t){EXTI5,GPIOB,GPIO_PIN_5,EXTI5_IQR}
#define    EXTI5PC5                                     (EXTI_GPIO_mapping_t){EXTI5,GPIOC,GPIO_PIN_5,EXTI5_IQR}
#define    EXTI5PD5                                     (EXTI_GPIO_mapping_t){EXTI5,GPIOD,GPIO_PIN_5,EXTI5_IQR}


//EXTI6
#define    EXTI6PA6                                     (EXTI_GPIO_mapping_t){EXTI6,GPIOA,GPIO_PIN_6,EXTI6_IQR}
#define    EXTI6PB6                                     (EXTI_GPIO_mapping_t){EXTI6,GPIOB,GPIO_PIN_6,EXTI6_IQR}
#define    EXTI6PC6                                     (EXTI_GPIO_mapping_t){EXTI6,GPIOC,GPIO_PIN_6,EXTI6_IQR}
#define    EXTI6PD6                                     (EXTI_GPIO_mapping_t){EXTI6,GPIOD,GPIO_PIN_6,EXTI6_IQR}


//EXTI7
#define    EXTI7PA7                                     (EXTI_GPIO_mapping_t){EXTI7,GPIOA,GPIO_PIN_7,EXTI7_IQR}
#define    EXTI7PB7                                     (EXTI_GPIO_mapping_t){EXTI7,GPIOB,GPIO_PIN_7,EXTI7_IQR}
#define    EXTI7PC7                                     (EXTI_GPIO_mapping_t){EXTI7,GPIOC,GPIO_PIN_7,EXTI7_IQR}
#define    EXTI7PD7                                     (EXTI_GPIO_mapping_t){EXTI7,GPIOD,GPIO_PIN_7,EXTI7_IQR}


//EXTI8
#define    EXTI8PA8                                     (EXTI_GPIO_mapping_t){EXTI8,GPIOA,GPIO_PIN_8,EXTI8_IQR}
#define    EXTI8PB8                                     (EXTI_GPIO_mapping_t){EXTI8,GPIOB,GPIO_PIN_8,EXTI8_IQR}
#define    EXTI8PC8                                     (EXTI_GPIO_mapping_t){EXTI8,GPIOC,GPIO_PIN_8,EXTI8_IQR}
#define    EXTI8PD8                                     (EXTI_GPIO_mapping_t){EXTI8,GPIOD,GPIO_PIN_8,EXTI8_IQR}


//EXTI9
#define    EXTI9PA9                                     (EXTI_GPIO_mapping_t){EXTI9,GPIOA,GPIO_PIN_9,EXTI9_IQR}
#define    EXTI9PB9                                     (EXTI_GPIO_mapping_t){EXTI9,GPIOB,GPIO_PIN_9,EXTI9_IQR}
#define    EXTI9PC9                                     (EXTI_GPIO_mapping_t){EXTI9,GPIOC,GPIO_PIN_9,EXTI9_IQR}
#define    EXTI9PD9                                     (EXTI_GPIO_mapping_t){EXTI9,GPIOD,GPIO_PIN_9,EXTI9_IQR}


//EXTI10
#define    EXTI10PA10                                   (EXTI_GPIO_mapping_t){EXTI10,GPIOA,GPIO_PIN_10,EXTI10_IQR}
#define    EXTI10PB10                                   (EXTI_GPIO_mapping_t){EXTI10,GPIOB,GPIO_PIN_10,EXTI10_IQR}
#define    EXTI10PC10                                   (EXTI_GPIO_mapping_t){EXTI10,GPIOC,GPIO_PIN_10,EXTI10_IQR}
#define    EXTI10PD10                                   (EXTI_GPIO_mapping_t){EXTI10,GPIOD,GPIO_PIN_10,EXTI10_IQR}


//EXTI11
#define    EXTI11PA11                                   (EXTI_GPIO_mapping_t){EXTI11,GPIOA,GPIO_PIN_11,EXTI11_IQR}
#define    EXTI11PB11                                   (EXTI_GPIO_mapping_t){EXTI11,GPIOB,GPIO_PIN_11,EXTI11_IQR}
#define    EXTI11PC11                                   (EXTI_GPIO_mapping_t){EXTI11,GPIOC,GPIO_PIN_11,EXTI11_IQR}
#define    EXTI11PD11                                   (EXTI_GPIO_mapping_t){EXTI11,GPIOD,GPIO_PIN_11,EXTI11_IQR}


//EXTI12
#define    EXTI12PA12                                   (EXTI_GPIO_mapping_t){EXTI12,GPIOA,GPIO_PIN_12,EXTI12_IQR}
#define    EXTI12PB12                                   (EXTI_GPIO_mapping_t){EXTI12,GPIOB,GPIO_PIN_12,EXTI12_IQR}
#define    EXTI12PC12                                   (EXTI_GPIO_mapping_t){EXTI12,GPIOC,GPIO_PIN_12,EXTI12_IQR}
#define    EXTI12PD12                                   (EXTI_GPIO_mapping_t){EXTI12,GPIOD,GPIO_PIN_12,EXTI12_IQR}


//EXTI13
#define    EXTI13PA13                                   (EXTI_GPIO_mapping_t){EXTI13,GPIOA,GPIO_PIN_13,EXTI13_IQR}
#define    EXTI13PB13                                   (EXTI_GPIO_mapping_t){EXTI13,GPIOB,GPIO_PIN_13,EXTI13_IQR}
#define    EXTI13PC13                                   (EXTI_GPIO_mapping_t){EXTI13,GPIOC,GPIO_PIN_13,EXTI13_IQR}
#define    EXTI13PD13                                   (EXTI_GPIO_mapping_t){EXTI13,GPIOD,GPIO_PIN_13,EXTI13_IQR}


//EXTI14
#define    EXTI14PA14                                   (EXTI_GPIO_mapping_t){EXTI14,GPIOA,GPIO_PIN_14,EXTI14_IQR}
#define    EXTI14PB14                                   (EXTI_GPIO_mapping_t){EXTI14,GPIOB,GPIO_PIN_14,EXTI14_IQR}
#define    EXTI14PC14                                   (EXTI_GPIO_mapping_t){EXTI14,GPIOC,GPIO_PIN_14,EXTI14_IQR}
#define    EXTI14PD14                                   (EXTI_GPIO_mapping_t){EXTI14,GPIOD,GPIO_PIN_14,EXTI14_IQR}


//EXTI15
#define    EXTI15PA15                                   (EXTI_GPIO_mapping_t){EXTI15,GPIOA,GPIO_PIN_15,EXTI15_IQR}
#define    EXTI15PB15                                   (EXTI_GPIO_mapping_t){EXTI15,GPIOB,GPIO_PIN_15,EXTI15_IQR}
#define    EXTI15PC15                                   (EXTI_GPIO_mapping_t){EXTI15,GPIOC,GPIO_PIN_15,EXTI15_IQR}
#define    EXTI15PD15                                   (EXTI_GPIO_mapping_t){EXTI15,GPIOD,GPIO_PIN_15,EXTI15_IQR}



//================================
//@ref EXTI_trigger_define

#define EXTI_TRIGGER_FALLING					0
#define EXTI_TRIGGER_RISING						1
#define EXTI_TRIGGER_RISINGandFALLING			2



//================================
//@ref EXTI_IRQ_define
#define EXTI_IRQ_ENABLE			1
#define EXTI_IRQ_DISABLE		0



/*
 * =======================================================================================
 * 							APIs Supported by "MCAL EXTI DRIVER"
 * =======================================================================================
 */

void MCAL_EXTI_GPIO_INIT(EXTI_PinConfig_t* EXTIO_Config);
void MCAL_EXTI_GPIO_DEINIT(void);
void MCAL_EXTI_GPIO_UPDATE(EXTI_PinConfig_t* EXTIO_Config);




#endif /* MCAL_EXTI_STM32F103C6_EXTI_DRIVER_H_ */
