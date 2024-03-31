/*
 * STM32F103C6_USART_DRIVER.c
 *
 *  Created on: Oct 4, 2023
 *      Author: ABRAM
 */

#include "STM32F103C6_USART_DRIVER.h"

/*
 * ======================================================================
 * 					Generic Variables
 * ======================================================================
 */

UART_Configuration_t *Gl_UART_CFG = NULL;
UART_Configuration_t *Gl_AUARTx_CFG[3] = {NULL, NULL, NULL};

/*
 * ======================================================================
 * 					Generic Functions
 * ======================================================================
 */


/*
 * ======================================================================
 * 								APIs
 * ======================================================================
 */


/**================================================================
 * @Fn			-MCAL_UART_Init
 * @brief 		-initialize UART
 * @param [in] 	-USARTx: it is an instance from USART (x --> 1..3)
 * @param [in] 	-UART_Config: it is a structure containing configuration of UART.
 * @retval 		-none
 * Note			-we implement Asynchronous mode
================================================================**/
void MCAL_UART_Init(USART_TypeDef *USARTx, UART_Configuration_t *UART_Config)
{
	uint32_t Pclk, BRR;

	Gl_UART_CFG = UART_Config;

	//Enable Clock for UART
	if(USARTx == USART1)
	{
		RCC_USART1_CLK_EN();
		Gl_AUARTx_CFG[0] = UART_Config;
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_CLK_EN();
		Gl_AUARTx_CFG[1] = UART_Config;
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_CLK_EN();
		Gl_AUARTx_CFG[2] = UART_Config;
	}

	//Enable the USART by writing the UE bit in USART_CR1 register to 1.
	//Bit 13 UE: USART enable
	USARTx->CR1 |= (1 << 13);

	//Set the UART MODE bit in USART_CR1
	USARTx->CR1 |= UART_Config->UART_MODE;

	//Program the M bit in USART_CR1 to define the word length
	USARTx->CR1 |= UART_Config->UART_Payload_length;

	//Program the number of stop bits in USART_CR2.
	USARTx->CR1 |= UART_Config->UART_Num_Stop_Bits;

	//Configure Parity
	USARTx->CR1 |= UART_Config->UART_Parity;

	//Configure Hardware Flow Control
	USARTx->CR1 |= UART_Config->UART_HW_FLOW_CTL;

	//Configure BaudRate (BRR)
	//Calculate the clock --> PCLK1 for USART2,3 & PCLK2 for USART1
	if(USARTx == USART1)
		Pclk = MCAL_RCC_GetPCLK2Freq();
	else if(USARTx == USART2 || USARTx == USART3)
		Pclk = MCAL_RCC_GetPCLK1Freq();

	BRR = UART_BRR_Register(Pclk, UART_Config->UART_BaudRate);
	USARTx->BRR = BRR;

	//Configuration of UART if it is enabled
	if(UART_Config->UART_IRQ_Enable != UART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= UART_Config->UART_IRQ_Enable;


		//Enable NVIC for UARTx IRQ
		if(USARTx == USART1)
		{
			NVIC_USART1_IRQ37_ENABLE;
		}
		else if(USARTx == USART2)
		{
			NVIC_USART2_IRQ38_ENABLE;
		}
		else if(USARTx == USART3)
		{
			NVIC_USART3_IRQ39_ENABLE;
		}

	}
}

/**================================================================
 * @Fn			-MCAL_UART_DeInit
 * @brief 		-Deinitialize UART
 * @param [in] 	-USARTx: it is an instance from USART (x --> 1..3)
 * @retval 		-none
 * Note			-we implement Asynchronous mode
================================================================**/
void MCAL_UART_DeInit(USART_TypeDef *USARTx)
{

	//Reset UART from RCC
	//Disable NVIC for UARTx IRQ
	if(USARTx == USART1)
	{
		RCC_USART1_Reset();
		NVIC_USART1_IRQ37_DISABLE;
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_Reset();
		NVIC_USART2_IRQ38_DISABLE;
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_Reset();
		NVIC_USART3_IRQ39_DISABLE;
	}

}


/**================================================================
 * @Fn			-MCAL_UART_SendData
 * @brief 		-Send data by using UART
 * @param [in] 	-USARTx: it is an instance from USART (x --> 1..3)
 * @param [in] 	-pTxBuffer: data buffer
 * @param [in] 	-PollingEn: enable polling or disable it
 * @retval 		-none
 * Note			-we implement Asynchronous mode
================================================================**/
void MCAL_UART_SendData(USART_TypeDef *USARTx, uint16_t *pTxBuffer, enum Polling_Mechnism PollingEn)
{

	//Wait until TXE is set (Transmit is empty)
	if(PollingEn == enable)
		while(!((USARTx->SR >> 7) & 1));

	//	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	//	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	//	because it is replaced by the parity.
	//	When receiving with the parity enabled, the value read in the MSB bit is the received parity
	//	bit

	//check the length of data 8B or 9B
	if(Gl_UART_CFG->UART_Payload_length == UART_Payload_length_9B)
	{
		USARTx->DR = (*pTxBuffer & (uint16_t)0x01FF);
	}
	else if(Gl_UART_CFG->UART_Payload_length == UART_Payload_length_8B)
	{
		USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
	}

}


