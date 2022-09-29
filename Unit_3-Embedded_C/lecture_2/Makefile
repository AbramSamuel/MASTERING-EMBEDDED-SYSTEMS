# Abram Samuel
CC=arm-none-eabi-
CFLAGS =-mcpu=arm926ej-s -g
INCS = -I .
SRC =$(wildcard *.c)
OBJ = $(SRC:.c=.o)
Project_Name=learn-in-depth


all: $(Project_Name).bin
	@echo "             ==========>DONE<==========            "

$(Project_Name).bin: $(Project_Name).elf
	$(CC)objcopy.exe -O binary $< $@

startup.o: startup.s 
	$(CC)as.exe $(CFLAGS) $< -o $@

%.o: %.c
	$(CC)gcc.exe  $(INCS) $(CFLAGS) -c $< -o $@


$(Project_Name).elf: $(OBJ) startup.o
	$(CC)ld.exe -T Linker_Script.ld startup.o $(OBJ) -o $@ -Map=Map_File.map

clean_all:
	rm *.o *.elf *.bin

clean:
	rm *.elf *.bin