################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F103C6_DRIVERS/MCAL/EXTI/STM32F103C6_EXTI_DRIVER.c 

OBJS += \
./STM32F103C6_DRIVERS/MCAL/EXTI/STM32F103C6_EXTI_DRIVER.o 

C_DEPS += \
./STM32F103C6_DRIVERS/MCAL/EXTI/STM32F103C6_EXTI_DRIVER.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F103C6_DRIVERS/MCAL/EXTI/STM32F103C6_EXTI_DRIVER.o: ../STM32F103C6_DRIVERS/MCAL/EXTI/STM32F103C6_EXTI_DRIVER.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"E:/Mastering EMBDDED SYSTEMS Diploma Online/Unit 8 - MCU Interfacing/Lesson_5_SPI_DRIVER_Lab_1/STM32F103C6_DRIVERS/INCLUDE" -I"E:/Mastering EMBDDED SYSTEMS Diploma Online/Unit 8 - MCU Interfacing/Lesson_5_SPI_DRIVER_Lab_1/STM32F103C6_DRIVERS/MCAL/EXTI" -I"E:/Mastering EMBDDED SYSTEMS Diploma Online/Unit 8 - MCU Interfacing/Lesson_5_SPI_DRIVER_Lab_1/STM32F103C6_DRIVERS/MCAL/GPIO" -I"E:/Mastering EMBDDED SYSTEMS Diploma Online/Unit 8 - MCU Interfacing/Lesson_5_SPI_DRIVER_Lab_1/STM32F103C6_DRIVERS/MCAL/RCC" -I"E:/Mastering EMBDDED SYSTEMS Diploma Online/Unit 8 - MCU Interfacing/Lesson_5_SPI_DRIVER_Lab_1/STM32F103C6_DRIVERS/MCAL/SPI" -I"E:/Mastering EMBDDED SYSTEMS Diploma Online/Unit 8 - MCU Interfacing/Lesson_5_SPI_DRIVER_Lab_1/STM32F103C6_DRIVERS/MCAL/USART" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_DRIVERS/MCAL/EXTI/STM32F103C6_EXTI_DRIVER.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

