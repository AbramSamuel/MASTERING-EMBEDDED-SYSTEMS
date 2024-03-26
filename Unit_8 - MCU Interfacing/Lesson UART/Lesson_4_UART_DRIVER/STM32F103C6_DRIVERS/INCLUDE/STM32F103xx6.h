/*
 * STM32F103xx6.h
 *
 *  Created on: Sep 15, 2023
 *      Author: ABRAM
 */

#ifndef STM32F103XX6_H_
#define STM32F103XX6_H_


//-----------------------------
//Includes
//-----------------------------
#include <stdlib.h>
#include <stdint.h>

//======================================================================

//-----------------------------
//Base addresses for Memories
//-----------------------------
#define FLASH_Memory_BASE							0x08000000UL
#define SYSTEM_Memory_Base							0x1FFFF000UL
#define SRAM_Memory_BASE							0x20000000UL

#define Peripherals_BASE							0x40000000UL

#define Cortex_M3_Internal_Peripherals_BASE			0xE0000000UL

#define NVIC_BASE									0xE000E100UL

//======================================================================

//-----------------------------
//Base addresses for Peripherals
//-----------------------------

//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------

//RCC
#define RCC_BASE									0x40021000UL

//-----------------------------
//Base addresses for APB2 Peripherals
//-----------------------------

//GPIO
//A,B fully included in LQFP48 Package
#define GPIOA_BASE									0x40010800UL
#define GPIOB_BASE									0x40010C00UL

//C,D partial included in LQFP48 Package
#define GPIOC_BASE									0x40011000UL
#define GPIOD_BASE									0x40011400UL

//E is not included in LQFP48 Package
#define GPIOE_BASE									0x40011800UL


//EXTI
#define EXTI_BASE									0x40010400UL


//AFIO
#define AFIO_BASE									0x40010000UL

//USART1
#define USART1_BASE									0x40013800UL


//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------

//USART2
#define USART2_BASE									0x40004400UL

//USART3
#define USART3_BASE									0x40004800UL

//======================================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4]; /* EXTICR1, EXTICR2, EXTICR3, EXTICR4 */
	volatile uint32_t RESERVED0; //0x18
	volatile uint32_t MAPR2;
}AFIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
}RCC_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: NVIC
//-*-*-*-*-*-*-*-*-*-*-*-
#define NVIC_ISER0									*((volatile uint32_t *)(NVIC_BASE + 0x000))
#define NVIC_ISER1									*((volatile uint32_t *)(NVIC_BASE + 0x004))
#define NVIC_ISER2									*((volatile uint32_t *)(NVIC_BASE + 0x008))
#define NVIC_ICER0									*((volatile uint32_t *)(NVIC_BASE + 0x080))
#define NVIC_ICER1									*((volatile uint32_t *)(NVIC_BASE + 0x084))
#define NVIC_ICER2									*((volatile uint32_t *)(NVIC_BASE + 0x088))

//======================================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA										((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB										((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC										((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD										((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE										((GPIO_TypeDef *)GPIOE_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: RCC
//-*-*-*-*-*-*-*-*-*-*-*
#define RCC											((RCC_TypeDef *)RCC_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
#define EXTI										((EXTI_TypeDef *)EXTI_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
#define AFIO										((AFIO_TypeDef *)AFIO_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: USART
//-*-*-*-*-*-*-*-*-*-*-*
#define USART1										((USART_TypeDef *)USART1_BASE)
#define USART2										((USART_TypeDef *)USART2_BASE)
#define USART3										((USART_TypeDef *)USART3_BASE)

//======================================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define SET_BIT(Reg,Bit_No)							(Reg |= (1 << Bit_No))
#define CLEAR_BIT(Reg,Bit_No)						(Reg &= ~ (1 << Bit_No))
#define TOGGLE_BIT(Reg,Bit_No)						(Reg ^= (1 << Bit_No))
#define READ_BIT(Reg,Bit_No)						((Reg >> Bit_No) & 1)

//======================================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define RCC_AFIO_CLK_EN()							SET_BIT(RCC->APB2ENR,0)

#define RCC_GPIOA_CLK_EN()							SET_BIT(RCC->APB2ENR,2)
#define RCC_GPIOB_CLK_EN()							SET_BIT(RCC->APB2ENR,3)
#define RCC_GPIOC_CLK_EN()							SET_BIT(RCC->APB2ENR,4)
#define RCC_GPIOD_CLK_EN()							SET_BIT(RCC->APB2ENR,5)
#define RCC_GPIOE_CLK_EN()							SET_BIT(RCC->APB2ENR,6)

