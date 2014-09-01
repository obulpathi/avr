MMCU=atmega168
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-g -mmcu=$(MMCU)

rom.hex:main.out
	$(OBJCOPY) -j .text -O ihex main.out rom.hex

main.out:main.o
	$(CC) $(CFLAGS) -o main.out -Wl,-Map,main.map main.o

main.o:main.c main.h global.h makefile
	$(CC) $(CFLAGS) -Os -c main.c

clean:
	rm -f *.out *.o *.hex

start:
	sudo dfu-programmer atmega168 start

erase:
	sudo dfu-programmer atmega168 erase
	
flash:rom.hex
	sudo avrdude dfu-programmer atmega168 flash rom.hex

rflash:
	avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U flash:r:flash.rom:i

dump:
	dfu-programmer atmega168 dump
