all:main.elf
	avr-objcopy -j .text -O ihex main.elf rom.hex

main.elf:main.asm
	avr-gcc -mmcu=atmega32 main.asm -o main.elf

asm:
	avr-gcc -S main.c -o main.asm
