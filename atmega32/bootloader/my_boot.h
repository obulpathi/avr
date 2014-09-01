void my_boot(void) __attribute__ ((section (".bootloader")));
void boot_program_page (uint32_t page, uint8_t * buf) __attribute__ ((section (".bootloader")));
