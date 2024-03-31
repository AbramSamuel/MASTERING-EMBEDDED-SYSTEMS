/*
 * STM32F103xx6.h
 *
 *  Created on: Sep 15, 2023
 *      Author: ABRAM
 */

#ifndef STM32F103XX6_H_
#define STM32F103XX6_H_

//---------------------------------------------------------------------------------------------------
//Includes
//---------------------------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdint.h>


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

//SPI1
#define SPI1_BASE									0x40013000UL


//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------

//USART2
#define USART2_BASE									0x40004400UL

//USART3
#define USART3_BASE									0x40004800UL

//SPI2
#define SPI2_BASE									0x40003800UL

//I2C1
#define I2C1_BASE									0x40005400UL

//I2C2
#define I2C2_BASE									0x40005800UL

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
//Peripheral register: SPI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;
}SPI_TypeDef;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: I2C
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
}I2C_TypeDef;


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

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: SPI
//-*-*-*-*-*-*-*-*-*-*-*
#define SPI1										((SPI_TypeDef *)SPI1_BASE)
#define SPI2										((SPI_TypeDef *)SPI2_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: I2C
//-*-*-*-*-*-*-*-*-*-*-*
#define I2C1										((I2C_TypeDef *)I2C1_BASE)
#define I2C2										((I2C_TypeDef *)I2C2_BASE)

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

//enable clock for SPI				PCLK2 --> SPI1		& 	PCLK1 --> SPI2
#define RCC_SPI1_CLK_EN()							SET_BIT(RCC->APB2ENR,12)
#define RCC_SPI2_CLK_EN()							SET_BIT(RCC->APB1ENR,14)

//enable clock for I2C				PCLK1 --> I2C1 & I2C2
#define RCC_I2C1_CLK_EN()							SET_BIT(RCC->APB1ENR,21)
#define RCC_I2C2_CLK_EN()							SET_BIT(RCC->APB1ENR,22)

//reset clock for USART
#define RCC_USART1_Reset()							SET_BIT(RCC->APB2RSTR,14)
#define RCC_USART2_Reset()							SET_BIT(RCC->APB1RSTR,17)
#define RCC_USART3_Reset()							SET_BIT(RCC->APB1RSTR,18)

//reset clock for SPI
#define RCC_SPI1_Reset()							SET_BIT(RCC->APB2RSTR,12)
#define RCC_SPI2_Reset()							SET_BIT(RCC->APB1RSTR,14)

//reset clock for I2C
#define RCC_I2C1_Reset()							SET_BIT(RCC->APB1RSTR,21)
#define RCC_I2C2_Reset()							SET_BIT(RCC->APB1RSTR,22)

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

//SPI IRQ
#define SPI1_IRQ									35
#define SPI2_IRQ									36

//I2C IRQ
#define I2C1_EV_IRQ									31
#define I2C1_ER_IRQ									32
#define I2C2_EV_IRQ									33
#define I2C2_ER_IRQ									34

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

//enable SPI interrupts
#define NVIC_SPI1_IRQ35_ENABLE						SET_BIT(NVIC_ISER1,(SPI1_IRQ-32));
#define NVIC_SPI2_IRQ36_ENABLE						SET_BIT(NVIC_ISER1,(SPI2_IRQ-32));

//enable I2C interrupts
#define NVIC_I2C1_EV_IRQ31_ENABLE					SET_BIT(NVIC_ISER0,I2C1_EV_IRQ);
#define NVIC_I2C1_ER_IRQ32_ENABLE					SET_BIT(NVIC_ISER1,(I2C1_ER_IRQ-32));
#define NVIC_I2C2_EV_IRQ33_ENABLE					SET_BIT(NVIC_ISER1,(I2C2_EV_IRQ-32));
#define NVIC_I2C2_ER_IRQ34_ENABLE					SET_BIT(NVIC_ISER1,(I2C2_ER_IRQ-32));

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

//disable SPI interrupts
#define NVIC_SPI1_IRQ35_DISABLE						SET_BIT(NVIC_ICER1,(SPI1_IRQ-32));
#define NVIC_SPI2_IRQ36_DISABLE						SET_BIT(NVIC_ICER1,(SPI2_IRQ-32));

