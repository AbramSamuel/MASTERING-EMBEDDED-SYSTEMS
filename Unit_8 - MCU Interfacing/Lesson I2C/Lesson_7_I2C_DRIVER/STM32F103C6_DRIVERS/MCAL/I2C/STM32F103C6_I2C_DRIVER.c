/*
 * STM32F103C6_I2C_DRIVER.c
 *
 *  Created on: Feb 18, 2024
 *      Author: ABRAM
 */


#include "STM32F103C6_I2C_DRIVER.h"

/*
 * ======================================================================
 * 					Generic Variables
 * ======================================================================
 */
I2C_Configuration_t Gl_AI2C_CFG[2];


/*
 * ======================================================================
 * 					Generic Macros
 * ======================================================================
 */
#define I2C1_INDEX							0
#define I2C2_INDEX							1


/*
 * ======================================================================
 * 					Generic Functions
 * ======================================================================
 */
/**================================================================
 * @Fn			-I2C_Generate_Start_Condition
 * @brief 		-it is used to generate start condition
 * @param [in] 	-I2Cx: it is an instance from I2C (x --> 1..2)
 * @param [in] 	-Functional_State: it is used to determine if we need to enable or disable this function
 * @param [in] 	-start: it is determine that we send start or repeated start
 * @retval 		-none
 * Note			-none
================================================================**/
void I2C_Generate_Start_Condition(I2C_TypeDef *I2Cx, Functional_State state, Start_State start)
{
	//check if we use start or repeated start because if we use normal start we should check that if the bus is bus
	//but when we use repeated start we don't check because the bus is busy because we use it.
	if(start != Repeated_Start)
	{
		//check if the bus is busy or not (Bus is idle)
		while(I2C_Get_Flag_Status(I2Cx, I2C_FlAG_BUS_BUSY));
	}

	//Bit 8 START: Start generation
	//This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
	//In Master Mode:
	//0: No Start generation
	//1: Repeated start generation
	//In Slave mode:
	//0: No Start generation
	//1: Start generation when the bus is free
	if(state == Fun_enable)
	{
		/* Generate the start condition */
		I2Cx->CR1 |= I2C_CR1_START;
	}
	else if(state == Fun_disable)
	{
		/* Don't Generate the start condition */
		I2Cx->CR1 &= ~(I2C_CR1_START);
	}
}

