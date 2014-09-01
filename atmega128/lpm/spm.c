#include "spm.h"

int page_erase( uint32_t page)
{
        uint8_t sreg;
	
	// save status register
        sreg = SREG;

	// erase the page
        boot_page_erase (page);
	// wait until the memory is erased.
        boot_spm_busy_wait ();
	
        // Reenable RWW-section again. We need this if we want to jump back
        // to the application after bootloading.
        boot_rww_enable ();
	
	// restore status register
        SREG = sreg;

	return 0;
}

void boot_program_page (uint32_t page, uint8_t *buf)
{
        uint16_t i, w;
        uint8_t sreg;

	// save status register
        sreg = SREG;
	
        // Disable interrupts.
        cli();
	
	// wait for eeprom write completion
        eeprom_busy_wait ();
	
	// erase the page
        boot_page_erase (page);
	
	// wait until the memory is erased.
        boot_spm_busy_wait ();

	// fill up the buffer
        for ( i = 0; i < SPM_PAGESIZE; i = i + 2)
        {
		// Set up little-endian word.

		w = *buf++;
		w += (*buf++) << 8;
        
		boot_page_fill (page + i, w);
        }
	
	// store buffer in flash page.
        boot_page_write (page);
	
	// wait until the memory is written.
        boot_spm_busy_wait(); 

        // Reenable RWW-section again. We need this if we want to jump back
        // to the application after bootloading.
        boot_rww_enable ();

        // restore the status register
        SREG = sreg;
	
	// reenable the interrupts ... if they are enabled.
	sei();

	return;
}
