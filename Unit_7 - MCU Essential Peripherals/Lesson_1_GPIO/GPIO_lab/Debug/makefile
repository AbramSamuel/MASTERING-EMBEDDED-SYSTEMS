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
Lesson_1_GPIO.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Lesson_1_GPIO.list \

OBJCOPY_HEX += \
Lesson_1_GPIO.hex \

OBJCOPY_BIN += \
Lesson_1_GPIO.bin \


# All Target
all: Lesson_1_GPIO.elf secondary-outputs

# Tool invocations
Lesson_1_GPIO.elf: $(OBJS) $(USER_OBJS) E:\Mastering\ EMBDDED\ SYSTEMS\ Diploma\ Online\Unit\ 6\ -\ Micro-controller\ Arch\Lesson_1_GPIO\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "Lesson_1_GPIO.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"E:\Mastering EMBDDED SYSTEMS Diploma Online\Unit 6 - Micro-controller Arch\Lesson_1_GPIO\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Lesson_1_GPIO.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Lesson_1_GPIO.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Lesson_1_GPIO.list"
	@echo 'Finished building: $@'
	@echo ' '

Lesson_1_GPIO.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Lesson_1_GPIO.hex"
	@echo 'Finished building: $@'
	@echo ' '

Lesson_1_GPIO.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Lesson_1_GPIO.bin"
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