/**================================================================
 * @Fn			-I2C_Get_Flag_Status
 * @brief 		-it is used to see the status of the flag
 * @param [in] 	-I2Cx: it is an instance from I2C (x --> 1..2)
 * @param [in] 	-flag: it is the flag that we need to check its status
 * @retval 		-we return the status of the flag --> set or reset
 * Note			-none
================================================================**/
Flag_Status I2C_Get_Flag_Status(I2C_TypeDef *I2Cx, Status flag)
{
	volatile uint32_t dummy_Read = 0;
	uint32_t flag1 = 0, flag2 = 0, Last_Event = 0;
	Flag_Status flag_state = reset;

	switch(flag)
	{
	//*******************************************************************************
	//Bit 1 BUSY: Bus busy
	//0: No communication on the bus
	//1: Communication ongoing on the bus
	//– Set by hardware on detection of SDA or SCL low
	//– cleared by hardware on detection of a Stop condition.
	//It indicates a communication in progress on the bus. This information is still updated when
	//the interface is disabled (PE=0).
	case I2C_FlAG_BUS_BUSY:
		if((I2Cx->SR2) & (I2C_SR2_BUSY))
			flag_state = set;
		else
			flag_state = reset;
		break;
	//*******************************************************************************

	//*******************************************************************************
		//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
		//Bit 0 SB: Start bit (Master mode)
		//0: No Start condition
		//1: Start condition generated.
		//– Set when a Start condition generated.
		//– Cleared by software by reading the SR1 register followed by writing the DR register, or by
		//hardware when PE=0
	case EV5:
		if((I2Cx->SR1) & (I2C_SR1_SB))
			flag_state = set;
		else
			flag_state = reset;
		break;
	//*******************************************************************************

	//*******************************************************************************
		//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
		//Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
		//This bit is cleared by software reading SR1 register followed reading SR2, or by hardware
		//when PE=0.
		//Address matched (Slave)
		//0: Address mismatched or not received.
		//1: Received address matched.
		//– Set by hardware as soon as the received slave address matched with the OAR registers
		//content or a general call or a SMBus Device Default Address or SMBus Host or SMBus Alert
		//is recognized. (when enabled depending on configuration).
		//Note: In slave mode, it is recommended to perform the complete clearing sequence (READ
		//SR1 then READ SR2) after ADDR is set. Refer to Figure 272.
		//Address sent (Master)
		//0: No end of address transmission
		//1: End of address transmission
		//– For 10-bit addressing, the bit is set after the ACK of the 2nd byte.
		//– For 7-bit addressing, the bit is set after the ACK of the byte.
		//Note: ADDR is not set after a NACK reception
	case EV6:
		if((I2Cx->SR1) & (I2C_SR1_ADDR))
			flag_state = set;
		else
			flag_state = reset;
		break;
	//*******************************************************************************

	//*******************************************************************************
	case MASTER_BYTE_TRANSMITTING:
		/* Read I2Cx status registers */
		flag1 = I2Cx->SR1;
		flag2 = I2Cx->SR2;
		flag2 = flag2 << 16;

		/* Merge flag1 & flag2 in the same variable to get the last event */
		Last_Event = ((flag1 | flag2) & ((uint32_t)0x00FFFFFF));

		if((Last_Event & flag) == flag)
		{
			// last event is equal to I2C Event
			flag_state = set;
		}
		else
		{
			// last event is different from I2C Event
			flag_state = reset;
		}
		break;
	//*******************************************************************************

	//*******************************************************************************
		//EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
		//EV8: TxE=1, shift register not empty, d. ata register empty, cleared by writing DR register
		//Bit 7 TxE: Data register empty (transmitters)
		//0: Data register not empty
		//1: Data register empty
		//– Set when DR is empty in transmission. TxE is not set during address phase.
		//– Cleared by software writing to the DR register or by hardware after a start or a stop condition
		//or when PE=0.
		//TxE is not set if either a NACK is received, or if next byte to be transmitted is PEC (PEC=1)
		//Note: TxE is not cleared by writing the first data being transmitted, or by writing data when
		//BTF is set, as in both cases the data register is still empty.
	case EV8:
	case EV8_1:
		if((I2Cx->SR1) & (I2C_SR1_TXE))
			flag_state = set;
		else
			flag_state = reset;
		break;
	//*******************************************************************************

	//*******************************************************************************
		//EV7: RxNE = 1 cleared by reading DR register
		//Bit 6 RxNE: Data register not empty (receivers)
		//0: Data register empty
		//1: Data register not empty
		//– Set when data register is not empty in receiver mode. RxNE is not set during address phase.
		//– Cleared by software reading or writing the DR register or by hardware when PE=0.
		//RxNE is not set in case of ARLO event.
		//Note: RxNE is not cleared by reading data when BTF is set, as the data register is still full
	case EV7:
		if((I2Cx->SR1) & I2C_SR1_RXNE)
			flag_state = set;
		else
			flag_state = reset;
		break;
	//*******************************************************************************
	}


	return flag_state;
}

/**================================================================
 * @Fn			-I2C_Send_Address
 * @brief 		-it is used to send address with Read/Write bit
 * @param [in] 	-I2Cx: it is an instance from I2C (x --> 1..2)
 * @param [in] 	-Address: it is the address that we need to send it
 * @param [in] 	-RW: it is determine that we need to write or read
 * @retval 		-none
 * Note			-none
================================================================**/
void I2C_Send_Address(I2C_TypeDef *I2Cx, uint16_t Address, I2C_Direction RW)
{
	uint8_t Index = (I2Cx == I2C1)? I2C1_INDEX : I2C2_INDEX;

	/* check if we are in 7-bit or 10-bit address mode */
	if(Gl_AI2C_CFG[Index].I2C_Slave_Device_Address.I2C_Slave_Address_Length == I2C_Slave_Address_Length_7Bit)
	{
		/* Send the Address */
		Address = (Address << 1);

		if(RW == I2C_Direction_Transimitter)
		{
			/* Clear RW bit when we write */
			Address &= ~(1 << 0);
		}
		else if(RW == I2C_Direction_Receiver)
		{
			/* Set RW bit when we read */
			Address |= (1 << 0);
		}

		I2Cx->DR = Address;
	}
	else if(Gl_AI2C_CFG[Index].I2C_Slave_Device_Address.I2C_Slave_Address_Length == I2C_Slave_Address_Length_10Bit)
	{
		//10-Bit slave address is not supported
	}
}

