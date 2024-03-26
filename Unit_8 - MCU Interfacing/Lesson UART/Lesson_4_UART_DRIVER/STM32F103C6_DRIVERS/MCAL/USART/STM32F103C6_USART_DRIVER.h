/*
 * STM32F103C6_USART_DRIVER.h
 *
 *  Created on: Oct 4, 2023
 *      Author: ABRAM
 */

#ifndef MCAL_USART_STM32F103C6_USART_DRIVER_H_
#define MCAL_USART_STM32F103C6_USART_DRIVER_H_

#include "STM32F103xx6.h"
#include "STM32F103C6_GPIO_DRIVER.h"
#include "STM32F103C6_EXTI_DRIVER.h"
#include "STM32F103C6_RCC_DRIVER.h"



//-*-*-*-*-*-*-*-*-*-*-*-
//USART Configuration:
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	/* This specify SART mode --> Tx or Rx or TxRx
	 * it must specify according to @ref UART_MODE_define */
	uint8_t UART_MODE;

	/* This specify UART Payload length --> data length
	 * it must specify according to @ref UART_Payload_length_define */
	uint8_t UART_Payload_length;

	/* This specify UART num of stop bits --> 1 or 2
	 * it must specify according to @ref UART_Num_Stop_Bits_define */
	uint8_t UART_Num_Stop_Bits;

	/* This specify UART Parity --> enable/disable parity and if enable --> even/odd parity
	 * it must specify according to @ref UART_Parity_define */
	uint8_t UART_Parity;

	/* This specify USART BaudRate
	 * it must specify according to @ref UART_BaudRate_define */
	uint32_t UART_BaudRate;

	/* This specify UART Hardware flow control --> enable/disable CTS, RTS
	 * it must specify according to @ref UART_HW_FLOW_CTL_define */
	uint8_t UART_HW_FLOW_CTL;

	/* This specify UART IRQ --> enable/disable
	 * it must specify according to @ref UART_IRQ_Enable_define */
	uint8_t UART_IRQ_Enable;

	/* This specify UART ISR */
	void (* UART_PF_IRQ_CallBack)(void);

}UART_Configuration_t;

//======================================================================

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref UART_MODE_define
//Bit2,3 -->  (USART_CR1)
#define UART_MODE_Tx										(uint32_t)(1 << 3)	//Bit 3 TE: Transmitter enable
#define UART_MODE_Rx										(uint32_t)(1 << 2)	//Bit 2 RE: Receiver enable
#define UART_MODE_Tx_Rx										(uint32_t)((1 << 3) | (1 << 2))

//@ref UART_Payload_length_define
//Bit 12 M: Word length --> (USART_CR1)
#define UART_Payload_length_8B								(uint32_t)(0)		//0: 1 Start bit, 8 Data bits, n Stop bit
#define UART_Payload_length_9B								(uint32_t)(1 << 12)	//1: 1 Start bit, 9 Data bits, n Stop bit

//@ref UART_Num_Stop_Bits_define
//Bits 13:12 STOP: STOP bits --> (USART_CR2)
#define UART_Num_Stop_Bits_half_bit							(uint32_t)(0b01 << 12)	//01: 0.5 Stop bit
#define UART_Num_Stop_Bits_one_bit							(uint32_t)(0b00 << 12)	//00: 1 Stop bit
#define UART_Num_Stop_Bits_one_half_bit						(uint32_t)(0b11 << 12)	//11: 1.5 Stop bit
#define UART_Num_Stop_Bits_two_bit							(uint32_t)(0b10 << 12)	//10: 2 Stop bits

//@ref UART_Parity_define
//Bit 10 PCE: Parity control enable			Bit 9 PS: Parity selection		--> (USART_CR1)
#define UART_Parity_NONE									(uint32_t)(0)						//0: Parity control disabled
#define UART_Parity_EVEN									(uint32_t)(1 << 10)					//1: Parity control enabled && 0: Even parity
#define UART_Parity_ODD										(uint32_t)((1 << 10) | (1 << 9))	//1: Parity control enabled && 1: Odd parity
/*
 * Note about parity: If the PCE bit is set in USART_CR1, then the MSB bit of the data
 * written in the data register is transmitted but is changed by the parity bit (even number of
 * “1s” if even parity is selected (PS=0) or an odd number of “1s” if odd parity is selected
 * (PS=1)). If the parity check fails, the PE flag is set in the USART_SR register and an
 * interrupt is generated if PEIE is set in the USART_CR1 register.
 */

