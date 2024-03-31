/*
 * I2C_SLAVE_EEPROM.c
 *
 *  Created on: Feb 21, 2024
 *      Author: ABRAM
 */
#include "I2C_SLAVE_EEPROM.h"

void EEPROM_INITIALIZE(void)
{
	/*-------------------------------I2C Init--------------------------*/
	//			PB6: I2C1_SCL
	//			PB7: I2C2_SDA

	I2C_Configuration_t I2C1_CFG;

	/*-------------------------------I2C controller act as a Master--------------------------*/
	I2C1_CFG.I2C_Mode = I2C_Mode_I2C;
	I2C1_CFG.I2C_General_Call_Control= I2C_Clock_Stretching_Enable;
	I2C1_CFG.I2C_ACK_Control = I2C_ACK_Control_Enable;
	I2C1_CFG.I2C_ClockSpeed = I2C_ClockSpeed_SM_100KHz;
	I2C1_CFG.I2C_Clock_Stretching= I2C_Clock_Stretching_Enable;
	I2C1_CFG.PF_Slave_Event_CallBack = NULL;

	MCAL_GPIO_I2C_Set_Pins(I2C1);
	MCAL_I2C_Init(I2C1, &I2C1_CFG);
}

uint8_t EEPROM_Write_NBytes(uint32_t Memory_Address, uint8_t *Data, uint8_t Data_Length)
{
	uint8_t i = 0;

	//MISRA C++ 2008, 18-4-1 : Dynamic Memory Allocation shall not be used
	//Violate MISRA Rule
	//uint8_t *buffer = (unsigned char *)malloc(Data_Length+2);

	uint8_t buffer[256];
	buffer[0] = (uint8_t)(Memory_Address >> 8);	//upper byte of Memory address
	buffer[1] = (uint8_t)(Memory_Address);	//lower byte of Memory address

	for(i = 2; i < (Data_Length+2); i++)
	{
		buffer[i] = Data[i-2];
	}

	void MCAL_I2C_Master_Tx(I2C_TypeDef *I2Cx, uint16_t Device_Address, uint8_t *Data_Out, uint16_t Data_Length, Stop_Generation stop, Start_State start);
	return 0;
}

uint8_t EEPROM_Read_NBytes(uint32_t Memory_Address, uint8_t *Data_Out, uint8_t Data_Length)
{
	uint8_t buffer[2];
	buffer[0] = (uint8_t)(Memory_Address >> 8);	//upper byte of Memory address
	buffer[1] = (uint8_t)(Memory_Address);	//lower byte of Memory address

	void MCAL_I2C_Master_Tx(I2C_TypeDef *I2Cx, uint16_t Device_Address, uint8_t *Data_Out, uint16_t Data_Length, Stop_Generation stop, Start_State start);
	void MCAL_I2C_Master_Rx(I2C_TypeDef *I2Cx, uint16_t Device_Address, uint8_t *Data_Out, uint16_t Data_Length, Stop_Generation stop, Start_State start);
	return 0;
}

