/*
 * STM32F103C6_SPI_DRICER.c
 *
 *  Created on: Oct 10, 2023
 *      Author: ABRAM
 */


#include "STM32F103C6_SPI_DRIVER.h"

/*
 * ======================================================================
 * 					Generic Variables
 * ======================================================================
 */
SPI_Configuration_t *Gl_SPI_CFG = NULL;
SPI_Configuration_t *Gl_ASPI_CFG[2] = {NULL, NULL};


/*
 * ======================================================================
 * 					Generic Macros
 * ======================================================================
 */
#define SPI1_INDEX						0
#define SPI2_INDEX						1

#define SPI_SR_TXE						1
#define SPI_SR_RXNE						0

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
 * @Fn			-MCAL_SPI_Init
 * @brief 		-initialize SPI
 * @param [in] 	-SPIx: it is an instance from SPI (x --> 1..2)
 * @param [in] 	-SPI_Config: it is a structure containing configuration of SPI.
 * @retval 		-none
 * Note			-Support for SPI full Duplex Master/Slave only & NSS hardware/software
 * 				-in case of master you have to configure pin and drive it.
================================================================**/
void MCAL_SPI_Init(SPI_TypeDef *SPIx, SPI_Configuration_t *SPI_Config)
{
	//Safety for registers
	uint16_t Tmpreg_CR1 = 0;
	uint16_t Tmpreg_CR2 = 0;

	Gl_SPI_CFG = SPI_Config;

	//enable clock for SPI
	if(SPIx == SPI1)
	{
		Gl_ASPI_CFG[SPI1_INDEX] = SPI_Config;
		RCC_SPI1_CLK_EN();
	}
	else if(SPIx == SPI2)
	{
		Gl_ASPI_CFG[SPI2_INDEX] = SPI_Config;
		RCC_SPI2_CLK_EN();
	}

	// Select the BR[2:0] bits to define the serial clock baud rate  --> CR1
	Tmpreg_CR1 |= SPI_Config->SPI_BuadRate_PreScalar;

	// Set the DFF bit to define 8- or 16-bit data frame format  --> CR1
	Tmpreg_CR1 |= SPI_Config->SPI_Data_Size;

	//Select the CPOL and CPHA bits  --> CR1
	Tmpreg_CR1 |= SPI_Config->SPI_Clock_Polarity;
	Tmpreg_CR1 |= SPI_Config->SPI_Clock_Phase;

	//The frame format (MSB-first or LSB-first)  --> CR1
	Tmpreg_CR1 |= SPI_Config->SPI_Frame_Format;

	//configure Device Mode --> Master or Slave
	Tmpreg_CR1 |= SPI_Config->SPI_Device_Mode;

	//configure Communication Mode --> FD or HD or Simplex
	Tmpreg_CR1 |= SPI_Config->SPI_Communication_Mode;

	//Enable SPI --> Bit 6 SPE: SPI enable --> CR1
	Tmpreg_CR1 |= (1 << 6);

	//================================NSS=================================
	if(SPI_Config->SPI_NSS == SPI_NSS_Hardware_Master_SS_Output_Enable)
	{
		Tmpreg_CR2 |= SPI_Config->SPI_NSS;
	}
	else if(SPI_Config->SPI_NSS == SPI_NSS_Hardware_Master_SS_Output_Disable)
	{
		Tmpreg_CR2 &= SPI_Config->SPI_NSS;
	}
	else
	{
		Tmpreg_CR1 |= SPI_Config->SPI_NSS;
	}

	//Configuration of SPI interrupt if it is enabled
	if(SPI_Config->SPI_IRQ_Enable != SPI_IRQ_Enable_NONE)
	{
		Tmpreg_CR2 |= SPI_Config->SPI_IRQ_Enable;

		//Enable NVIC for SPIx IRQ
		if(SPIx == SPI1)
		{
			NVIC_SPI1_IRQ35_ENABLE;
		}
		else if(SPIx == SPI2)
		{
			NVIC_SPI2_IRQ36_ENABLE;
		}
	}

	SPIx->CR1 = Tmpreg_CR1;
	SPIx->CR2 = Tmpreg_CR2;

}


