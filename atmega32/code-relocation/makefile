MMCU=atmega32
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-g -mmcu=$(MMCU)

flash:rom.hex
	avrdude -P usb -B 10 -c dragon_isp -p $(MMCU) -U flash:w:rom.hex:i

rom.hex:main.out
	$(OBJCOPY) -j .text -j .data -j .bootloader -O ihex main.out rom.hex

main.out:main.o my_boot.o
	$(CC) $(CFLAGS) -Wl,--section-start=.bootloader=0x7E00 -o rom.elf main.o my_boot.o -o main.out

main.o:main.c main.h makefile
	$(CC) $(CFLAGS) -Os -c main.c -o main.o

my_boot.o:my_boot.c my_boot.h makefile
	$(CC) $(CFLAGS) -Os -c my_boot.c -o my_boot.o

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
