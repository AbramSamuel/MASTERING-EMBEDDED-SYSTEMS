/*
 * STM32F103C6_I2C_DRIVER.h
 *
 *  Created on: Feb 18, 2024
 *      Author: ABRAM
 */

#ifndef STM32F103C6_I2C_DRIVER_H_
#define STM32F103C6_I2C_DRIVER_H_

#include "STM32F103xx6.h"
#include "STM32F103C6_GPIO_DRIVER.h"
#include "STM32F103C6_RCC_DRIVER.h"


struct S_I2C_Slave_Device_Address
{
	/* This specify the length of the slave address 7-bit or 10-bit
	 * it must specify according to @ref I2C_Slave_Address_Length_define */
	uint16_t				I2C_Slave_Address_Length;

	/* This specify that if we need to enable dual address for slave or disable it
	 * it must specify according to @ref I2C_Slave_Address_DUAL_define */
	uint16_t				I2C_Slave_Address_DUAL;

	/* This specify the primary address of the slave device */
	uint16_t				I2C_Primary_Slave_Address;

	/* This specify the secondary address of the slave device */
	uint16_t				I2C_Secondary_Slave_Address;
};

//======================================================================

typedef enum
{
	I2C_EV_STOP,
	I2C_ERROR_AF,
	I2C_EV_ADDR_Matched,
	I2C_EV_DATA_REQ,			//the APP layer should send the data (by using MCAL_I2C_Slave_Tx)
	I2C_EV_DATA_RCV				//the APP layer should read the data (by using MCAL_I2C_Slave_Rx)
}Slave_State_t;

//======================================================================

typedef struct
{
	/* This specify the Master_Mode_Selection --> Standard Mode or Fast Mode
	 * it must specify according to @ref I2C_Master_Mode_Selection_define */
	uint16_t				I2C_Master_Mode_Selection;

	/* This specify the clock of I2C
	 * The Maximum is 100 KHz in Standard mode & 400 KHz in Fast Mode
	 * it must specify according to @ref I2C_ClockSpeed_define */
	uint32_t				I2C_ClockSpeed;

	/* This specify that if we use it as I2C or SMBUS(System Management Bust)
	 * it must specify according to @ref I2C_Mode_define */
	uint16_t				I2C_Mode;

	/* This specify that if we need to enable Clock stretching or disable it
	 * it must specify according to @ref I2C_Clock_Stretching_define */
	uint16_t				I2C_Clock_Stretching;

	/* This specify that if we need to enable automatic acknowledge or disable it
	 * it must specify according to @ref I2C_ACK_Control_define */
	uint16_t				I2C_ACK_Control;

	/* This specify that if we need to enable general call or disable it
	 * it must specify according to @ref I2C_General_Call_Control_define */
	uint16_t				I2C_General_Call_Control;

	/* This specify some points about slave device:
	 * 			--> Slave Address Length
	 * 			--> Dual Address enable or not
	 * 			--> Primary Slave Address
	 * 			--> Secondary Slave Address */
	struct S_I2C_Slave_Device_Address	I2C_Slave_Device_Address;

	/* This is a pointer to callback function that will execute when we are in Slave mode depend on some states */
	void (* PF_Slave_Event_CallBack)(Slave_State_t state);

}I2C_Configuration_t;


//======================================================================

//-----------------------------
//Macros Configuration References
//-----------------------------

//********************************************************************************************************************************
//@ref I2C_Master_Mode_Selection_define
//Bit 15 F/S: I2C master mode selection (I2C_CCR)
//0: Sm mode I2C
//1: Fm mode I2C
#define I2C_Master_Mode_Selection_SM												(0)
#define I2C_Master_Mode_Selection_FM												I2C_CCR_F_or_S	// Fast Mode not supported yet
//********************************************************************************************************************************

//********************************************************************************************************************************
//@ref I2C_ClockSpeed_define
//Note: we configure the clock before we enable the peripheral
//Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
//		--> Bits 5:0 FREQ[5:0]: Peripheral clock frequency in I2C_CR2
//		--> The minimum allowed frequency is 2 MHz and cannot exceed 50 MHz
//Configure the clock control registers
//		--> Bits 11:0 CCR[11:0]: Clock control register in Fm/Sm mode (Master mode) in (I2C_CCR)
//		--> Controls the SCL clock in master mode.
//		--> Sm mode or SMBus:
//		--> Thigh = CCR * TPCLK1
//		--> Tlow = CCR * TPCLK1
//Configure the rise time register
//		--> Bits 5:0 TRISE[5:0]: Maximum rise time in Fm/Sm mode (Master mode) in (I2C_TRISE)
//		--> the maximum allowed SCL rise time is 1000 ns.
//		--> If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
//			therefore the TRISE[5:0] bits must be programmed with 09h.
//			(1000 ns / 125 ns = 8 + 1)
#define I2C_ClockSpeed_SM_50KHz														(50000U)
#define I2C_ClockSpeed_SM_100KHz													(100000U)
#define I2C_ClockSpeed_FM_200KHz													(200000U)	// Fast Mode not supported yet
#define I2C_ClockSpeed_FM_400KHz													(400000U)	// Fast Mode not supported yet
//********************************************************************************************************************************

//********************************************************************************************************************************
//@ref I2C_Mode_define
//Bit 1 SMBUS: SMBus mode in (I2C_CR1)
//0: I2C mode
//1: SMBus mode
#define I2C_Mode_I2C																(0)
#define I2C_Mode_SMBus																I2C_CR1_SMBUS
//********************************************************************************************************************************