//@ref UART_BaudRate_define
#define UART_BaudRate_2400									2400
#define UART_BaudRate_9600									9600
#define UART_BaudRate_19200									19200
#define UART_BaudRate_57600									57600
#define UART_BaudRate_115200								115200
#define UART_BaudRate_230400								230400
#define UART_BaudRate_460800								460800
#define UART_BaudRate_921600								921600
#define UART_BaudRate_2250000								2250000
#define UART_BaudRate_4500000								4500000


//@ref UART_HW_FLOW_CTL_define
#define UART_HW_FLOW_CTL_NONE								(uint32_t)(0)
#define UART_HW_FLOW_CTL_CTS								(uint32_t)(1 << 9)					//Bit 9 CTSE: CTS enable
#define UART_HW_FLOW_CTL_RTS								(uint32_t)(1 << 8)					//Bit 8 RTSE: RTS enable
#define UART_HW_FLOW_CTL_CTS_RTS							(uint32_t)((1 << 9) | (1 << 8))

//@ref UART_IRQ_Enable_define
#define UART_IRQ_Enable_NONE								(uint32_t)(0)
#define UART_IRQ_Enable_TXE                                 (uint32_t)(1 << 7)		//Transmit data register empty
#define UART_IRQ_Enable_TC                                  (uint32_t)(1 << 6)		//Transmission complete
#define UART_IRQ_Enable_RXNE                                (uint32_t)(1 << 5)		//Received data ready to be read
#define UART_IRQ_Enable_PE                                  (uint32_t)(1 << 8)		//Parity Error


//======================================================================

enum Polling_Mechnism
{
	enable,
	disable
};

//======================================================================

/*
 * Calculate BaudRate without using float
 * >> USARTDIV = fclk / (16 * Baudrate)
 * >> USARTDIV_MUL100 = uint32((100 *fclk ) / (16 * Baudrate) == (25 *fclk ) / (4* Baudrate) )
 * >> DIV_Mantissa_MUL100 = Integer Part (USARTDIV ) * 100
 * >> DIV_Mantissa = Integer Part (USARTDIV )
 * >> DIV_Fraction = (( USARTDIV_MUL100 - DIV_Mantissa_MUL100 ) * 16 ) / 100
 * */
#define USARTDIV(_PCLK_, _BAUDRATE_)						(uint32_t)(_PCLK_/(16 * _BAUDRATE_))
#define USARTDIV_MUL100(_PCLK_, _BAUDRATE_)					(uint32_t)((25 * _PCLK_) / (4 * _BAUDRATE_))
#define Mantissa_MUL100(_PCLK_, _BAUDRATE_)					(uint32_t)(USARTDIV(_PCLK_, _BAUDRATE_) * 100)
#define DIV_Mantissa(_PCLK_, _BAUDRATE_)					(uint32_t)(USARTDIV(_PCLK_, _BAUDRATE_))
#define DIV_Fraction(_PCLK_, _BAUDRATE_)					(uint32_t)(((USARTDIV_MUL100(_PCLK_, _BAUDRATE_) - Mantissa_MUL100(_PCLK_, _BAUDRATE_)) * 16) / 100)
#define UART_BRR_Register(_PCLK_, _BAUDRATE_)				(uint32_t)((DIV_Mantissa(_PCLK_, _BAUDRATE_) << 4) | (DIV_Fraction(_PCLK_, _BAUDRATE_) & 0xF))

//======================================================================

/*
 * ======================================================================
 * 			APIs Supported by "MCAL USART DRIVER"
 * ======================================================================
 */

void MCAL_UART_Init(USART_TypeDef *USARTx, UART_Configuration_t *UART_Config);
void MCAL_UART_DeInit(USART_TypeDef *USARTx);

void MCAL_UART_GPIO_Set_Pins(USART_TypeDef *USARTx);

void MCAL_UART_SendData(USART_TypeDef *USARTx, uint16_t *pTxBuffer, enum Polling_Mechnism PollingEn);
void MCAL_UART_ReceiveData(USART_TypeDef *USARTx, uint16_t *pRxBuffer, enum Polling_Mechnism PollingEn);

void MCAL_UART_WAIT_TC(USART_TypeDef *USARTx);


#endif /* MCAL_USART_STM32F103C6_USART_DRIVER_H_ */
