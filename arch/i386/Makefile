# CROSS_COMPILE ?= /home/tuxx/opt/cross/bin/i686-elf-
CFLAGS=-nostdlib -m32 -ffreestanding -O0 -Wall -Wextra -std=gnu99 -I.
LDFLAGS=-m32 -nostdlib -Wl,-N -Wl,-Ttext -Wl,100000
OBJ=boot.o gdt.o kernel.o common.o vesa.o

all: $(OBJ)
	$(CROSS_COMPILE)gcc -T linker.ld -o myos.bin $(CFLAGS) *.o -lgcc

%.o: %.c
	$(CROSS_COMPILE)gcc -c $< -o $@ $(CFLAGS)

%.o: %.s
	$(CROSS_COMPILE)gcc -c $< -o $@ $(CFLAGS)

clean:
	rm *.o
