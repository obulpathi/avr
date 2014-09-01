#include <avr/io.h>
#include <avr/boot.h>
#include <inttypes.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

void boot_erase_page (uint32_t page) __attribute__ ((section (".bootloader")));
void boot_program_page (uint32_t page, uint8_t *buf) __attribute__ ((section (".bootloader")));
