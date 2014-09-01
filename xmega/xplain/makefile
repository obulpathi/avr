MMCU=atxmega128a1
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

read:
	sudo avrdude -P usb -B 10 -c jtagmkII -p atxmega128a1 -U flash:r:xplain.hex:i
	
flash:
	sudo avrdude -P usb -B 10 -c avrispmkII -p atxmega128a1 -U flash:w:rom.hex:i

erase:
	avrdude -e -P /dev/ttyUSB0 -b 9600 -c jtag1 -p atxmega128a1 -U flash:w:rom.hex:i

rflash:
	avrdude -P /dev/ttyUSB0 -B 10 -c dragon_isp -p $(MMCU) -U flash:r:rom1.hex:i

lfuses:
	avrdude -P /dev/ttyUSb0 -B 10 -c jtag1 -p $(MMCU) -U lfuse:r:lfuses:i

hfuses:
	avrdude -P /dev/ttyUSB0 -B 10 -c jtag1 -p $(MMCU) -U hfuse:r:hfuses:i

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
