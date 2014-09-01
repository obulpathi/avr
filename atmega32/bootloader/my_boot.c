#include <avr/io.h>
#include <avr/boot.h>
#include <avr/interrupt.h>
#include "my_boot.h"

void my_boot(void)
{
	uint32_t page = 0;
	uint8_t buffer[SPM_PAGESIZE] = {0x44};

	boot_program_page (page, buffer);

	return;
}

void boot_program_page (uint32_t page, uint8_t * buf)
{
  uint16_t i;
  uint8_t sreg;

  // Disable interrupts.

  sreg = SREG;

  boot_page_erase (page);
  boot_spm_busy_wait ();	// Wait until the memory is erased.

  for (i = 0; i < SPM_PAGESIZE; i += 2)
  {
    // Set up little-endian word.
    uint16_t w = *buf++;
    w += (*buf++) << 8;
    boot_page_fill (page + i, w);
  }

  boot_page_write (page);	// Store buffer in flash page.
  boot_spm_busy_wait ();	// Wait until the memory is written.

  // Reenable RWW-section again. We need this if we want to jump back
  // to the application after bootloading.
  boot_rww_enable ();

  SREG = sreg;
}
