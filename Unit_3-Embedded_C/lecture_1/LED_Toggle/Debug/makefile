################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
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
Lab1_LED_Toggle.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Lab1_LED_Toggle.list \

OBJCOPY_HEX += \
Lab1_LED_Toggle.hex \

OBJCOPY_BIN += \
Lab1_LED_Toggle.bin \


# All Target
all: Lab1_LED_Toggle.elf secondary-outputs

# Tool invocations
Lab1_LED_Toggle.elf: $(OBJS) $(USER_OBJS) E:\Mastering\ EMBDDED\ SYSTEMS\ Diploma\ Online\Unit\ 3\ -\ Embedded\ C\Projects\Lab1_LED_Toggle\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -o "Lab1_LED_Toggle.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"E:\Mastering EMBDDED SYSTEMS Diploma Online\Unit 3 - Embedded C\Projects\Lab1_LED_Toggle\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Lab1_LED_Toggle.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Lab1_LED_Toggle.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Lab1_LED_Toggle.list"
	@echo 'Finished building: $@'
	@echo ' '

Lab1_LED_Toggle.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Lab1_LED_Toggle.hex"
	@echo 'Finished building: $@'
	@echo ' '

Lab1_LED_Toggle.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Lab1_LED_Toggle.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
