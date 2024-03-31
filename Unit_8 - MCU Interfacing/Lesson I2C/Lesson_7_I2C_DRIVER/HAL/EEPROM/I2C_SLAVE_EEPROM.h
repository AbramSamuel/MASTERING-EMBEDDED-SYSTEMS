/*
 * I2C_SLAVE_EEPROM.h
 *
 *  Created on: Feb 21, 2024
 *      Author: ABRAM
 */

#ifndef EEPROM_I2C_SLAVE_EEPROM_H_
#define EEPROM_I2C_SLAVE_EEPROM_H_

#include "STM32F103C6_I2C_DRIVER.h"

// EEPROM is an I2C Slave
// Idle Mode: device is high-impedance state and waits for data.
// Master Transmitter Mode: the device transmits data to a slave receiver.
// Master Receiver Mode: the device receives data from a slave transmitter.

#define EEPROM_Slave_Address						0x2A


//======================================================================
/*
 * ======================================================================
 * 			APIs Supported by "HAL EEPROM Driver"
 * ======================================================================
 */

//*******************************************************************************
void EEPROM_INITIALIZE(void);
//*******************************************************************************

//*******************************************************************************
uint8_t EEPROM_Write_NBytes(uint32_t Memory_Address, uint8_t *Data, uint8_t Data_Length);
uint8_t EEPROM_Read_NBytes(uint32_t Memory_Address, uint8_t *Data_Out, uint8_t Data_Length);
//*******************************************************************************


#endif /* EEPROM_I2C_SLAVE_EEPROM_H_ */
