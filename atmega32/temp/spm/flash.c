       /* _____STANDARD INCLUDES____________________________________________________ */
i      #include <avr/boot.h>
00042 
00043 /* _____PROJECT INCLUDES_____________________________________________________ */
00044 #include "flash.h"
00045 
00046 /* _____PUBLIC FUNCTIONS_____________________________________________________ */
00047 /**
00048  *  Function to clear a page.
00049  *
00050  *  @param u16Page  0 to (#FLASH_NR_OF_PAGES - 1)
00051  * 
00052  */
00053 BOOTLOADER_SECTION PUBLIC void FLASH_vClearPage(uint16 u16Page)
00054 {
00055     // Calculate 32-bit address from specified page
00056     uint32  u32Address = ((uint32)u16Page)<<8;
00057 
00058     // Save status of global interrupts
00059     uint8   u8Sreg = SREG;
00060 
00061     boot_page_erase(u32Address);
00062 
00063     // Wait until SPM command has finished
00064     boot_spm_busy_wait();
00065 
00066     // Re-enable RWW-section
00067     boot_rww_enable();
00068 
00069     // Restore status of global interrupts
00070     SREG = u8Sreg;
00071 }
00072 
00073 /**
00074  *  Function to write a page.
00075  * 
00076  *  @param u16Page      0 to (#FLASH_NR_OF_PAGES - 1)
00077  *  @param pu8Buffer    Pointer to buffer containing data to write
00078  * 
00079  */
00080 BOOTLOADER_SECTION PUBLIC void FLASH_vWritePage(uint16 u16Page, uint8* pu8Buffer)
00081 {
00082     uint16  i;
00083 
00084     // Calculate 32-bit address from specified page
00085     uint32  u32Address = ((uint32)u16Page)<<8;
00086 
00087     // Cast 8-bit pointer to 16-bit pointer
00088     uint16* pu16Data   = (uint16*)pu8Buffer;
00089 
00090     // Save status of global interrupts
00091     uint8   u8Sreg = SREG;
00092 
00093     // Clear the page first
00094     FLASH_vClearPage(u16Page);
00095 
00096     // Fill write buffer with 16-bit data
00097     for(i=0; i<SPM_PAGESIZE; i+=2)
00098     {
00099         boot_page_fill(u32Address+i,*pu16Data++);
00100     }
00101 
00102     // Commit buffer to flash page
00103     boot_page_write(u32Address);   
00104 
00105     // Wait until SPM command has finished
00106     boot_spm_busy_wait();
00107 
00108     // Re-enable RWW-section
00109     boot_rww_enable();
00110 
00111     // Restore status of global interrupts
00112     SREG = u8Sreg;
00113 }
00114 
00115 /* _____LOG__________________________________________________________________ */
00116 /*
00117 
00118  2007-03-31 : PJC
00119  - First release
00120    
00121 */