/**================================================================
 * @Fn			-I2C_Generate_Stop_Condition
 * @brief 		-it is used to generate stop condition
 * @param [in] 	-I2Cx: it is an instance from I2C (x --> 1..2)
 * @param [in] 	-Functional_State: it is used to determine if we need to enable or disable this function
 * @retval 		-none
 * Note			-none
================================================================**/
void I2C_Generate_Stop_Condition(I2C_TypeDef *I2Cx, Functional_State state)
{
	//Bit 9 STOP: Stop generation
	//The bit is set and cleared by software, cleared by hardware when a Stop condition is
	//detected, set by hardware when a timeout error is detected.
	//In Master Mode:
	//0: No Stop generation.
	//1: Stop generation after the current byte transfer or after the current Start condition is sent.
	//In Slave mode:
	//0: No Stop generation.
	//1: Release the SCL and SDA lines after the current byte transfer
	if(state == Fun_enable)
	{
		I2Cx->CR1 |= (I2C_CR1_STOP);
	}
	else if(state == Fun_disable)
	{
		I2Cx->CR1 &= ~(I2C_CR1_STOP);
	}
}

/**================================================================
 * @Fn			-I2C_Acknowledge_Config
 * @brief 		-it is used to configure the acknowledge
 * @param [in] 	-I2Cx: it is an instance from I2C (x --> 1..2)
 * @param [in] 	-Functional_State: it is used to determine if we need to enable or disable this function
 * @retval 		-none
 * Note			-none
================================================================**/
void I2C_Acknowledge_Config(I2C_TypeDef *I2Cx, Functional_State state)
{
	//Bit 10 ACK: Acknowledge enable
	//This bit is set and cleared by software and cleared by hardware when PE=0.
	//0: No acknowledge returned
	//1: Acknowledge returned after a byte is received (matched address or data)
	if(state == Fun_enable)
	{
		I2Cx->CR1 |= (I2C_CR1_ACK);
	}
	else if(state == Fun_disable)
	{
		I2Cx->CR1 &= ~(I2C_CR1_ACK);
	}
}

/**================================================================
 * @Fn			-Slave_States
 * @brief 		-it is used to see which ISR should call depend on State
 * @param [in] 	-I2Cx: it is an instance from I2C (x --> 1..2)
 * @param [in] 	-State: it is the a flag that determine which ISR should we call it
 * @retval 		-none
 * Note			-none
================================================================**/
void Slave_States(I2C_TypeDef *I2Cx,Slave_State_t State)
{
	uint8_t index = (I2Cx == I2C1) ? I2C1_INDEX : I2C2_INDEX ;

	switch(State)
	{
	//*******************************************************************************
	case I2C_ERROR_AF:
		//make sure that the slave is really in transmitter mode
		if(I2Cx->SR2 & (I2C_SR2_TRA))
		{
			//Slave shouldn't send anything else
		}
		break;
	//*******************************************************************************

	//*******************************************************************************
	case I2C_EV_STOP:
		//make sure that the slave is really in transmitter mode
		if(I2Cx->SR2 & (I2C_SR2_TRA))
		{
			//Notify APP that the Stop Condition is Sent by the master
			Gl_AI2C_CFG[index].PF_Slave_Event_CallBack(I2C_EV_STOP);
		}
		break;
	//*******************************************************************************

	//*******************************************************************************
	case I2C_EV_ADDR_Matched:
		//Notify APP that The address is matched with The slave address
		Gl_AI2C_CFG[index].PF_Slave_Event_CallBack(I2C_EV_ADDR_Matched);
		break;
	//*******************************************************************************

	//*******************************************************************************
	case I2C_EV_DATA_REQ:
		//make sure that the slave is really in transmitter mode
		if(I2Cx->SR2 & (I2C_SR2_TRA))
		{
			//The APP Layer should send the data (MCAL_I2C_Slave_Tx)in this state
			Gl_AI2C_CFG[index].PF_Slave_Event_CallBack(I2C_EV_DATA_REQ);
		}
		break;
	//*******************************************************************************

	//*******************************************************************************
	case I2C_EV_DATA_RCV:
		//make sure that the slave is really in receiver mode
		if(!(I2Cx->SR2 & (I2C_SR2_TRA)) )
		{
			//The APP Layer should read the data (MCAL_I2C_Slave_Rx)in this state
			Gl_AI2C_CFG[index].PF_Slave_Event_CallBack(I2C_EV_DATA_RCV);
		}
		break;
	//*******************************************************************************
	}
}