//enable clock for USART			PCLK2 --> USART1		& PCLK1 --> USART2,3
#define RCC_USART1_CLK_EN()							SET_BIT(RCC->APB2ENR,14)
#define RCC_USART2_CLK_EN()							SET_BIT(RCC->APB1ENR,17)
#define RCC_USART3_CLK_EN()							SET_BIT(RCC->APB1ENR,18)

//reset clock for USART
#define RCC_USART1_Reset()							SET_BIT(RCC->APB2RSTR,14)
#define RCC_USART2_Reset()							SET_BIT(RCC->APB1RSTR,17)
#define RCC_USART3_Reset()							SET_BIT(RCC->APB1RSTR,18)

//======================================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//IVT numbers:
//-*-*-*-*-*-*-*-*-*-*-*
#define EXTI0_IRQ									6
#define EXTI1_IRQ									7
#define EXTI2_IRQ									8
#define EXTI3_IRQ									9
#define EXTI4_IRQ									10
/* EXTI9_5 --> 23 */
#define EXTI5_IRQ									23
#define EXTI6_IRQ									23
#define EXTI7_IRQ									23
#define EXTI8_IRQ									23
#define EXTI9_IRQ									23
/* EXTI15_10 --> 40 */
#define EXTI10_IRQ									40
#define EXTI11_IRQ									40
#define EXTI12_IRQ									40
#define EXTI13_IRQ									40
#define EXTI14_IRQ									40
#define EXTI15_IRQ									40

//USART IRQ
#define USART1_IRQ									37
#define USART2_IRQ									38
#define USART3_IRQ									39

//======================================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define NVIC_EXTI0_IRQ_ENABLE						SET_BIT(NVIC_ISER0,EXTI0_IRQ);
#define NVIC_EXTI1_IRQ_ENABLE						SET_BIT(NVIC_ISER0,EXTI1_IRQ);
#define NVIC_EXTI2_IRQ_ENABLE						SET_BIT(NVIC_ISER0,EXTI2_IRQ);
#define NVIC_EXTI3_IRQ_ENABLE						SET_BIT(NVIC_ISER0,EXTI3_IRQ);
#define NVIC_EXTI4_IRQ_ENABLE						SET_BIT(NVIC_ISER0,EXTI4_IRQ);
#define NVIC_EXTI9_5_IRQ_ENABLE						SET_BIT(NVIC_ISER0,EXTI5_IRQ);
#define NVIC_EXTI15_10_IRQ_ENABLE					SET_BIT(NVIC_ISER1,(EXTI10_IRQ-32));

//enable USART interrupts
#define NVIC_USART1_IRQ37_ENABLE					SET_BIT(NVIC_ISER1,(USART1_IRQ-32));
#define NVIC_USART2_IRQ38_ENABLE					SET_BIT(NVIC_ISER1,(USART2_IRQ-32));
#define NVIC_USART3_IRQ39_ENABLE					SET_BIT(NVIC_ISER1,(USART3_IRQ-32));

//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC disable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define NVIC_EXTI0_IRQ_DISABLE						SET_BIT(NVIC_ICER0,EXTI0_IRQ);
#define NVIC_EXTI1_IRQ_DISABLE						SET_BIT(NVIC_ICER0,EXTI1_IRQ);
#define NVIC_EXTI2_IRQ_DISABLE						SET_BIT(NVIC_ICER0,EXTI2_IRQ);
#define NVIC_EXTI3_IRQ_DISABLE						SET_BIT(NVIC_ICER0,EXTI3_IRQ);
#define NVIC_EXTI4_IRQ_DISABLE						SET_BIT(NVIC_ICER0,EXTI4_IRQ);
#define NVIC_EXTI9_5_IRQ_DISABLE					SET_BIT(NVIC_ICER0,EXTI5_IRQ);
#define NVIC_EXTI15_10_IRQ_DISABLE					SET_BIT(NVIC_ICER1,(EXTI10_IRQ-32));

//disable USART interrupts
#define NVIC_USART1_IRQ37_DISABLE					SET_BIT(NVIC_ICER1,(USART1_IRQ-32));
#define NVIC_USART2_IRQ38_DISABLE					SET_BIT(NVIC_ICER1,(USART2_IRQ-32));
#define NVIC_USART3_IRQ39_DISABLE					SET_BIT(NVIC_ICER1,(USART3_IRQ-32));

//======================================================================


#endif /* STM32F103XX6_H_ */

