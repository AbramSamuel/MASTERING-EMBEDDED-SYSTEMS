/*
 * STM32F103C6_SPI_DRICER.h
 *
 *  Created on: Oct 10, 2023
 *      Author: ABRAM
 */

#ifndef MCAL_SPI_STM32F103C6_SPI_DRIVER_H_
#define MCAL_SPI_STM32F103C6_SPI_DRIVER_H_

#include "STM32F103xx6.h"
#include "STM32F103C6_GPIO_DRIVER.h"
#include "STM32F103C6_EXTI_DRIVER.h"
#include "STM32F103C6_RCC_DRIVER.h"

struct S_IRQ_Source
{
	uint8_t TXE:1;
	uint8_t RXNE:1;
	uint8_t ERRI:1;
	uint8_t Reserved:5;
};

typedef struct
{
	/*
	 * This determine if Device Mode is Master or Slave
	 * it must specify according to @ref SPI_Device_Mode_define
	 */
	uint16_t SPI_Device_Mode;

	/*
	 * This determine if SPI work as Full-Duplex or Half-Duplex or Simplex
	 * it must specify according to @ref SPI_Communication_Mode_define
	 */
	uint16_t SPI_Communication_Mode;

	/*
	 * This determine the first bit we will send --> MSB or LSB
	 * it must specify according to @ref SPI_Frame_Format_define
	 */
	uint16_t SPI_Frame_Format;

	/*
	 * This determine Data Size --> 8 or 16 bit
	 * it must specify according to @ref SPI_Data_Size_define
	 */
	uint16_t SPI_Data_Size;

	/*
	 * This determine Clock Polarity --> 0 or 1 when it's idle
	 * it must specify according to @ref SPI_Clock_Polarity_define
	 */
	uint16_t SPI_Clock_Polarity;

	/*
	 * This determine Clock Phase --> at 1st edge or 2nd edge data capture
	 * it must specify according to @ref SPI_Clock_Phase_define
	 */
	uint16_t SPI_Clock_Phase;

	/*
	 * This determine the clock speed of SPI by divide it to the prescalar
	 * it must specify according to @ref SPI_BuadRate_PreScalar_define
	 */
	uint16_t SPI_BuadRate_PreScalar;

	/*
	 * This determine Slave Select NSS --> By Software or Hardware
	 * it must specify according to @ref SPI_NSS_define
	 */
	uint16_t SPI_NSS;

	/*
	 * This determine if we need to enable interrupts
	 * it must specify according to @ref SPI_IRQ_Enable_define
	 */
	uint16_t SPI_IRQ_Enable;

	/*
	 * This is a pointer to ISR that will execute when interrupt is happened
	 */
	void (*PF_IRQ_CallBack)(struct S_IRQ_Source irq_src);

}SPI_Configuration_t;

//======================================================================

//-----------------------------
//Macros Configuration References
//-----------------------------

//************************************************************************************
//@ref SPI_Device_Mode_define
//Bit 2 MSTR: Master selection --> in CR1
#define SPI_Device_Mode_Slave											(uint32_t)(0)	//0: Slave configuration
#define SPI_Device_Mode_Master											(uint32_t)(1 << 2)	//1: Master configuration
//************************************************************************************

//************************************************************************************
//@ref SPI_Communication_Mode_define
/*
 * -------------------------------------------------------
 * 2Line & Full-Duplex		--> 0 on BIDIMODE & 0 on RXONLY
 * 2Line & Rx only			--> 0 on BIDIMODE & 1 on RXONLY
 * 1Line & Tx only			--> 1 on BIDIMODE & 0 on BIDIOE
 * 1Line & Rx only			--> 1 on BIDIMODE & 1 on BIDIOE
 * -------------------------------------------------------
 * Bit 15 BIDIMODE: Bidirectional data mode enable		--> CR1
 * 0: 2-line unidirectional data mode selected
 * 1: 1-line bidirectional data mode selected
 * -------------------------------------------------------
 * Bit 14 BIDIOE: Output enable in bidirectional mode	--> CR1
 * This bit combined with the BIDImode bit selects the direction of transfer in bidirectional mode
 * 0: Output disabled (receive-only mode)
 * 1: Output enabled (transmit-only mode)
 * -------------------------------------------------------
 * Bit 10 RXONLY: Receive only							--> CR1
 * This bit combined with the BIDImode bit selects the direction of transfer in 2-line
 * unidirectional mode. This bit is also useful in a multislave system in which this particular
 * slave is not accessed, the output from the accessed slave is not corrupted.
 * 0: Full duplex (Transmit and receive)
 * 1: Output disabled (Receive-only mode)
 * -------------------------------------------------------
 */