//disable I2C interrupts
#define NVIC_I2C1_EV_IRQ31_DISABLE					SET_BIT(NVIC_ICER0,I2C1_EV_IRQ);
#define NVIC_I2C1_ER_IRQ32_DISABLE					SET_BIT(NVIC_ICER1,(I2C1_ER_IRQ-32));
#define NVIC_I2C2_EV_IRQ33_DISABLE					SET_BIT(NVIC_ICER1,(I2C2_EV_IRQ-32));
#define NVIC_I2C2_ER_IRQ34_DISABLE					SET_BIT(NVIC_ICER1,(I2C2_ER_IRQ-32));

//======================================================================

/********************************************************/
/********************************************************/
/********************************************************/
/*******************  Bit definition  ********************/
/********************************************************/
/********************************************************/


/*******************  Bit definition for I2C_CR1 register  ********************/
#define I2C_CR1_PE_Pos                      (0U)
#define I2C_CR1_PE_Msk                      (0x1UL << I2C_CR1_PE_Pos)           /*!< 0x00000001 */
#define I2C_CR1_PE                          I2C_CR1_PE_Msk                     /*!< Peripheral Enable */
#define I2C_CR1_SMBUS_Pos                   (1U)
#define I2C_CR1_SMBUS_Msk                   (0x1UL << I2C_CR1_SMBUS_Pos)        /*!< 0x00000002 */
#define I2C_CR1_SMBUS                       I2C_CR1_SMBUS_Msk                  /*!< SMBus Mode */
#define I2C_CR1_SMBTYPE_Pos                 (3U)
#define I2C_CR1_SMBTYPE_Msk                 (0x1UL << I2C_CR1_SMBTYPE_Pos)      /*!< 0x00000008 */
#define I2C_CR1_SMBTYPE                     I2C_CR1_SMBTYPE_Msk                /*!< SMBus Type */
#define I2C_CR1_ENARP_Pos                   (4U)
#define I2C_CR1_ENARP_Msk                   (0x1UL << I2C_CR1_ENARP_Pos)        /*!< 0x00000010 */
#define I2C_CR1_ENARP                       I2C_CR1_ENARP_Msk                  /*!< ARP Enable */
#define I2C_CR1_ENPEC_Pos                   (5U)
#define I2C_CR1_ENPEC_Msk                   (0x1UL << I2C_CR1_ENPEC_Pos)        /*!< 0x00000020 */
#define I2C_CR1_ENPEC                       I2C_CR1_ENPEC_Msk                  /*!< PEC Enable */
#define I2C_CR1_ENGC_Pos                    (6U)
#define I2C_CR1_ENGC_Msk                    (0x1UL << I2C_CR1_ENGC_Pos)         /*!< 0x00000040 */
#define I2C_CR1_ENGC                        I2C_CR1_ENGC_Msk                   /*!< General Call Enable */
#define I2C_CR1_NOSTRETCH_Pos               (7U)
#define I2C_CR1_NOSTRETCH_Msk               (0x1UL << I2C_CR1_NOSTRETCH_Pos)    /*!< 0x00000080 */
#define I2C_CR1_NOSTRETCH                   I2C_CR1_NOSTRETCH_Msk              /*!< Clock Stretching Disable (Slave mode) */
#define I2C_CR1_START_Pos                   (8U)
#define I2C_CR1_START_Msk                   (0x1UL << I2C_CR1_START_Pos)        /*!< 0x00000100 */
#define I2C_CR1_START                       I2C_CR1_START_Msk                  /*!< Start Generation */
#define I2C_CR1_STOP_Pos                    (9U)
#define I2C_CR1_STOP_Msk                    (0x1UL << I2C_CR1_STOP_Pos)         /*!< 0x00000200 */
#define I2C_CR1_STOP                        I2C_CR1_STOP_Msk                   /*!< Stop Generation */
#define I2C_CR1_ACK_Pos                     (10U)
#define I2C_CR1_ACK_Msk                     (0x1UL << I2C_CR1_ACK_Pos)          /*!< 0x00000400 */
#define I2C_CR1_ACK                         I2C_CR1_ACK_Msk                    /*!< Acknowledge Enable */
#define I2C_CR1_POS_Pos                     (11U)
#define I2C_CR1_POS_Msk                     (0x1UL << I2C_CR1_POS_Pos)          /*!< 0x00000800 */
#define I2C_CR1_POS                         I2C_CR1_POS_Msk                    /*!< Acknowledge/PEC Position (for data reception) */
#define I2C_CR1_PEC_Pos                     (12U)
#define I2C_CR1_PEC_Msk                     (0x1UL << I2C_CR1_PEC_Pos)          /*!< 0x00001000 */
#define I2C_CR1_PEC                         I2C_CR1_PEC_Msk                    /*!< Packet Error Checking */
#define I2C_CR1_ALERT_Pos                   (13U)
#define I2C_CR1_ALERT_Msk                   (0x1UL << I2C_CR1_ALERT_Pos)        /*!< 0x00002000 */
#define I2C_CR1_ALERT                       I2C_CR1_ALERT_Msk                  /*!< SMBus Alert */
#define I2C_CR1_SWRST_Pos                   (15U)
#define I2C_CR1_SWRST_Msk                   (0x1UL << I2C_CR1_SWRST_Pos)        /*!< 0x00008000 */
#define I2C_CR1_SWRST                       I2C_CR1_SWRST_Msk                  /*!< Software Reset */
/*******************  Bit definition for I2C_CR2 register  ********************/
#define I2C_CR2_FREQ_Pos                    (0U)
#define I2C_CR2_FREQ_Msk                    (0x3FUL << I2C_CR2_FREQ_Pos)        /*!< 0x0000003F */
#define I2C_CR2_FREQ                        I2C_CR2_FREQ_Msk                   /*!< FREQ[5:0] bits (Peripheral Clock Frequency) */
#define I2C_CR2_ITERREN_Pos                 (8U)
#define I2C_CR2_ITERREN_Msk                 (0x1UL << I2C_CR2_ITERREN_Pos)      /*!< 0x00000100 */
#define I2C_CR2_ITERREN                     I2C_CR2_ITERREN_Msk                /*!< Error Interrupt Enable */
#define I2C_CR2_ITEVTEN_Pos                 (9U)
#define I2C_CR2_ITEVTEN_Msk                 (0x1UL << I2C_CR2_ITEVTEN_Pos)      /*!< 0x00000200 */
#define I2C_CR2_ITEVTEN                     I2C_CR2_ITEVTEN_Msk                /*!< Event Interrupt Enable */
#define I2C_CR2_ITBUFEN_Pos                 (10U)
#define I2C_CR2_ITBUFEN_Msk                 (0x1UL << I2C_CR2_ITBUFEN_Pos)      /*!< 0x00000400 */
#define I2C_CR2_ITBUFEN                     I2C_CR2_ITBUFEN_Msk                /*!< Buffer Interrupt Enable */
#define I2C_CR2_DMAEN_Pos                   (11U)
#define I2C_CR2_DMAEN_Msk                   (0x1UL << I2C_CR2_DMAEN_Pos)        /*!< 0x00000800 */
#define I2C_CR2_DMAEN                       I2C_CR2_DMAEN_Msk                  /*!< DMA Requests Enable */
#define I2C_CR2_LAST_Pos                    (12U)
#define I2C_CR2_LAST_Msk                    (0x1UL << I2C_CR2_LAST_Pos)         /*!< 0x00001000 */
#define I2C_CR2_LAST                        I2C_CR2_LAST_Msk                   /*!< DMA Last Transfer */
/*******************  Bit definition for I2C_OAR1 register  *******************/
#define I2C_OAR1_ADD_Pos                    (1U)
#define I2C_OAR1_ADDMODE_Pos				(15U)
#define I2C_OAR1_ADDMODE_Msk				(0x1UL << I2C_OAR1_ADDMODE_Pos)     /*!< 0x00008000 */
#define I2C_OAR1_ADDMODE					I2C_OAR1_ADDMODE_Msk                /*!< Addressing mode (slave mode) */
/*******************  Bit definition for I2C_OAR2 register  *******************/
#define I2C_OAR2_ENDUAL_Pos                 (0U)
#define I2C_OAR2_ENDUAL_Msk                 (0x1UL << I2C_OAR2_ENDUAL_Pos)      /*!< 0x00000001 */
#define I2C_OAR2_ENDUAL                     I2C_OAR2_ENDUAL_Msk                /*!< Dual addressing mode enable */
#define I2C_OAR2_ADD2_Pos                   (1U)
/*******************  Bit definition for I2C_SR1 register  ********************/
#define I2C_SR1_SB_Pos                      (0U)
#define I2C_SR1_SB_Msk                      (0x1UL << I2C_SR1_SB_Pos)           /*!< 0x00000001 */
#define I2C_SR1_SB                          I2C_SR1_SB_Msk                     /*!< Start Bit (Master mode) */
#define I2C_SR1_ADDR_Pos                    (1U)
#define I2C_SR1_ADDR_Msk                    (0x1UL << I2C_SR1_ADDR_Pos)         /*!< 0x00000002 */
#define I2C_SR1_ADDR                        I2C_SR1_ADDR_Msk                   /*!< Address sent (master mode)/matched (slave mode) */
#define I2C_SR1_BTF_Pos                     (2U)
#define I2C_SR1_BTF_Msk                     (0x1UL << I2C_SR1_BTF_Pos)          /*!< 0x00000004 */
#define I2C_SR1_BTF                         I2C_SR1_BTF_Msk                    /*!< Byte Transfer Finished */
#define I2C_SR1_ADD10_Pos                   (3U)
#define I2C_SR1_ADD10_Msk                   (0x1UL << I2C_SR1_ADD10_Pos)        /*!< 0x00000008 */
#define I2C_SR1_ADD10                       I2C_SR1_ADD10_Msk                  /*!< 10-bit header sent (Master mode) */
#define I2C_SR1_STOPF_Pos                   (4U)
#define I2C_SR1_STOPF_Msk                   (0x1UL << I2C_SR1_STOPF_Pos)        /*!< 0x00000010 */
#define I2C_SR1_STOPF                       I2C_SR1_STOPF_Msk                  /*!< Stop detection (Slave mode) */
#define I2C_SR1_RXNE_Pos                    (6U)
#define I2C_SR1_RXNE_Msk                    (0x1UL << I2C_SR1_RXNE_Pos)         /*!< 0x00000040 */
#define I2C_SR1_RXNE                        I2C_SR1_RXNE_Msk                   /*!< Data Register not Empty (receivers) */
#define I2C_SR1_TXE_Pos                     (7U)
#define I2C_SR1_TXE_Msk                     (0x1UL << I2C_SR1_TXE_Pos)          /*!< 0x00000080 */
#define I2C_SR1_TXE                         I2C_SR1_TXE_Msk                    /*!< Data Register Empty (transmitters) */
#define I2C_SR1_BERR_Pos                    (8U)
#define I2C_SR1_BERR_Msk                    (0x1UL << I2C_SR1_BERR_Pos)         /*!< 0x00000100 */
#define I2C_SR1_BERR                        I2C_SR1_BERR_Msk                   /*!< Bus Error */
#define I2C_SR1_ARLO_Pos                    (9U)
#define I2C_SR1_ARLO_Msk                    (0x1UL << I2C_SR1_ARLO_Pos)         /*!< 0x00000200 */
#define I2C_SR1_ARLO                        I2C_SR1_ARLO_Msk                   /*!< Arbitration Lost (master mode) */
#define I2C_SR1_AF_Pos                      (10U)
#define I2C_SR1_AF_Msk                      (0x1UL << I2C_SR1_AF_Pos)           /*!< 0x00000400 */
#define I2C_SR1_AF                          I2C_SR1_AF_Msk                     /*!< Acknowledge Failure */
#define I2C_SR1_OVR_Pos                     (11U)
#define I2C_SR1_OVR_Msk                     (0x1UL << I2C_SR1_OVR_Pos)          /*!< 0x00000800 */
#define I2C_SR1_OVR                         I2C_SR1_OVR_Msk                    /*!< Overrun/Underrun */
#define I2C_SR1_PECERR_Pos                  (12U)
#define I2C_SR1_PECERR_Msk                  (0x1UL << I2C_SR1_PECERR_Pos)       /*!< 0x00001000 */
#define I2C_SR1_PECERR                      I2C_SR1_PECERR_Msk                 /*!< PEC Error in reception */
#define I2C_SR1_TIMEOUT_Pos                 (14U)
#define I2C_SR1_TIMEOUT_Msk                 (0x1UL << I2C_SR1_TIMEOUT_Pos)      /*!< 0x00004000 */
#define I2C_SR1_TIMEOUT                     I2C_SR1_TIMEOUT_Msk                /*!< Timeout or Tlow Error */
#define I2C_SR1_SMBALERT_Pos                (15U)
#define I2C_SR1_SMBALERT_Msk                (0x1UL << I2C_SR1_SMBALERT_Pos)     /*!< 0x00008000 */
#define I2C_SR1_SMBALERT                    I2C_SR1_SMBALERT_Msk               /*!< SMBus Alert */

