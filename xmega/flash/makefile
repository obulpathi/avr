MMCU=atxmega128a1
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-g -mmcu=$(MMCU) -std=c99

all:
	$(CC) $(CFLAGS) -c -o main.o main.c
	$(CC) $(CFLAGS) -o main.elf -Wl,-Map,main.map main.o
	$(OBJCOPY) -O ihex main.out rom.hex

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
	rm -f *.out *.o *.hex *.map

clean:
	rm -f *.out *.o *.hex *.map
