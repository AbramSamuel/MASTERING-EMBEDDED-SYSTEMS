# ENG. Abram Samuel

CC=arm-none-eabi-
CFLAGS =-mcpu=cortex-m4 -mthumb -gdwarf-2 -g 
INCS = -I .
SRC =$(wildcard *.c)
OBJ = $(SRC:.c=.o)
As = $(wildcard *.s)
AsOBJ = $(As:.s=.o)

Project_Name=PRESSURE_DETECTION


all: $(Project_Name).bin
	@echo "             ==========>DONE<==========            "

$(Project_Name).bin: $(Project_Name).elf
	$(CC)objcopy.exe -O binary $< $@



%.o: %.c
	$(CC)gcc.exe  $(INCS) $(CFLAGS) -c $< -o $@


$(Project_Name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T Linker.ld  $(OBJ) $(AsOBJ) -o $@ -Map=Map_File.map
	cp $(Project_Name).elf $(Project_Name).axf

clean_all:
	rm *.o *.elf *.bin *.elf.asm *.axf

clean:
	rm *.elf *.bin