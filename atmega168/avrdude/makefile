MMCU=atmega168
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

flash:
	sudo avrdude -P /dev/ttyUSB0 -B 10 -c stk500v2 -p atmega168 -U flash:w:rom.hex:i

rflash:
	sudo avrdude -P /dev/ttyUSB0 -B 10 -c stk500v2 -p m168 -U flash:r:romr.hex:i

celan:
	rm -f *out *o *hex *map

clean:
	rm -f *out *o *hex *map