/*******************  Bit definition for I2C_SR2 register  ********************/
#define I2C_SR2_MSL_Pos                     (0U)
#define I2C_SR2_MSL_Msk                     (0x1UL << I2C_SR2_MSL_Pos)          /*!< 0x00000001 */
#define I2C_SR2_MSL                         I2C_SR2_MSL_Msk                    /*!< Master/Slave */
#define I2C_SR2_BUSY_Pos                    (1U)
#define I2C_SR2_BUSY_Msk                    (0x1UL << I2C_SR2_BUSY_Pos)         /*!< 0x00000002 */
#define I2C_SR2_BUSY                        I2C_SR2_BUSY_Msk                   /*!< Bus Busy */
#define I2C_SR2_TRA_Pos                     (2U)
#define I2C_SR2_TRA_Msk                     (0x1UL << I2C_SR2_TRA_Pos)          /*!< 0x00000004 */
#define I2C_SR2_TRA                         I2C_SR2_TRA_Msk                    /*!< Transmitter/Receiver */
#define I2C_SR2_GENCALL_Pos                 (4U)
#define I2C_SR2_GENCALL_Msk                 (0x1UL << I2C_SR2_GENCALL_Pos)      /*!< 0x00000010 */
#define I2C_SR2_GENCALL                     I2C_SR2_GENCALL_Msk                /*!< General Call Address (Slave mode) */
#define I2C_SR2_SMBDEFAULT_Pos              (5U)
#define I2C_SR2_SMBDEFAULT_Msk              (0x1UL << I2C_SR2_SMBDEFAULT_Pos)   /*!< 0x00000020 */
#define I2C_SR2_SMBDEFAULT                  I2C_SR2_SMBDEFAULT_Msk             /*!< SMBus Device Default Address (Slave mode) */
#define I2C_SR2_SMBHOST_Pos                 (6U)
#define I2C_SR2_SMBHOST_Msk                 (0x1UL << I2C_SR2_SMBHOST_Pos)      /*!< 0x00000040 */
#define I2C_SR2_SMBHOST                     I2C_SR2_SMBHOST_Msk                /*!< SMBus Host Header (Slave mode) */
#define I2C_SR2_DUALF_Pos                   (7U)
#define I2C_SR2_DUALF_Msk                   (0x1UL << I2C_SR2_DUALF_Pos)        /*!< 0x00000080 */
#define I2C_SR2_DUALF                       I2C_SR2_DUALF_Msk                  /*!< Dual Flag (Slave mode) */
#define I2C_SR2_PEC_Pos                     (8U)
#define I2C_SR2_PEC_Msk                     (0xFFUL << I2C_SR2_PEC_Pos)         /*!< 0x0000FF00 */
#define I2C_SR2_PEC                         I2C_SR2_PEC_Msk                    /*!< Packet Error Checking Register */
/*******************  Bit definition for I2C_CCR register  *******************/
#define I2C_CCR_DUTY_Pos					(14U)
#define I2C_CCR_DUTY_Msk					(0x1UL << I2C_CCR_DUTY_Pos)     /*!< 0x00008000 */
#define I2C_CCR_DUTY						I2C_CCR_DUTY_Msk                /*!< Fm mode duty cycle */
#define I2C_CCR_F_or_S_Pos					(15U)
#define I2C_CCR_F_or_S_Msk					(0x1UL << I2C_CCR_F_or_S_Pos)     /*!< 0x00008000 */
#define I2C_CCR_F_or_S						I2C_CCR_F_or_S_Msk                /*!< I2C master mode selection */

#endif /* STM32F103XX6_H_ */