/*
 * ======================================================================
 * 								APIs
 * ======================================================================
 */

/**================================================================
 * @Fn			-MCAL_I2C_Init
 * @brief 		-initialize I2C
 * @param [in] 	-I2Cx: it is an instance from I2C (x --> 1..2)
 * @param [in] 	-I2C_Config: it is a structure containing configuration of I2C.
 * @retval 		-none
 * Note			-none
================================================================**/
void MCAL_I2C_Init(I2C_TypeDef *I2Cx, I2C_Configuration_t *I2C_Config)
{
	uint16_t TempReg = 0;
	uint32_t PClk1 = 8000000;
	uint16_t FreqRange = 0, CCR_Val = 0, RiseTime = 0;

	/*-------------------------------enable clock for peripheral--------------------------*/
	if(I2Cx == I2C1)
	{
		RCC_I2C1_CLK_EN();
		Gl_AI2C_CFG[I2C1_INDEX] = *I2C_Config;
	}
	else if(I2Cx == I2C2)
	{
		RCC_I2C2_CLK_EN();
		Gl_AI2C_CFG[I2C2_INDEX] = *I2C_Config;
	}

	/*-------------------------------see if we are in I2C Mode or SMBus Mode--------------------------*/
	if(I2C_Config->I2C_Mode == I2C_Mode_I2C)
	{
		/* Disable the peripheral till we initialize the clock and the timing of the peripheral */
		I2Cx->CR1 &= ~(I2C_CR1_PE_Msk);

		/*-------------------------------Initialize the Peripheral Clock & Time--------------------------*/

		//*******************************************************************************
		//Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
		//		--> Bits 5:0 FREQ[5:0]: Peripheral clock frequency in I2C_CR2

		/* Get PClk1 by using RCC Driver */
		PClk1 = MCAL_RCC_GetPCLK1Freq();

		/* Frequency Range --> FREQ = PClk1 / 1000000(M) */
		FreqRange = (uint16_t)(PClk1 / 1000000);

		/* Write FREQ on I2C_CR2 */
		I2Cx->CR2 &= ~(I2C_CR2_FREQ_Msk);
		I2Cx->CR2 |= (FreqRange << I2C_CR2_FREQ_Pos);
		//*******************************************************************************

		//*******************************************************************************
		//Configure the clock control registers
		//		--> Bits 11:0 CCR[11:0]: Clock control register in Fm/Sm mode (Master mode) in (I2C_CCR)

		/* Set Master Mode Selection --> Standard or Fast Mode */
		TempReg = I2C_Config->I2C_Master_Mode_Selection;

		if(I2C_Config->I2C_Master_Mode_Selection == I2C_Master_Mode_Selection_SM)
		{
			/* Calculate CCR value from the equation <Standard Mode> */
			//Thigh = CCR * TPClk1
			//Ti2cclock = Thigh + Tlow ------> Thigh = Ti2cclock / 2
			//CCR = Ti2cclock / (2 * TPClk1)
			//CCR = FPClk1 / (2 * Fi2cclock)
			CCR_Val = (uint16_t)(PClk1 / (I2C_Config->I2C_ClockSpeed << 1));

			TempReg |= CCR_Val;
		}
		else if(I2C_Config->I2C_Master_Mode_Selection == I2C_Master_Mode_Selection_FM)
		{
			//Fast Mode is not supported
		}

		/* Write CCR Value on I2C_CCR */
		I2Cx->CCR = TempReg;
		//*******************************************************************************

		//*******************************************************************************
		//Configure the rise time register
		//		--> Bits 5:0 TRISE[5:0]: Maximum rise time in Fm/Sm mode (Master mode) in (I2C_TRISE)
		//		--> the maximum allowed SCL rise time is 1000 ns.
		//		--> If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
		//			therefore the TRISE[5:0] bits must be programmed with 09h.
		//			(1000 ns / 125 ns = 8 + 1)
		RiseTime = FreqRange + 1;
		I2Cx->TRISE |= RiseTime;
		//*******************************************************************************


		/*-------------------------------Initialize the I2C_CR1 Register Configuration --------------------------*/
		I2Cx->CR1 |= (I2C_Config->I2C_Mode | I2C_Config->I2C_General_Call_Control | I2C_Config->I2C_Clock_Stretching | I2C_Config->I2C_ACK_Control);

		/*-------------------------------Initialize the I2C_CR2 Register Configuration --------------------------*/
		//we do the configuration of the clock & we will do configuration of Interrupts if we are a slave
		/* we use Interrupt Mechanism when we are in Slave Mode */
		if(I2C_Config->PF_Slave_Event_CallBack != NULL)
		{
			/* Enable all Interrupts Slave */
			//Bit 8 ITERREN: Error interrupt enable
			I2Cx->CR2 |= (I2C_CR2_ITERREN);
			//Bit 9 ITEVTEN: Event interrupt enable
			I2Cx->CR2 |= (I2C_CR2_ITEVTEN);
			//Bit 10 ITBUFEN: Buffer interrupt enable
			I2Cx->CR2 |= (I2C_CR2_ITBUFEN);

			/* Enable Interrupts from NVIC */
			if(I2Cx == I2C1)
			{
				NVIC_I2C1_EV_IRQ31_ENABLE;
				NVIC_I2C1_ER_IRQ32_ENABLE;
			}
			else if(I2Cx == I2C2)
			{
				NVIC_I2C2_EV_IRQ33_ENABLE;
				NVIC_I2C2_ER_IRQ34_ENABLE;
			}
		}

		/*-------------------------------Initialize the I2C_OAR1 Register Configuration --------------------------*/
		/*-------------------------------Initialize the I2C_OAR2 Register Configuration --------------------------*/
		//Set Primary address of the slave & choose the slave address mode
		TempReg = 0;
		TempReg |= I2C_Config->I2C_Slave_Device_Address.I2C_Slave_Address_Length;
		TempReg |= (I2C_Config->I2C_Slave_Device_Address.I2C_Primary_Slave_Address << I2C_OAR1_ADD_Pos);
		I2Cx->OAR1 = TempReg;

		//check if Dual address is enable
		if(I2C_Config->I2C_Slave_Device_Address.I2C_Slave_Address_DUAL == I2C_Slave_Address_DUAL_Enable)
		{
			//Set Secondary address of the slave & enable the dual slave address mode
			TempReg = I2C_Slave_Address_DUAL_Enable;
			TempReg |= (I2C_Config->I2C_Slave_Device_Address.I2C_Secondary_Slave_Address << I2C_OAR2_ADD2_Pos);
			I2Cx->OAR2 = TempReg;
		}


		/*-------------------------------Initialize the I2C_SR1 Register Configuration --------------------------*/
		/*-------------------------------Initialize the I2C_SR2 Register Configuration --------------------------*/
		I2Cx->SR1 = 0;
		I2Cx->SR2 = 0;


		/*-------------------------------Enable the Peripheral --------------------------*/
		I2Cx->CR1 |= (I2C_CR1_PE_Msk);

	}
	else if(I2C_Config->I2C_Mode == I2C_Mode_SMBus)
	{
		//SMBus is not supported
	}
}

