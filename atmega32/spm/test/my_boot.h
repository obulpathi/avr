#include <inttypes.h>
#include <avr/io.h>
#include <avr/boot.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

void my_boot(void) __attribute__ ((section (".bootloader")));
