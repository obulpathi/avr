MMCU=atxmega128a1
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-g -mmcu=$(MMCU) -std=c99

all:
	avr-gcc -mmcu=$(MMCU) -c des.s -o des.o
	$(CC) $(CFLAGS) -c main.c -o main.o
	$(CC) $(CFLAGS) main.o des.o -o main.elf
	avr-objcopy -O ihex main.elf rom.hex

read:
	avrdude -P usb -B 10 -c avrispmkII -p $(MMCU) -U flash:r:xplain.hex:i
	
flash:
	avrdude -P usb -B 10 -c avrispmkII -p $(MMCU) -U flash:w:rom.hex:i

erase:
	avrdude -e -P usb -B 10 -c avrispmkII -p $(MMCU)

read_eeprom:
	avrdude -P usb -B 10 -c avrispmkII -p $(MMCU) -U eeprom:r:eeprom.hex:i

write_eeprom:
	avrdude -P usb -B 10 -c avrispmkII -p $(MMCU) -U eeprom:w:eeprom.hex:i

celan:
	rm -f *.out .o *.hex *.map

clean:
	rm -f *.out .o *.hex *.map