#define SPI_Communication_Mode_2Line_FD									(uint32_t)(0)
#define SPI_Communication_Mode_2Line_Rxonly								(uint32_t)(1 << 10)
#define SPI_Communication_Mode_1Line_Txonly								(uint32_t)(1 << 15)
#define SPI_Communication_Mode_1Line_Rxonly								(uint32_t)((1 << 15) | (1 << 14))
//************************************************************************************

//************************************************************************************
//@ref SPI_Frame_Format_define
//Bit 7 LSBFIRST: Frame format		--> CR1
#define SPI_Frame_Format_MSB_First										(uint32_t)(0)	//0: MSB transmitted first
#define SPI_Frame_Format_LSB_First										(uint32_t)(1 << 7)	//1: LSB transmitted first
//************************************************************************************

//************************************************************************************
//@ref SPI_Data_Size_define
//Bit 11 DFF: Data frame format		--> CR1
//Note: This bit should be written only when SPI is disabled (SPE = ‘0’) for correct operation
#define SPI_Data_Size_8B												(uint32_t)(0)	//0: 8-bit data frame format
#define SPI_Data_Size_16B												(uint32_t)(1 << 11)	//1: 16-bit data frame format
//************************************************************************************

//************************************************************************************
//@ref SPI_Clock_Polarity_define
//Bit1 CPOL: Clock polarity			--> CR1
#define SPI_Clock_Polarity_low_idle										(uint32_t)(0)	//0: CK to 0 when idle
#define SPI_Clock_Polarity_high_idle									(uint32_t)(1 << 1)	//1: CK to 1 when idle
//************************************************************************************

//************************************************************************************
//@ref SPI_Clock_Phase_define
//Bit 0 CPHA: Clock phase			--> CR1
#define SPI_Clock_Phase_1st_Edge										(uint32_t)(0)	//0: The first clock transition is the first data capture edge
#define SPI_Clock_Phase_2nd_Edge										(uint32_t)(1 << 0)	//1: The second clock transition is the first data capture edge
//************************************************************************************

//************************************************************************************
//@ref SPI_BuadRate_PreScalar_define
//Bits 5:3 BR[2:0]: Baud rate control		--> CR1
#define SPI_BaudRate_PreScalar_Divide_2									(uint32_t)(0b000 << 3)	//000: fPCLK/2
#define SPI_BaudRate_PreScalar_Divide_4									(uint32_t)(0b001 << 3)	//001: fPCLK/4
#define SPI_BaudRate_PreScalar_Divide_8									(uint32_t)(0b010 << 3)	//010: fPCLK/8
#define SPI_BaudRate_PreScalar_Divide_16								(uint32_t)(0b011 << 3)	//011: fPCLK/16
#define SPI_BaudRate_PreScalar_Divide_32								(uint32_t)(0b100 << 3)	//100: fPCLK/32
#define SPI_BaudRate_PreScalar_Divide_64								(uint32_t)(0b101 << 3)	//101: fPCLK/64
#define SPI_BaudRate_PreScalar_Divide_128								(uint32_t)(0b110 << 3)	//110: fPCLK/128
#define SPI_BaudRate_PreScalar_Divide_256								(uint32_t)(0b111 << 3)	//111: fPCLK/256
//************************************************************************************