//********************************************************************************************************************************
//I2C_Clock_Stretching_define
//Bit 7 NOSTRETCH: Clock stretching disable (Slave mode) in (I2C_CR1)
//This bit is used to disable clock stretching in slave mode when ADDR or BTF flag is set, until it is reset by software.
//0: Clock stretching enabled
//1: Clock stretching disabled
#define I2C_Clock_Stretching_Enable													(0)
#define I2C_Clock_Stretching_Disable												I2C_CR1_NOSTRETCH
//********************************************************************************************************************************

//********************************************************************************************************************************
//@ref I2C_ACK_Control_define
//Bit 10 ACK: Acknowledge enable in (I2C_CR1)
//This bit is set and cleared by software and cleared by hardware when PE=0.
//0: No acknowledge returned
//1: Acknowledge returned after a byte is received (matched address or data)
#define I2C_ACK_Control_Disable														(0)
#define I2C_ACK_Control_Enable														I2C_CR1_ACK
//********************************************************************************************************************************

//********************************************************************************************************************************
//@ref I2C_General_Call_Control_define
//Bit 6 ENGC: General call enable in (I2C_CR1)
//0: General call disabled. Address 00h is NACKed.
//1: General call enabled. Address 00h is ACKed.
#define I2C_General_Call_Control_Disable											(0)
#define I2C_General_Call_Control_Enable												I2C_CR1_ENGC
//********************************************************************************************************************************

//********************************************************************************************************************************
//@ref I2C_Slave_Address_Length_define
//Bit 15 ADDMODE Addressing mode (slave mode) in (I2C_OAR1)
//0: 7-bit slave address (10-bit address not acknowledged)
//1: 10-bit slave address (7-bit address not acknowledged)
#define I2C_Slave_Address_Length_7Bit												(0)
#define I2C_Slave_Address_Length_10Bit												I2C_OAR1_ADDMODE
//********************************************************************************************************************************

//********************************************************************************************************************************
//@ref I2C_Slave_Address_DUAL_define
//Bit 0 ENDUAL: Dual addressing mode enable in (I2C_OAR1)
//0: Only OAR1 is recognized in 7-bit addressing mode
//1: Both OAR1 and OAR2 are recognized in 7-bit addressing mode
#define I2C_Slave_Address_DUAL_Disable												(0)
#define I2C_Slave_Address_DUAL_Enable												I2C_OAR2_ENDUAL
//********************************************************************************************************************************

//********************************************************************************************************************************

//********************************************************************************************************************************

//======================================================================

#define I2C_EVENT_MASTER_BYTE_TRANSMITTING											((uint32_t)0x00070080) /* TRA, BUSY, MSL, TXE flags */

//======================================================================

//*******************************************************************************
typedef enum
{
	With_Stop,
	Without_Stop
}Stop_Generation;
//*******************************************************************************

//*******************************************************************************
typedef enum
{
	Start,
	Repeated_Start
}Start_State;
//*******************************************************************************

//*******************************************************************************
typedef enum
{
	Fun_disable,
	Fun_enable
}Functional_State;
//*******************************************************************************

//*******************************************************************************
typedef enum
{
	reset,
	set
}Flag_Status;
//*******************************************************************************

//*******************************************************************************
typedef enum
{
	I2C_FlAG_BUS_BUSY,
	EV5,	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
	EV6,	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	EV8_1, //TxE=1, shift register empty, data register empty, write Data1 in DR.
	EV8,  //EV8: TxE=1, shift register not empty, d. ata register empty, cleared by writing DR register
	EV7, //EV7: RxNE = 1 cleared by reading DR register
	MASTER_BYTE_TRANSMITTING = I2C_EVENT_MASTER_BYTE_TRANSMITTING //check TRA, BUSY, MSL, TXE flags
}Status;
//*******************************************************************************

//*******************************************************************************
typedef enum
{
	I2C_Direction_Transimitter,
	I2C_Direction_Receiver
}I2C_Direction;
//*******************************************************************************

//======================================================================
/*
 * ======================================================================
 * 			APIs Supported by "MCAL SPI DRIVER"
 * ======================================================================
 */

//*******************************************************************************
void MCAL_I2C_Init(I2C_TypeDef *I2Cx, I2C_Configuration_t *I2C_Config);
void MCAL_I2C_DeInit(I2C_TypeDef *I2Cx);
//*******************************************************************************

//*******************************************************************************
void MCAL_GPIO_I2C_Set_Pins(I2C_TypeDef *I2Cx);
//*******************************************************************************

//*******************************************************************************
//Master works with Polling Mechanism
void MCAL_I2C_Master_Tx(I2C_TypeDef *I2Cx, uint16_t Device_Address, uint8_t *Data_Out, uint16_t Data_Length, Stop_Generation stop, Start_State start);
void MCAL_I2C_Master_Rx(I2C_TypeDef *I2Cx, uint16_t Device_Address, uint8_t *Data_Out, uint16_t Data_Length, Stop_Generation stop, Start_State start);
//*******************************************************************************

//*******************************************************************************
//Slave works with Interrupt Mechanism
void MCAL_I2C_Slave_Tx(I2C_TypeDef *I2Cx, uint8_t Data);
uint8_t MCAL_I2C_Slave_Rx(I2C_TypeDef *I2Cx);
//*******************************************************************************

//*******************************************************************************
//Generic APIs
void I2C_Generate_Start_Condition(I2C_TypeDef *I2Cx, Functional_State state, Start_State start);
Flag_Status I2C_Get_Flag_Status(I2C_TypeDef *I2Cx, Status flag);
void I2C_Send_Address(I2C_TypeDef *I2Cx, uint16_t Address, I2C_Direction RW);
void I2C_Generate_Stop_Condition(I2C_TypeDef *I2Cx, Functional_State state);
void I2C_Acknowledge_Config(I2C_TypeDef *I2Cx, Functional_State state);
//*******************************************************************************




#endif /* STM32F103C6_I2C_DRIVER_H_ */