/**================================================================
 * @Fn			-MCAL_UART_WAIT_TC
 * @brief 		-polling until transmit complete
 * @param [in] 	-USARTx: it is an instance from USART (x --> 1..3)
 * @retval 		-none
 * Note			-we implement Asynchronous mode
================================================================**/
void MCAL_UART_WAIT_TC(USART_TypeDef *USARTx)
{
	//wait unit TC is set (Transmit complete)
	while(!((USARTx->SR >> 6) & 1));
}


/**================================================================
 * @Fn			-MCAL_UART_ReceiveData
 * @brief 		-Receive data by using UART
 * @param [in] 	-USARTx: it is an instance from USART (x --> 1..3)
 * @param [in] 	-pRxBuffer: data buffer
 * @param [in] 	-PollingEn: enable polling or disable it
 * @retval 		-none
 * Note			-we implement Asynchronous mode
================================================================**/
void MCAL_UART_ReceiveData(USART_TypeDef *USARTx, uint16_t *pRxBuffer, enum Polling_Mechnism PollingEn)
{
	//Wait until RXNE is set (Receive is not empty)
	if(PollingEn == enable)
		while(!((USARTx->SR >> 5) & 1));

	//check the length of data 8B or 9B
	if(Gl_UART_CFG->UART_Payload_length == UART_Payload_length_9B)
	{
		if(Gl_UART_CFG->UART_Parity == UART_Parity_NONE)
		{
			//No parity --> Data is 9B & Parity is 0B
			*((uint16_t *)pRxBuffer) = USARTx->DR;
		}
		else
		{
			//parity enabled --> Data is 8B & Parity is 1B
			*((uint16_t *)pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);
		}
	}
	else if(Gl_UART_CFG->UART_Payload_length == UART_Payload_length_8B)
	{
		if(Gl_UART_CFG->UART_Parity == UART_Parity_NONE)
		{
			//No parity --> Data is 8B & Parity is 0B
			*((uint16_t *)pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);
		}
		else
		{
			//parity enabled --> Data is 7B & Parity is 1B
			*((uint16_t *)pRxBuffer) = (USARTx->DR & (uint8_t)0x7F);
		}
	}
}


