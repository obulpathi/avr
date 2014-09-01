
############## TARGET ######################
MCU_TARGET     = atmega128

###### BOOTLOADER START LOCATION ###########

# this is for atmega128
BOOTLOADER_START = 0x1E000
//BOOTLOADER_START = 0xFE00

# this is for atmega64
#BOOTLOADER_START = 0x3800

######### RESET VECTOR ####################
# Reset goes to BOOTLOADER_START
FUSES = ff18ff

# Reset goes to 0x00
#FUSES = ff19ff

#######  BOOTLOADER MODE ##################
# use the UART code 
DEFS           = -DBOOT_UART
# use the USB code
#DEFS           = -DBOOT_USB

#########################################
# DO NOT EDIT ANYTHING BELOW THIS POINT #
#########################################
PRG            = rom
OBJ	       = main.o bootloader.o 
OPTIMIZE       = -Os
INCDIR         = .

LIBS           =

IFLAGS         =  -Wstrict-prototypes -Wa,-adhlmsn=$(<:.c=.lst)
LFLAGS         = 

# You should not have to change anything below here.

CC             = avr-gcc
AS             = avr-gcc
LD	       = $(CC) -mmcu=$(MCU_TARGET)


# Override is only needed by avr-lib build system.

override CFLAGS = -g -Wall $(OPTIMIZE) $(IFLAGS) $(LFLAGS) -mmcu=$(MCU_TARGET) $(DEFS)
override LDFLAGS = -Wl,-Map,$(PRG).map,--section-start=.bootloader=$(BOOTLOADER_START) 
ASFLAGS = -mmcu=$(MCU_TARGET) -Wa,-mmcu=$(MCU_TARGET),-gstabs

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

all:  $(PRG).elf lst text

$(PRG).elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf $(OBJ) $(PRG).elf *.eps *.png *.pdf *.bak 
	rm -rf *.bin *.srec *.hex
	rm -rf *.lst *.map $(EXTRA_CLEAN_FILES)
	rm -rf *.bin *.hex *.srec

upload: $(PRG).bin
	avarice --write-fuses $(FUSES) --program -f $^

#debug: $(PRG).bin
#	avarice  --file $(PRG).bin   10.0.3.1  4500
#
#debug2: $(PRG).bin
#	avarice  10.0.3.1  4500

lst:  $(PRG).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

# Rules for compiling assembly code
%o : %S
	$(AS) -x assembler-with-cpp $(ASFLAGS) -I$(INCDIR) -c $< -o $@


# Rules for building the .text rom images

text: hex bin srec

hex:  $(PRG).hex
bin:  $(PRG).bin
smallbin:  $(PRG).smallbin
srec: $(PRG).srec

%.cof: %.elf
	/usr/local/src/binutils-2.13.2/binutils/objcopy --debugging \
        -O coff-avr \
        --change-section-address .data-0x800000 \
        --change-section-address .bss-0x800000 \
        --change-section-address .noinit-0x800000 \
	$< $@

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -j .bootloader -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -j .bootloader -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -j .bootloader -O binary $< $@

%.smallbin: %.elf
	$(OBJCOPY) -j .text -j .data  -O binary $< $@
