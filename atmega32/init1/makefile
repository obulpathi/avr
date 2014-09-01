MMCU=atmega32
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-g -mmcu=$(MMCU)

flash:rom.hex
	avrdude -F -P usb -B 10 -c dragon_isp -p $(MMCU) -U flash:w:rom.hex:i

rom.hex:main.out
	$(OBJCOPY) -j .text -O ihex main.out rom.hex

main.out:main.o
	$(CC) $(CFLAGS) -o main.out -Wl,-Map,main.map main.o

main.o:main.c main.h global.h makefile
	$(CC) $(CFLAGS) -Os -c main.c

xram.o:xram.S
	avr-as xram.S -o xram.s

rflash:
	avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U flash:r:flash.rom:i

rfuse:
	avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U lfuse:r:-:i
	sleep 2
	avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U hfuse:r:-:i

wfuse:
	avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U lfuse:w:lfuse:i
	sleep 2
	avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U hfuse:w:hfuse:i

readeeprom:
	avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U eeprom:r:eeprom_read.hex:i

writeeeprom:
	avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U eeprom:w:eeprom_write.hex:i

clean:
	rm -f *.out *.o *.hex