/**================================================================
 * @Fn			-MCAL_I2C_DeInit
 * @brief 		-Deinitialize I2C
 * @param [in] 	-I2Cx: it is an instance from I2C (x --> 1..2)
 * @retval 		-none
 * Note			-none
================================================================**/
void MCAL_I2C_DeInit(I2C_TypeDef *I2Cx)
{
	if(I2Cx == I2C1)
	{
		/* Disable Interrupts & then Reset Clock */
		NVIC_I2C1_EV_IRQ31_DISABLE;
		NVIC_I2C1_ER_IRQ32_DISABLE;

		RCC_I2C1_Reset();
	}
	else if(I2Cx == I2C2)
	{
		/* Disable Interrupts & then Reset Clock */
		NVIC_I2C2_EV_IRQ33_DISABLE;
		NVIC_I2C2_ER_IRQ34_DISABLE;

		RCC_I2C2_Reset();
	}
}


/**================================================================
 * @Fn			-MCAL_GPIO_I2C_Set_Pins
 * @brief 		-initialize GPIO pins
 * @param [in] 	-I2Cx: it is an instance from I2C (x --> 1..2)
 * @retval 		-none
 * Note			-we should enable the corresponding AFIO & GPIO in RCC clock also called after MCAL_I2C_Init()
================================================================**/
void MCAL_GPIO_I2C_Set_Pins(I2C_TypeDef *I2Cx)
{
	GPIO_PIN_Configuration_t PinCFG;

	/*
	 * I2Cx_SCL --> Alternate function open drain
	 * I2Cx_SDA --> Alternate function open drain
	 */

	if(I2Cx == I2C1)
	{
		/*
		 * SCL --> PB6
		 * SDA --> PB7
		 */
		//*******************************************************************************
		//Configure SCL of I2C1
		PinCFG.GPIO_PinNumber = GPIO_PIN_6;
		PinCFG.GPIO_PinMODE = GPIO_MODE_OUTPUT_AF_OD;
		PinCFG.GPIO_PinSPEED = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOB, &PinCFG);
		//*******************************************************************************

		//*******************************************************************************
		//Configure SDA of I2C1
		PinCFG.GPIO_PinNumber = GPIO_PIN_7;
		PinCFG.GPIO_PinMODE = GPIO_MODE_OUTPUT_AF_OD;
		PinCFG.GPIO_PinSPEED = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOB, &PinCFG);
		//*******************************************************************************
	}
	else if(I2Cx == I2C2)
	{
		/*
		 * SCL --> PB10
		 * SDA --> PB11
		 */
		//*******************************************************************************
		//Configure SCL of I2C2
		PinCFG.GPIO_PinNumber = GPIO_PIN_10;
		PinCFG.GPIO_PinMODE = GPIO_MODE_OUTPUT_AF_OD;
		PinCFG.GPIO_PinSPEED = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOB, &PinCFG);
		//*******************************************************************************

		//*******************************************************************************
		//Configure SDA of I2C2
		PinCFG.GPIO_PinNumber = GPIO_PIN_11;
		PinCFG.GPIO_PinMODE = GPIO_MODE_OUTPUT_AF_OD;
		PinCFG.GPIO_PinSPEED = GPIO_SPEED_10MHz;
		MCAL_GPIO_Init(GPIOB, &PinCFG);
		//*******************************************************************************
	}
}

