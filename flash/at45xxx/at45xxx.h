// organige the fle properly ... its too messy ...

// general dataat45xxx definitions

#define BUFFER1 0
#define BUFFER2 1

// definitions for AT45DB321

#define BUFFER_SIZE  528
#define NUM_PAGES   8192

// command definitions

// read commands

// program and erase commands

// other commands

#define FLASH_BUSY 		0x00
#define FLASH_MASK_BUSY		0x80
#define FLASH_DONTCARE		0x00
#define FLASH_TRUE		0x00
#define FLASH_SR_READ		0xD7
#define FLASH_MM_PAGE_READ	0xD2
#define FLASH_PW_TH_BUFFER1	0x82
#define FLASH_MM_PAGE_BUF_COM	0x60
#define FLASH_PAGE_START	0x00

extern unsigned char data[528];

unsigned char at45xxx_status_read(void);
int at45xxx_device_ready(void);
int at45xxx_page_read(unsigned int address);
int at45xxx_page_write(unsigned int address);


/* Properly redefine the following headers ... 
// Define Data flash commands. For further details, see datasheet.
// Note!! All possible commands are not implemented yet.

#define BLOCK_ERASE         0x50
#define PAGE_ERASE          0x81
#define MEM_PAGE_READ       0x52
#define READ_BUFFER1        0x54
#define READ_BUFFER2        0x56
#define MEM_TO_BUFFER1      0x53
#define MEM_TO_BUFFER2      0x55
#define MEM_COMP_BUFFER1    0x60
#define MEM_COMP_BUFFER2    0x61
#define WRITE_BUFFER1       0x84
#define WRITE_BUFFER2       0x87
#define BUFFER1_TO_MEM_WE   0x83
#define BUFFER2_TO_MEM_WE   0x86
#define BUFFER1_TO_MEM_NE   0x88
#define BUFFER2_TO_MEM_NE   0x89
#define MEM_WR_TH_BUFFER1   0x82
#define MEM_WR_TH_BUFFER2   0x85
#define AUTO_RW_TH_BUFFER1  0x58
#define AUTO_RW_TH_BUFFER2  0x59
#define READ_STATUS         0x57
*/
