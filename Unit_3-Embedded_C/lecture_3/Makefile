# ENG. Abram Samuel

CC=arm-none-eabi-
CFLAGS =-mcpu=cortex-m3 -mthumb -gdwarf-2  
INCS = -I .
SRC =$(wildcard *.c)
OBJ = $(SRC:.c=.o)
As = $(wildcard *.s)
AsOBJ = $(As:.s=.o)

Project_Name=learn-in-depth_cortex-m3


all: $(Project_Name).bin
	@echo "             ==========>DONE<==========            "

$(Project_Name).bin: $(Project_Name).elf
	$(CC)objcopy.exe -O binary $< $@



%.o: %.c
	$(CC)gcc.exe  $(INCS) $(CFLAGS) -c $< -o $@


$(Project_Name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T Linker_Script.ld  $(OBJ) $(AsOBJ) -o $@ -Map=Map_File.map

clean_all:
	rm *.o *.elf *.bin

clean:
	rm *.elf *.bin