/**================================================================
 * @Fn			-MCAL_I2C_Master_Tx
 * @brief 		-Master transmit data
 * @param [in] 	-I2Cx: it is an instance from I2C (x --> 1..2)
 * @param [in] 	-Device_Address: it is the address of the slave that we need to send the data to it
 * @param [in] 	-*Data_Out: it is a pointer to the data that we need to send it
 * @param [in] 	-Data_Length: it is the length of the data that we need to send it
 * @param [in] 	-stop: it is determine that we need to end with stop condition or not
 * @param [in] 	-start: it is determine that we send start or repeated start
 * @retval 		-none
 * Note			-none
================================================================**/
void MCAL_I2C_Master_Tx(I2C_TypeDef *I2Cx, uint16_t Device_Address, uint8_t *Data_Out, uint16_t Data_Length, Stop_Generation stop, Start_State start)
{
	int i = 0;

	/* To Do:
	 * Support timeout (configure timer working for specific duration and then rise interrupt)
	 * timer_interrupt() { flag = 1}
	 * so any code exist in while should (check flag || check any polling conditions)
	 */

	//*******************************************************************************
	//1.Send Start Condition to switch the device from slave to master
	I2C_Generate_Start_Condition(I2Cx, Fun_enable, Start);
	//*******************************************************************************

	//*******************************************************************************
	//2.Wait for Event5
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
	while(!(I2C_Get_Flag_Status(I2Cx, EV5)));
	//*******************************************************************************

	//*******************************************************************************
	//3.Send Device Address
	I2C_Send_Address(I2Cx, Device_Address, I2C_Direction_Transimitter);
	//*******************************************************************************

	//*******************************************************************************
	//4.Wait for Event6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!(I2C_Get_Flag_Status(I2Cx, EV6)));
	//*******************************************************************************

	//*******************************************************************************
	//5.Check	--> TRA: Transmitter/receiver
	//			--> BUSY: bus is busy or not
	//			--> MSL: Master/slave Mode
	//			--> TXE:  Data register empty
	while(!(I2C_Get_Flag_Status(I2Cx, MASTER_BYTE_TRANSMITTING)));
	//*******************************************************************************

	//*******************************************************************************
	//6.Write Data in DR
	for(i = 0; i < Data_Length; i++)
	{
		I2Cx->DR = Data_Out[i];

		//*******************************************************************************
		//7.Wait for Event8
		//EV8: TxE=1, shift register not empty, d. ata register empty, cleared by writing DR register
		while(!(I2C_Get_Flag_Status(I2Cx, EV8)));
		//*******************************************************************************
	}
	//*******************************************************************************

	//*******************************************************************************
	//8.Stop Condition
	if(stop == With_Stop)
	{
		I2C_Generate_Stop_Condition(I2Cx, Fun_enable);
	}
	//*******************************************************************************
}