/**================================================================
 * @Fn			-MCAL_SPI_DeInit
 * @brief 		-Deinitialize SPI
 * @param [in] 	-SPIx: it is an instance from SPI (x --> 1..2)
 * @retval 		-none
 * Note			-none
================================================================**/
void MCAL_SPI_DeInit(SPI_TypeDef *SPIx)
{
	//reset clock and disable interrupts
	if(SPIx == SPI1)
	{
		NVIC_SPI1_IRQ35_DISABLE;
		RCC_SPI1_Reset();
	}
	else if(SPIx == SPI2)
	{
		NVIC_SPI2_IRQ36_DISABLE;
		RCC_SPI2_Reset();
	}
}

/**================================================================
 * @Fn			-MCAL_SPI_SendData
 * @brief 		-Send data by using SPI
 * @param [in] 	-SPIx: it is an instance from SPI (x --> 1..2)
 * @param [in] 	-pTx_Buffer: data buffer
 * @param [in] 	-polling_state: enable polling or disable it
 * @retval 		-none
 * Note			-none
================================================================**/
void MCAL_SPI_SendData(SPI_TypeDef *SPIx, uint16_t *pTx_Buffer, enum SPI_Polling_Mechnism polling_state)
{
	//Wait until TXE is set (Transmit is empty)
	if(polling_state == Polling_Enable)
		while(!((SPIx->SR >> SPI_SR_TXE)&1));

	/*
	 * Depending on the data frame format selection bit (DFF in SPI_CR1 register), the data
	 * sent or received is either 8-bit or 16-bit. This selection has to be made before enabling
	 * the SPI to ensure correct operation.
	 * -------------------------------------------------------
	 * For an 8-bit data frame, the buffers are 8-bit and only the LSB of the register
	 * (SPI_DR[7:0]) is used for transmission/reception. When in reception mode, the MSB of
	 * the register (SPI_DR[15:8]) is forced to 0.
	 * For a 16-bit data frame, the buffers are 16-bit and the entire register, SPI_DR[15:0] is
	 * used for transmission/reception
	 */
	if(Gl_SPI_CFG->SPI_Data_Size == SPI_Data_Size_8B)
	{
		SPIx->DR = ((*pTx_Buffer) & ((uint8_t)0xFF));
	}
	else if(Gl_SPI_CFG->SPI_Data_Size == SPI_Data_Size_16B)
	{
		SPIx->DR = *pTx_Buffer;
	}
}

/**================================================================
 * @Fn			-MCAL_SPI_ReceiveData
 * @brief 		-Receive data by using SPI
 * @param [in] 	-SPIx: it is an instance from SPI (x --> 1..2)
 * @param [in] 	-pRxBuffer: data buffer
 * @param [in] 	-polling_state: enable polling or disable it
 * @retval 		-none
 * Note			-none
================================================================**/
void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx, uint16_t *pRx_Buffer, enum SPI_Polling_Mechnism polling_state)
{
	//Wait until RXNE is set (Receive is not empty)
	if(polling_state == Polling_Enable)
		while(!((SPIx->SR >> SPI_SR_RXNE) & 1));

	if(Gl_SPI_CFG->SPI_Data_Size == SPI_Data_Size_8B)
	{
		*pRx_Buffer = ((uint16_t)((SPIx->DR) & ((uint8_t)0xFF)));
	}
	else if(Gl_SPI_CFG->SPI_Data_Size == SPI_Data_Size_16B)
	{
		*pRx_Buffer = ((uint16_t)SPIx->DR);
	}
}


/**================================================================
 * @Fn			-MCAL_SPI_Tx_Rx
 * @brief 		-Send & Receive data by using SPI in the same function
 * @param [in] 	-SPIx: it is an instance from SPI (x --> 1..2)
 * @param [in] 	-pTx_Buffer: data buffer
 * @param [in] 	-polling_state: enable polling or disable it
 * @retval 		-none
 * Note			-we send & receive by one function
================================================================**/
void MCAL_SPI_Tx_Rx(SPI_TypeDef *SPIx, uint16_t *pTx_Buffer, enum SPI_Polling_Mechnism polling_state)
{
	//Wait until TXE is set (Transmit is empty)
	if(polling_state == Polling_Enable)
		while(!((SPIx->SR >> SPI_SR_TXE)&1));

	SPIx->DR = *pTx_Buffer;

	//Wait until RXNE is set (Receive is not empty)
	if(polling_state == Polling_Enable)
		while(!((SPIx->SR >> SPI_SR_RXNE) & 1));

	*pTx_Buffer = SPIx->DR;
}


