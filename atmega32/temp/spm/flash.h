00001 #ifndef __FLASH_H__
00002 #define __FLASH_H__
00003 /* =============================================================================
00004 
00005     Copyright (c) 2006 Piconomic Design [www.piconomic.co.za]
00006     All rights reserved.
00007     
00008     Redistribution and use in source and binary forms, with or without
00009     modification, are permitted provided that the following conditions are met:
00010     
00011     * Redistributions of source code must retain the above copyright
00012      notice, this list of conditions and the following disclaimer.
00013     
00014     * Redistributions in binary form must reproduce the above copyright
00015      notice, this list of conditions and the following disclaimer in
00016      the documentation and/or other materials provided with the
00017      distribution.
00018     
00019     * Neither the name of the copyright holders nor the names of
00020      contributors may be used to endorse or promote products derived
00021      from this software without specific prior written permission.
00022     
00023     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
00024     AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
00025     IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
00026     ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
00027     LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
00028     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
00029     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
00030     INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
00031     CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
00032     ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
00033     POSSIBILITY OF SUCH DAMAGE.
00034     
00035     Title:          Internal FLASH write routines
00036     Author(s):      Pieter Conradie
00037     Creation Date:  2007-03-31
00038     Revision Info:  $Id$
00039 
00040 ============================================================================= */
00041 
00042 /** 
00043  *  @ingroup AVR_DRIVERS
00044  *  @defgroup FLASH flash.h : Internal FLASH write routines
00045  *
00046  *  This component can clear and write a page of internal FLASH.
00047  *
00048  *  Files: flash.h & flash.c
00049  *
00050  *  @note These routines must always reside in the bootloader section. 
00051  *        If mixing application code and bootloader code, the prefix 
00052  *        BOOTLOADER_SECTION can be used to place these functions in a 
00053  *        section called ".bootloader". See <avr/boot.h>
00054  * 
00055  * @par Example of setting ".bootloader" section address in Makefile:
00056  * @code
00057  * #LDFLAGS += -Wl,--section-start,.bootloader=0x1FF00
00058  * @endcode
00059  *
00060  *  @{
00061  */
00062 
00063 /* _____STANDARD INCLUDES____________________________________________________ */
00064 #include <avr/io.h>
00065 
00066 /* _____PROJECT INCLUDES_____________________________________________________ */
00067 #include "global.h"
00068 
00069 /* _____DEFINITIONS _________________________________________________________ */
00070 /// FLASH Page size in bytes
00071 #define FLASH_PAGE_SIZE  SPM_PAGESIZE
00072 
00073 /// Total number of FLASH pages (application and bootloader section)
00074 #define FLASH_NR_OF_PAGES ((FLASHEND+1)/FLASH_PAGE_SIZE)
00075 
00076 /* _____PUBLIC FUNCTION DECLARATIONS_________________________________________ */
00077 EXTERN PUBLIC void FLASH_vClearPage(uint16 u16Page);
00078 EXTERN PUBLIC void FLASH_vWritePage(uint16 u16Page,uint8* pu8Buffer);
00079 
00080 /**
00081  * @}
00082  */
00083 
00084 #endif
