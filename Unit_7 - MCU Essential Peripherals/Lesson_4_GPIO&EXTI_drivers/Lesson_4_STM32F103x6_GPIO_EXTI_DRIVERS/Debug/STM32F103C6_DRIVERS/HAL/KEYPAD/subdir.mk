################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F103C6_DRIVERS/HAL/KEYPAD/keypad.c 

OBJS += \
./STM32F103C6_DRIVERS/HAL/KEYPAD/keypad.o 

C_DEPS += \
./STM32F103C6_DRIVERS/HAL/KEYPAD/keypad.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F103C6_DRIVERS/HAL/KEYPAD/keypad.o: ../STM32F103C6_DRIVERS/HAL/KEYPAD/keypad.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"E:/Mastering EMBDDED SYSTEMS Diploma Online/Unit 7 - MCU Essential Peripherals/Lesson_4_STM32F103x6_DRIVERS(GPIO&EXTI)/STM32F103C6_DRIVERS/MCAL/GPIO" -I"E:/Mastering EMBDDED SYSTEMS Diploma Online/Unit 7 - MCU Essential Peripherals/Lesson_4_STM32F103x6_DRIVERS(GPIO&EXTI)/STM32F103C6_DRIVERS/MCAL/EXTI" -I"E:/Mastering EMBDDED SYSTEMS Diploma Online/Unit 7 - MCU Essential Peripherals/Lesson_4_STM32F103x6_DRIVERS(GPIO&EXTI)/STM32F103C6_DRIVERS/INCLUDE" -I"E:/Mastering EMBDDED SYSTEMS Diploma Online/Unit 7 - MCU Essential Peripherals/Lesson_4_STM32F103x6_DRIVERS(GPIO&EXTI)/STM32F103C6_DRIVERS/HAL/KEYPAD" -I"E:/Mastering EMBDDED SYSTEMS Diploma Online/Unit 7 - MCU Essential Peripherals/Lesson_4_STM32F103x6_DRIVERS(GPIO&EXTI)/STM32F103C6_DRIVERS/HAL/LCD" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_DRIVERS/HAL/KEYPAD/keypad.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

