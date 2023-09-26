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
Section_3_DRIVERS\ (LCD&KEYPAD).elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Section_3_DRIVERS\ (LCD&KEYPAD).list \

OBJCOPY_BIN += \
Section_3_DRIVERS\ (LCD&KEYPAD).bin \


# All Target
all: Section_3_DRIVERS\ (LCD&KEYPAD).elf secondary-outputs

# Tool invocations
Section_3_DRIVERS\ (LCD&KEYPAD).elf: $(OBJS) $(USER_OBJS) E:\Mastering\ EMBDDED\ SYSTEMS\ Diploma\ Online\Unit\ 7\ -\ MCU\ Essential\ Peripherals\DRIVERS\ _section_3_LCD_KEYPAD\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "Section_3_DRIVERS (LCD&KEYPAD).elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"E:\Mastering EMBDDED SYSTEMS Diploma Online\Unit 7 - MCU Essential Peripherals\DRIVERS _section_3_LCD_KEYPAD\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Section_3_DRIVERS (LCD&KEYPAD).map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Section_3_DRIVERS\ (LCD&KEYPAD).list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Section_3_DRIVERS (LCD&KEYPAD).list"
	@echo 'Finished building: $@'
	@echo ' '

Section_3_DRIVERS\ (LCD&KEYPAD).bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Section_3_DRIVERS (LCD&KEYPAD).bin"
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
