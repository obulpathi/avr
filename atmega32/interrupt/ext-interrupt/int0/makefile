MMCU=atmega32
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-g -mmcu=$(MMCU)

all:rom.hex

rom.hex:main.out
	$(OBJCOPY) -j .text -O ihex main.out rom.hex

main.out:main.o
	$(CC) $(CFLAGS) -o main.out -Wl,-Map,main.map main.o

main.o:main.c
	$(CC) $(CFLAGS) -Os -c main.c

flash:rom.hex
	uisp -dlpt=/dev/parport0 --erase --upload if=rom.hex -dprog=dapa

clean:
	rm -f main.out
	rm -f main.o
	rm -f rom.hex