/**================================================================
 * @Fn			-MCAL_UART_GPIO_Set_Pins
 * @brief 		-initialize GPIO pins
 * @param [in] 	-USARTx: it is an instance from USART (x --> 1..3)
 * @retval 		-none
 * Note			-we should enable the corresponding ALT & GPIO in RCC clock also called after MCAL_UART_Init()
================================================================**/
void MCAL_UART_GPIO_Set_Pins(USART_TypeDef *USARTx)
{
	GPIO_PIN_Configuration_t PinCFG;

	/*
	 * Tx  -->  Alternate function push-pull
	 * Rx  -->  Input floating
	 * CTS -->  Input floating
	 * RTS -->  Alternate function push-pull
	 */

	if(USARTx == USART1)
	{
		/*
		 * Tx  --> PA9
		 * Rx  --> PA10
		 * CTS --> PA11
		 * RTS --> PA12
		 */

		//configuration of Tx at PA9
		PinCFG.GPIO_PinNumber = GPIO_PIN_9;
		PinCFG.GPIO_PinMODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCFG.GPIO_PinSPEED = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOA, &PinCFG);

		//configuration of Rx at PA10
		PinCFG.GPIO_PinNumber = GPIO_PIN_10;
		PinCFG.GPIO_PinMODE = GPIO_MODE_INPUT_AF;
		MCAL_GPIO_Init(GPIOA, &PinCFG);

		//configuration of CTS or RTS or both
		if(Gl_AUARTx_CFG[0]->UART_HW_FLOW_CTL == UART_HW_FLOW_CTL_CTS || Gl_AUARTx_CFG[0]->UART_HW_FLOW_CTL == UART_HW_FLOW_CTL_CTS_RTS)
		{
			//configuration of CTS at PA11
			PinCFG.GPIO_PinNumber = GPIO_PIN_11;
			PinCFG.GPIO_PinMODE = GPIO_MODE_INPUT_AF;
			MCAL_GPIO_Init(GPIOA, &PinCFG);
		}

		if(Gl_AUARTx_CFG[0]->UART_HW_FLOW_CTL == UART_HW_FLOW_CTL_RTS || Gl_AUARTx_CFG[0]->UART_HW_FLOW_CTL == UART_HW_FLOW_CTL_CTS_RTS)
		{
			//configuration of RTS at PA12
			PinCFG.GPIO_PinNumber = GPIO_PIN_12;
			PinCFG.GPIO_PinMODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.GPIO_PinSPEED = GPIO_SPEED_10MHz;
			MCAL_GPIO_Init(GPIOA, &PinCFG);
		}
	}
	else if(USARTx == USART2)
	{
		/*
		 * Tx  --> PA2
		 * Rx  --> PA3
		 * CTS --> PA0
		 * RTS --> PA1
		 */

		//configuration of Tx at PA2
		PinCFG.GPIO_PinNumber = GPIO_PIN_2;
		PinCFG.GPIO_PinMODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCFG.GPIO_PinSPEED = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOA, &PinCFG);

		//configuration of Rx at PA3
		PinCFG.GPIO_PinNumber = GPIO_PIN_3;
		PinCFG.GPIO_PinMODE = GPIO_MODE_INPUT_AF;
		MCAL_GPIO_Init(GPIOA, &PinCFG);

		//configuration of CTS or RTS or both
		if(Gl_AUARTx_CFG[1]->UART_HW_FLOW_CTL == UART_HW_FLOW_CTL_CTS || Gl_AUARTx_CFG[1]->UART_HW_FLOW_CTL == UART_HW_FLOW_CTL_CTS_RTS)
		{
			//configuration of CTS at PA0
			PinCFG.GPIO_PinNumber = GPIO_PIN_0;
			PinCFG.GPIO_PinMODE = GPIO_MODE_INPUT_AF;
			MCAL_GPIO_Init(GPIOA, &PinCFG);
		}

		if(Gl_AUARTx_CFG[1]->UART_HW_FLOW_CTL == UART_HW_FLOW_CTL_RTS || Gl_AUARTx_CFG[1]->UART_HW_FLOW_CTL == UART_HW_FLOW_CTL_CTS_RTS)
		{
			//configuration of RTS at PA1
			PinCFG.GPIO_PinNumber = GPIO_PIN_1;
			PinCFG.GPIO_PinMODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.GPIO_PinSPEED = GPIO_SPEED_10MHz;
			MCAL_GPIO_Init(GPIOA, &PinCFG);
		}
	}
	else if(USARTx == USART3)
	{
		/*
		 * Tx  --> PB10
		 * Rx  --> PB11
		 * CTS --> PB13
		 * RTS --> PB14
		 */

		//configuration of Tx at PB10
		PinCFG.GPIO_PinNumber = GPIO_PIN_10;
		PinCFG.GPIO_PinMODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCFG.GPIO_PinSPEED = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOB, &PinCFG);

		//configuration of Rx at PB11
		PinCFG.GPIO_PinNumber = GPIO_PIN_11;
		PinCFG.GPIO_PinMODE = GPIO_MODE_INPUT_AF;
		MCAL_GPIO_Init(GPIOB, &PinCFG);

		//configuration of CTS or RTS or both
		if(Gl_AUARTx_CFG[2]->UART_HW_FLOW_CTL == UART_HW_FLOW_CTL_CTS || Gl_AUARTx_CFG[2]->UART_HW_FLOW_CTL == UART_HW_FLOW_CTL_CTS_RTS)
		{
			//configuration of CTS at PB13
			PinCFG.GPIO_PinNumber = GPIO_PIN_13;
			PinCFG.GPIO_PinMODE = GPIO_MODE_INPUT_AF;
			MCAL_GPIO_Init(GPIOB, &PinCFG);
		}

		if(Gl_AUARTx_CFG[2]->UART_HW_FLOW_CTL == UART_HW_FLOW_CTL_RTS || Gl_AUARTx_CFG[2]->UART_HW_FLOW_CTL == UART_HW_FLOW_CTL_CTS_RTS)
		{
			//configuration of RTS at PB14
			PinCFG.GPIO_PinNumber = GPIO_PIN_14;
			PinCFG.GPIO_PinMODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.GPIO_PinSPEED = GPIO_SPEED_10MHz;
			MCAL_GPIO_Init(GPIOB, &PinCFG);
		}
	}
}


//ISR for USARTx
void USART1_IRQHandler(void)
{
	Gl_AUARTx_CFG[0]->UART_PF_IRQ_CallBack();
}

void USART2_IRQHandler(void)
{
	Gl_AUARTx_CFG[1]->UART_PF_IRQ_CallBack();
}

void USART3_IRQHandler(void)
{
	Gl_AUARTx_CFG[2]->UART_PF_IRQ_CallBack();
}
