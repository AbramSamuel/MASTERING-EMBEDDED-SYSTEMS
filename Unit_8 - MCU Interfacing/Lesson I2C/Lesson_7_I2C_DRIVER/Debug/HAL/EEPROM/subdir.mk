################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/EEPROM/I2C_SLAVE_EEPROM.c 

OBJS += \
./HAL/EEPROM/I2C_SLAVE_EEPROM.o 

C_DEPS += \
./HAL/EEPROM/I2C_SLAVE_EEPROM.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/EEPROM/I2C_SLAVE_EEPROM.o: ../HAL/EEPROM/I2C_SLAVE_EEPROM.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"E:/Mastering EMBDDED SYSTEMS Diploma Online/Unit 8 - MCU Interfacing/Lesson_7_I2C_DRIVER/HAL/EEPROM" -I"E:/Mastering EMBDDED SYSTEMS Diploma Online/Unit 8 - MCU Interfacing/Lesson_7_I2C_DRIVER/STM32F103C6_DRIVERS/INCLUDE" -I"E:/Mastering EMBDDED SYSTEMS Diploma Online/Unit 8 - MCU Interfacing/Lesson_7_I2C_DRIVER/STM32F103C6_DRIVERS/MCAL/EXTI" -I"E:/Mastering EMBDDED SYSTEMS Diploma Online/Unit 8 - MCU Interfacing/Lesson_7_I2C_DRIVER/STM32F103C6_DRIVERS/MCAL/GPIO" -I"E:/Mastering EMBDDED SYSTEMS Diploma Online/Unit 8 - MCU Interfacing/Lesson_7_I2C_DRIVER/STM32F103C6_DRIVERS/MCAL/I2C" -I"E:/Mastering EMBDDED SYSTEMS Diploma Online/Unit 8 - MCU Interfacing/Lesson_7_I2C_DRIVER/STM32F103C6_DRIVERS/MCAL/RCC" -I"E:/Mastering EMBDDED SYSTEMS Diploma Online/Unit 8 - MCU Interfacing/Lesson_7_I2C_DRIVER/STM32F103C6_DRIVERS/MCAL/USART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/EEPROM/I2C_SLAVE_EEPROM.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

