MMCU=atxmega128a1
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-g -mmcu=$(MMCU)

all:rom.hex

rom.hex:main.out
	$(OBJCOPY) -O ihex main.out rom.hex
main.out:main.o
	$(CC) $(CFLAGS) -o main.out -Wl,-Map,main.map main.o

main.o:main.c
	$(CC) $(CFLAGS) -Os -c main.c

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

clean:
	rm -f *.out *.o *.hex *.map