/**================================================================
 * @Fn			-MCAL_GPIO_SPI_Set_Pins
 * @brief 		-initialize GPIO pins
 * @param [in] 	-SPIx: it is an instance from SPIx (x --> 1..2)
 * @retval 		-none
 * Note			-we should enable the corresponding ALT & GPIO in RCC clock also called after MCAL_UART_Init()
================================================================**/
void MCAL_GPIO_SPI_Set_Pins(SPI_TypeDef *SPIx)
{
	GPIO_PIN_Configuration_t PinCFG;

	/*
	 * SCLK:
	 * 		Master	-->  Alternate function push-pull
	 * 		Slave	-->  Input floating
	 * MOSI:
	 * 		Full duplex / master						--> Alternate function push-pull
	 * 		Full duplex / slave							--> Input floating / Input pull-up
	 * MISO:
	 * 		Full duplex / master 						--> Input floating / Input pull-up
	 * 		Full duplex / slave (point to point) 		--> Alternate function push-pull
	 * 		Full duplex / slave (multi-slave)			--> Alternate function open drain
	 * NSS:
	 * 		Hardware master /slave 						--> Input floating/ Input pull-up / Input pull-down
	 * 		Hardware master/ NSS output enabled			--> Alternate function push-pull
	 * 		Software Not used. 							--> Can be used as a GPIO
	 */

	if(SPIx == SPI1)
	{
		/*
		 * SCLK --> PA5
		 * MOSI --> PA7
		 * MISO --> PA6
		 * NSS  --> PA4
		 */
		if(Gl_SPI_CFG[SPI1_INDEX].SPI_Device_Mode == SPI_Device_Mode_Master)
		{
			//SCLK
			PinCFG.GPIO_PinNumber = GPIO_PIN_5;
			PinCFG.GPIO_PinMODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.GPIO_PinSPEED = GPIO_SPEED_10MHz;
			MCAL_GPIO_Init(GPIOA, &PinCFG);

			//MOSI
			PinCFG.GPIO_PinNumber = GPIO_PIN_7;
			PinCFG.GPIO_PinMODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.GPIO_PinSPEED = GPIO_SPEED_10MHz;
			MCAL_GPIO_Init(GPIOA, &PinCFG);

			//MISO
			PinCFG.GPIO_PinNumber = GPIO_PIN_6;
			PinCFG.GPIO_PinMODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCFG);

			//NSS
			if(Gl_SPI_CFG[SPI1_INDEX].SPI_NSS == SPI_NSS_Hardware_Master_SS_Output_Disable)
			{
				PinCFG.GPIO_PinNumber = GPIO_PIN_4;
				PinCFG.GPIO_PinMODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCFG);
			}
			else if(Gl_SPI_CFG[SPI1_INDEX].SPI_NSS == SPI_NSS_Hardware_Master_SS_Output_Enable)
			{
				PinCFG.GPIO_PinNumber = GPIO_PIN_4;
				PinCFG.GPIO_PinMODE = GPIO_MODE_OUTPUT_AF_PP;
				PinCFG.GPIO_PinSPEED = GPIO_SPEED_10MHz;
				MCAL_GPIO_Init(GPIOA, &PinCFG);
			}
		}
		else if(Gl_SPI_CFG[SPI1_INDEX].SPI_Device_Mode == SPI_Device_Mode_Slave)
		{
			//SCLK
			PinCFG.GPIO_PinNumber = GPIO_PIN_5;
			PinCFG.GPIO_PinMODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCFG);

			//MOSI
			PinCFG.GPIO_PinNumber = GPIO_PIN_7;
			PinCFG.GPIO_PinMODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCFG);

			//MISO
			PinCFG.GPIO_PinNumber = GPIO_PIN_6;
			PinCFG.GPIO_PinMODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.GPIO_PinSPEED = GPIO_SPEED_10MHz;
			MCAL_GPIO_Init(GPIOA, &PinCFG);

			//NSS
			if(Gl_SPI_CFG[SPI1_INDEX].SPI_NSS == SPI_NSS_Hardware_Slave)
			{
				PinCFG.GPIO_PinNumber = GPIO_PIN_4;
				PinCFG.GPIO_PinMODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCFG);
			}
		}
	}
	else if(SPIx == SPI2)
	{
		/*
		 * SCLK --> PB13
		 * MOSI --> PB15
		 * MISO --> PB14
		 * NSS  --> PB12
		 */

		if(Gl_SPI_CFG[SPI2_INDEX].SPI_Device_Mode == SPI_Device_Mode_Master)
		{
			//SCLK
			PinCFG.GPIO_PinNumber = GPIO_PIN_13;
			PinCFG.GPIO_PinMODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.GPIO_PinSPEED = GPIO_SPEED_10MHz;
			MCAL_GPIO_Init(GPIOB, &PinCFG);

			//MOSI
			PinCFG.GPIO_PinNumber = GPIO_PIN_15;
			PinCFG.GPIO_PinMODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.GPIO_PinSPEED = GPIO_SPEED_10MHz;
			MCAL_GPIO_Init(GPIOB, &PinCFG);

			//MISO
			PinCFG.GPIO_PinNumber = GPIO_PIN_14;
			PinCFG.GPIO_PinMODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCFG);

			//NSS
			if(Gl_SPI_CFG[SPI2_INDEX].SPI_NSS == SPI_NSS_Hardware_Master_SS_Output_Disable)
			{
				PinCFG.GPIO_PinNumber = GPIO_PIN_12;
				PinCFG.GPIO_PinMODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCFG);
			}
			else if(Gl_SPI_CFG[SPI2_INDEX].SPI_NSS == SPI_NSS_Hardware_Master_SS_Output_Enable)
			{
				PinCFG.GPIO_PinNumber = GPIO_PIN_12;
				PinCFG.GPIO_PinMODE = GPIO_MODE_OUTPUT_AF_PP;
				PinCFG.GPIO_PinSPEED = GPIO_SPEED_10MHz;
				MCAL_GPIO_Init(GPIOB, &PinCFG);
			}
		}
		else if(Gl_SPI_CFG[SPI2_INDEX].SPI_Device_Mode == SPI_Device_Mode_Slave)
		{
			//SCLK
			PinCFG.GPIO_PinNumber = GPIO_PIN_13;
			PinCFG.GPIO_PinMODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCFG);

			//MOSI
			PinCFG.GPIO_PinNumber = GPIO_PIN_15;
			PinCFG.GPIO_PinMODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCFG);

			//MISO
			PinCFG.GPIO_PinNumber = GPIO_PIN_14;
			PinCFG.GPIO_PinMODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.GPIO_PinSPEED = GPIO_SPEED_10MHz;
			MCAL_GPIO_Init(GPIOB, &PinCFG);

			//NSS
			if(Gl_SPI_CFG[SPI2_INDEX].SPI_NSS == SPI_NSS_Hardware_Slave)
			{
				PinCFG.GPIO_PinNumber = GPIO_PIN_12;
				PinCFG.GPIO_PinMODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCFG);
			}
		}
	}
}

/*
 * ======================================================================
 * 								ISR
 * ======================================================================
 */
void SPI1_IRQHandler(void)
{
	struct S_IRQ_Source irq_src;

	irq_src.TXE = ((SPI1->SR >> SPI_SR_TXE) & 1);
	irq_src.RXNE = ((SPI1->SR >> SPI_SR_RXNE) & 1);
	irq_src.ERRI = ((SPI1->SR >> 4) & 1);

	Gl_ASPI_CFG[SPI1_INDEX]->PF_IRQ_CallBack(irq_src);
}

void SPI2_IRQHandler(void)
{
	struct S_IRQ_Source irq_src;

	irq_src.TXE = ((SPI2->SR >> SPI_SR_TXE) & 1);
	irq_src.RXNE = ((SPI2->SR >> SPI_SR_RXNE) & 1);
	irq_src.ERRI = ((SPI2->SR >> 4) & 1);

	Gl_ASPI_CFG[SPI2_INDEX]->PF_IRQ_CallBack(irq_src);
}
