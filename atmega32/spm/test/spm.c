#include "spm.h"

static void my_boot(void)
{
	uint8_t sreg;

	// save status register
	sreg = SREG;
    
    // erase first page
    boot_page_erase(0);

	// wait for spm to finish tis job
	boot_spm_busy_wait();

	// reenable the rww section
	boot_rww_enable();

	// restore status register
	SREG = sreg;

    return;
}
