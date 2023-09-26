################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include STM32F103C6_DRIVERS/MCAL/GPIO/subdir.mk
-include STM32F103C6_DRIVERS/MCAL/EXTI/subdir.mk
-include STM32F103C6_DRIVERS/HAL/LCD/subdir.mk
-include STM32F103C6_DRIVERS/HAL/KEYPAD/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Lesson_4_STM32F103x6_DRIVERS(GPIO&EXTI).elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Lesson_4_STM32F103x6_DRIVERS(GPIO&EXTI).list \

OBJCOPY_BIN += \
Lesson_4_STM32F103x6_DRIVERS(GPIO&EXTI).bin \


# All Target
all: Lesson_4_STM32F103x6_DRIVERS(GPIO&EXTI).elf secondary-outputs

# Tool invocations
Lesson_4_STM32F103x6_DRIVERS(GPIO&EXTI).elf: $(OBJS) $(USER_OBJS) E:\Mastering\ EMBDDED\ SYSTEMS\ Diploma\ Online\Unit\ 7\ -\ MCU\ Essential\ Peripherals\Lesson_4_STM32F103x6_DRIVERS(GPIO&EXTI)\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "Lesson_4_STM32F103x6_DRIVERS(GPIO&EXTI).elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"E:\Mastering EMBDDED SYSTEMS Diploma Online\Unit 7 - MCU Essential Peripherals\Lesson_4_STM32F103x6_DRIVERS(GPIO&EXTI)\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Lesson_4_STM32F103x6_DRIVERS(GPIO&EXTI).map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Lesson_4_STM32F103x6_DRIVERS(GPIO&EXTI).list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Lesson_4_STM32F103x6_DRIVERS(GPIO&EXTI).list"
	@echo 'Finished building: $@'
	@echo ' '

Lesson_4_STM32F103x6_DRIVERS(GPIO&EXTI).bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Lesson_4_STM32F103x6_DRIVERS(GPIO&EXTI).bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
