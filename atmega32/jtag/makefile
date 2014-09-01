MMCU=atmega128
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
	sudo avrdude -P usb -B 10 -c dragon_jtag -p $(MMCU) -U flash:w:rom.hex:i

rflash:
	avrdude -P usb -B 10 -c dragon_jtag -p $(MMCU) -U flash:r:rom1.hex:i

lfuse:
	avrdude -P usb -B 10 -c dragon_jtag -p $(MMCU) -U lfuse:r:lfuses:i

hfuse:
	avrdude -P usb -B 10 -c dragon_jtag -p $(MMCU) -U hfuse:r:hfuses:i

reeprom:
	avrdude -P usb -B 10 -c dragon_jtag -p $(MMCU) -U eeprom:r:eeprom_read.hex:i

weeprom:
	avrdude -P usb -B 10 -c dragon_jtag -p $(MMCU) -U eeprom:w:eeprom_write.hex:i

debug:
	avarice --program --file [app name].elf --part [platform name] --jtag [device location] :[port number]

celan:
	rm -f main.out
	rm -f main.o
	rm -f rom.hex

clean:
	rm -f main.out
	rm -f main.o
	rm -f rom.hex
