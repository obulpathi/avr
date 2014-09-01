MMCU=atmega328p
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

celan:
	rm -f *out *o *hex *map

clean:
	rm -f *out *o *hex *map

flash:
	avrdude -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b57600 -D -U flash:w:rom.hex