/**================================================================
 * @Fn			-MCAL_I2C_Master_Rx
 * @brief 		-Master receive data
 * @param [in] 	-I2Cx: it is an instance from I2C (x --> 1..2)
 * @param [in] 	-Device_Address: it is the address of the slave that we need to send the data to it
 * @param [in] 	-*Data_Out: it is a pointer that we use it to point to the data
 * @param [in] 	-Data_Length: it is the length of the data that we need to receive it
 * @param [in] 	-stop: it is determine that we need to end with stop condition or not
 * @param [in] 	-start: it is determine that we send start or repeated start
 * @retval 		-none
 * Note			-none
================================================================**/
void MCAL_I2C_Master_Rx(I2C_TypeDef *I2Cx, uint16_t Device_Address, uint8_t *Data_Out, uint16_t Data_Length, Stop_Generation stop, Start_State start)
{
	int i = 0;
	uint8_t Index = (I2Cx == I2C1)? I2C1_INDEX : I2C2_INDEX;

	//*******************************************************************************
	//1.Send Start Condition to switch the device from slave to master
	I2C_Generate_Start_Condition(I2Cx, Fun_enable, start);
	//*******************************************************************************

	//*******************************************************************************
	//2.Wait for Event5
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
	while(!(I2C_Get_Flag_Status(I2Cx, EV5)));
	//*******************************************************************************

	//*******************************************************************************
	//3.Send Device Address
	I2C_Send_Address(I2Cx, Device_Address, I2C_Direction_Receiver);
	//*******************************************************************************

	//*******************************************************************************
	//4.Wait for Event6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!(I2C_Get_Flag_Status(I2Cx, EV6)));
	//*******************************************************************************

	I2C_Acknowledge_Config(I2Cx, Fun_enable);

	/* Check Data length because if it is equal zero we won't receive any thing */
	if(Data_Length)
	{
		for(i = Data_Length; i > 1; i--)
		{
			//*******************************************************************************
			//5.Wait for Event7
			//EV7: RxNE = 1 cleared by reading DR register
			while(!(I2C_Get_Flag_Status(I2Cx, EV7)));
			//*******************************************************************************

			//*******************************************************************************
			//6.Read Data from DR
			*Data_Out = I2Cx->DR;
			Data_Out++;
			//*******************************************************************************
		}

		I2C_Acknowledge_Config(I2Cx, Fun_disable);
	}

	//*******************************************************************************
	//7.Stop Condition
	if(stop == With_Stop)
	{
		I2C_Generate_Stop_Condition(I2Cx, Fun_enable);
	}
	//*******************************************************************************

	//*******************************************************************************
	//Re-Enabel Acknowledge
	if(Gl_AI2C_CFG[Index].I2C_ACK_Control == I2C_ACK_Control_Enable)
	{
		I2C_Acknowledge_Config(I2Cx, Fun_enable);
	}
	//*******************************************************************************
}

