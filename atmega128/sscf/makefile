MMCU=atmega128
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-g -mmcu=$(MMCU)

all:rom.hex

rom.hex:main.out
	$(OBJCOPY) -j .text -O ihex main.out rom.hex

main.out:main.o sscf.o
	$(CC) $(CFLAGS) -o main.out -Wl,-Map,main.map main.o sscf.o

main.o:main.c main.h
	$(CC) $(CFLAGS) -Os -c main.c

sscf.o:sscf.c sscf.h
	$(CC) $(CFLAGS) -Os -c sscf.c

flash:rom.hex
	uisp -dlpt=/dev/parport0 --erase --upload if=rom.hex -dprog=dapa

clean:
	rm -f main.out
	rm -f main.o
	rm -f rom.hex