//************************************************************************************
//@ref SPI_NSS_define
/*
 * -------------------------------------------------------
 * ============================
 * by Software
 * 	1 on SSM
 *	NSS value get from SSI
 * ============================
 * by Hardware
 * 	0 on SSM
 * 	Output:
 * 	enabled 	--> 1 on SSOE
 * 	disabled	--> 0 on SSOE
 * ============================
 * -------------------------------------------------------
 * Bit 9 SSM: Software slave management		--> CR1
 * When the SSM bit is set, the NSS pin input is replaced with the value from the SSI bit.
 * 0: Software slave management disabled
 * 1: Software slave management enabled
 * -------------------------------------------------------
 * Bit 8 SSI: Internal slave select			--> CR1
 * This bit has an effect only when the SSM bit is set. The value of this bit is forced onto the
 * NSS pin and the IO value of the NSS pin is ignored.
 * -------------------------------------------------------
 * Bit 2 SSOE: SS output enable				--> CR2
 * 0: SS output is disabled in master mode and the cell can work in multimaster configuration
 * 1: SS output is enabled in master mode and when the cell is enabled. The cell cannot work
 * in a multimaster environment.
 * -------------------------------------------------------
 */
//Hardware --> CR2
#define SPI_NSS_Hardware_Slave											(uint32_t)(0)			//0: Software slave management disabled (Hardware enabled)
#define SPI_NSS_Hardware_Master_SS_Output_Enable						(uint32_t)(1 << 2)		//1: SS output is enabled --> Bit 2 SSOE: SS output enable & 0 on Bit 9 SSM
#define SPI_NSS_Hardware_Master_SS_Output_Disable						~((uint32_t)(1 << 2))	//0: SS output is disabled --> Bit 2 SSOE: SS output enable & 0 on Bit 9 SSM
//Software --> CR1
#define SPI_NSS_Software_Internal_slave_select_Enable					(uint32_t)((1 << 9) | (1 << 8))	//1: Software slave management enabled & 1 on Bit 8 SSI: Internal slave select to enable SSI
#define SPI_NSS_Software_Internal_slave_select_Disable					(uint32_t)(1 << 9) 	//1: Software slave management enabled & 0 on Bit 8 SSI: Internal slave select to disable SSI
//************************************************************************************

//************************************************************************************
//@ref SPI_IRQ_Enable_define
//TXEIE(7) & RXNEIE(6) & ERRIE(5) --> CR2
#define SPI_IRQ_Enable_NONE												(uint32_t)(0)
#define SPI_IRQ_Enable_TXEIE											(uint32_t)(1 << 7)	//Bit 7 TXEIE: Tx buffer empty interrupt enable
#define SPI_IRQ_Enable_RXNEIE											(uint32_t)(1 << 6)	//Bit 6 RXNEIE: RX buffer not empty interrupt enable
#define SPI_IRQ_Enable_ERRIE											(uint32_t)(1 << 5)	//Bit 5 ERRIE: Error interrupt enable
//************************************************************************************

//************************************************************************************
//************************************************************************************

//======================================================================

enum SPI_Polling_Mechnism
{
	Polling_Enable,
	Polling_Disable
};

//======================================================================
/*
 * ======================================================================
 * 			APIs Supported by "MCAL SPI DRIVER"
 * ======================================================================
 */
void MCAL_SPI_Init(SPI_TypeDef *SPIx, SPI_Configuration_t *SPI_Config);

void MCAL_SPI_DeInit(SPI_TypeDef *SPIx);

void MCAL_GPIO_SPI_Set_Pins(SPI_TypeDef *SPIx);

void MCAL_SPI_SendData(SPI_TypeDef *SPIx, uint16_t *pTx_Buffer, enum SPI_Polling_Mechnism polling_state);

void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx, uint16_t *pRx_Buffer, enum SPI_Polling_Mechnism polling_state);

void MCAL_SPI_Tx_Rx(SPI_TypeDef *SPIx, uint16_t *pTx_Buffer, enum SPI_Polling_Mechnism polling_state);

#endif /* MCAL_SPI_STM32F103C6_SPI_DRIVER_H_ */