/**================================================================
 * @Fn			-MCAL_I2C_Slave_Tx
 * @brief 		-Slave transmit data
 * @param [in] 	-I2Cx: it is an instance from I2C (x --> 1..2)
 * @param [in] 	-Data: it is the data that we need to sent it
 * @retval 		-it return the data that exist in Data Register
 * Note			-none
================================================================**/
void MCAL_I2C_Slave_Tx(I2C_TypeDef *I2Cx, uint8_t Data)
{
	I2Cx->DR = Data;
}

/**================================================================
 * @Fn			-MCAL_I2C_Slave_Rx
 * @brief 		-Slave receive data
 * @param [in] 	-I2Cx: it is an instance from I2C (x --> 1..2)
 * @retval 		-it return the data that exist in Data Register
 * Note			-none
================================================================**/
uint8_t MCAL_I2C_Slave_Rx(I2C_TypeDef *I2Cx)
{
	return (uint8_t)(I2Cx->DR);
}

void I2C1_EV_IRQHandler(void)
{
	volatile uint32_t dummy_Read = 0;
	I2C_TypeDef *I2Cx = I2C1;

	//interrupt handling for Master & Slave mode of a device
	uint32_t temp1, temp2, temp3;

	//*******************************************************************************
	temp1 = ( (I2Cx->CR2) & (I2C_CR2_ITEVTEN) );
	temp2 = ( (I2Cx->CR2) & (I2C_CR2_ITBUFEN) );
	//*******************************************************************************

	//*******************************************************************************
	temp3 = ( (I2Cx->SR1) & (I2C_SR1_STOPF) );

	//Handle For Interrupt generated by STOPF event
	//Note : Stop detection flag is applicable only slave mode
	if(temp1 && temp3)
	{
		// STOP Flag is Set
		// Clear the STOPF by reading SR1 register followed by writing to CR1 register
		dummy_Read = I2Cx->SR1;
		I2Cx->CR1 = 0x0000;
		Slave_States(I2Cx,I2C_EV_STOP);
	}
	//*******************************************************************************

	//*******************************************************************************
	temp3 = I2Cx->SR1 & (I2C_SR1_ADDR);

	//Handle For Interrupt generated by ADDR event
	//Note :When master mode : Address is sent
	//		When slave mode  : Address is matched with own address
	if(temp1 && temp3)
	{
		// Interrupt is generated because of ADDR event
		// check for device mode
		if(I2Cx->SR2 & (I2C_SR2_MSL))
		{
			//Master mode
		}
		else
		{
			//Slave mode
			//Clear the ADDR flag (Read SR1 , Read SR2)
			dummy_Read = I2Cx->SR1;
			dummy_Read = I2Cx->SR2;
			Slave_States(I2Cx,I2C_EV_ADDR_Matched);
		}
	}
	//*******************************************************************************

	//*******************************************************************************
	temp3 = I2Cx->SR1 & (I2C_SR1_TXE);

	//Handle For Interrupt generated by TXE event
	if(temp1 && temp3)
	{
		// Interrupt is generated because of TXE event
		// check for device mode
		if(I2Cx->SR2 & (I2C_SR2_MSL))
		{
			//Master mode
		}
		else
		{
			//Slave mode
			Slave_States(I2Cx,I2C_EV_DATA_REQ);
		}
	}
	//*******************************************************************************

	//*******************************************************************************
	temp3 = I2Cx->SR1 & (I2C_SR1_RXNE);

	//Handle For Interrupt generated by RXNE event
	if(temp1 && temp3)
	{
		// Interrupt is generated because of RXNE event
		// check for device mode
		if(I2Cx->SR2 & (I2C_SR2_MSL))
		{
			//Master mode
		}
		else
		{
			//Slave mode
			Slave_States(I2Cx,I2C_EV_DATA_RCV);
		}
	}
	//*******************************************************************************
}

void I2C1_ER_IRQHandler(void)
{

}

void I2C2_EV_IRQHandler(void)
{

}

void I2C2_ER_IRQHandler(void)
{

}











