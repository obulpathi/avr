MMCU=atmega1281
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
	sudo avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U flash:w:rom.hex:i

rflash:
	sudo avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U flash:r:-:i

rfuse:
	sudo avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U lfuse:r:-:i
	sleep 2
	sudo avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U hfuse:r:-:i

wfuse:
	sudo avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U lfuse:w:lfuse:i
	sleep 2
	sudo avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U hfuse:w:hfuse:i

readeeprom:
	sudo avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U eeprom:r:eeprom_read.hex:i

writeeeprom:
	sudo avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U eeprom:w:eeprom_write.hex:i

celan:
	rm -f main.out
	rm -f main.o
	rm -f rom.hex

clean:
	rm -f main.out
	rm -f main.o
	rm -f rom.hex
