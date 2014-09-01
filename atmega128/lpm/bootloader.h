#include <avr/io.h>
#include <avr/boot.h>
#include <inttypes.h>
#include <avr/pgmspace.h>

void boot(void) __attribute__ ((section (".bootloader")));
void boot_program_page (uint32_t page, uint8_t *buf) __attribute__ ((section (".bootloader")));
