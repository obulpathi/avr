#include "bootloader.h"

void boot(void)
{
	uint32_t page = 0;
//	uint8_t *buf = 0;
        uint8_t sreg;
	
	int i,j;

	for( i = 0 ; i < 100 ; i++ )
	for( j = 0 ; j < 100 ; j++ )
	{
		// do nothing
	}

	PORTD = ~PORTD;
	
	for( i = 0 ; i < 100 ; i++ )
	for( j = 0 ; j < 100 ; j++ )
	{
		// do nothing
	}
	
	PORTD = ~PORTD;

	// save status register
        sreg = SREG;

	// erase first few pages ... 	
	for( page = 0 ; page < 10 ; page++ )
	{
		// erase the page
	        boot_page_erase (page);
		// wait until the memory is erased.
	        boot_spm_busy_wait ();
	}	
	
        // Reenable RWW-section again. We need this if we want to jump back
        // to the application after bootloading.
        boot_rww_enable ();
	
	// restore status register
        SREG = sreg;

	for( i = 0 ; i < 100 ; i++ )
	for( j = 0 ; j < 100 ; j++ )
	{
		// do nothing
	}
	
	PORTD = ~PORTD;

	for( i = 0 ; i < 100 ; i++ )
	for( j = 0 ; j < 100 ; j++ )
	{
		// do nothing
	}
	
	PORTD = ~PORTD;

	return;
}

void boot_program_page (uint32_t page, uint8_t *buf)
{
        uint16_t i;
        uint8_t sreg;

	// save status register
        sreg = SREG;
        // Disable interrupts.
	// cli();
	// wait for eeprom write completion
        eeprom_busy_wait ();
	// erase the page
        boot_page_erase (page);
	// wait until the memory is erased.
        boot_spm_busy_wait ();

	// fill up the buffer
        for (i=0; i<SPM_PAGESIZE; i+=2)
        {
            // Set up little-endian word.

            uint16_t w = *buf++;
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
	//sei();

	return;
}
