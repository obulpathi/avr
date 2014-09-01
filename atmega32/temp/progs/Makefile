# AVR-GCC Makefile
#**************************************************************
.SUFFIXES:
.SUFFIXES:	.S .c .o .cof .elf .eep .rom

#--- define some variables based on the AVR base path in $(AVR)
CC	= avr-gcc
AS	= avr-gcc
RM	= rm -f
RN	= mv
CP      = cp
BIN	= avr-objcopy
ELFCOF  = objtool
INCDIR	= .

#If all other steps compile ok then echo "Errors: none".
#Necessary for AVR Studio to understand that everything went ok.
DONE    = @echo Errors: none


#--- default mcu type
MCU = atmega32

#--- default compiler flags -ahlmsn
CPFLAGS = -g -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wall -Wstrict-prototypes -mmcu=$(MCU) -Wa,-ahlmsnd=$(<:.c=.lst)

#--- default assembler flags 
ASFLAGS = -mmcu=$(MCU) -Wa,-mmcu=$(MCU),-gstabs

#--- default linker flags
#LDFLAGS = -Wl,-Map=$(<:.o=.map),--cref -mmcu=$(MCU),-lm
LDFLAGS=-Wl,-Map=$(<:.o=.map),-lm,--cref -mmcu=$(MCU)

#--- output format can be srec (Motorola), ihex (Intel HEX)
ROMFORMAT 	= srec
EEPROMFORMAT    = ihex    # AVR Studio needs Intel HEX format


#--- compile: instructions to create assembler and/or object files from C source
#.c.o:
%o : %c 
	$(CC) -c $(CPFLAGS) -I$(INCDIR) $< -o $@

%s : %c
	$(CC) -s $(CPFLAGS) -I$(INCDIR) $< -o $@


#--- assemble: instructions to create object file from assembler source
%o : %S
	$(AS) -x assembler-with-cpp $(ASFLAGS) -I$(INCDIR) -c $< -o $@

%: %.c
	@echo "Error: target $@ not defined in Makefile"
	@exit 1


#--- link: instructions to create elf output file from object files
%elf:	%o
	$(CC) $^ $(LIB) $(LDFLAGS) -o $@

#--- create AVR Studio cof file from elf output file and map file
%cof: %elf
	$(ELFCOF) loadelf $^ mapfile $(<:.elf=.map) writecof $@

#--- create flash and eeprom bin file (ihex, srec) from elf output file
%hex: %elf
	$(BIN) -O $(ROMFORMAT) -R .eeprom $< $@

%eep: %elf
	$(BIN) -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O $(EEPROMFORMAT) $< $(@:.elf=.eep)


#*************************** add your projects below **************************************


#--- this defines the aims of the make process
all:	Flash

flash:
	 uisp -dprog=stk500 -dserial=/dev/ttyS0 -dpart=atmega32 --erase --upload --verify if=Flash.hex

clean:
	$(RM) *.hex *.eep *.cof
	$(RM) *.o 
	$(RM) *.elf 
	$(RM) *.lst 
	$(RM) *.map
	$(RM) *.rom

#-------- Flash library
Flash:	Flash.hex
	$(DONE)

Flash.elf:	Flash.o usart.o

Flash.o:	Flash.c usart.h

#-------- usart library
usart.o:	usart.c usart.h

