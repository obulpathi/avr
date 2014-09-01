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
	avrdude -P /dev/ttyUSB0 -B 10 -c stk500v2 -p $(MMCU) -U flash:w:rom.hex:i

rflash:
	avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U flash:r:rom1.hex:i

lfuses:
	avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U lfuse:r:lfuses:i

hfuses:
	avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U hfuse:r:hfuses:i

reeprom:
	avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U eeprom:r:eeprom_read.hex:i

weeprom:
	avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U eeprom:w:eeprom_write.hex:i

celan:
	rm -f main.out
	rm -f main.o
	rm -f rom.hex

clean:
	rm -f main.out
	rm -f main.o
	rm -f rom.hex
