/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
*
* \brief  XMEGA Self-programming driver example source.
*
*      This file contains an example application that demonstrates the Self-programming
*      driver. It shows how to program different values into the Application Table
*      Section.
*
* \par Application note:
*      AVR1316: XMEGA Self-programming
*
* \par Documentation
*      For comprehensive code documentation, supported compilers, compiler
*      settings and supported devices see readme.html
*
* \author
*      Atmel Corporation: http://www.atmel.com \n
*      Support email: avr@atmel.com
*
* $Revision: 1691 $
* $Date: 2008-07-29 13:25:40 +0200 (ti, 29 jul 2008) $  \n
*
* Copyright (c) 2008, Atmel Corporation All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.
*
* 3. The name of ATMEL may not be used to endorse or promote products derived
* from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
* SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************/

#include "sp_driver.h"

/*! Macro defined to read from the Application Table Section. */
//#define appTable(__tableIndex)	SP_ReadByte(APPTABLE_SECTION_START + __tableIndex)
#define appTable(__tableIndex)	SP_ReadByte(__tableIndex)

/* Buffers for testing Load/Read Flash Page. */
uint8_t WriteBuffer[FLASH_PAGE_SIZE];
uint8_t ReadBuffer[FLASH_PAGE_SIZE];
uint8_t sleepCtr;
uint8_t statusStore;
uint8_t pmicStore;
uint8_t globalInt;
uint8_t spmintStore;

/* Test message to write to the signature row. */
uint8_t message[32] = {"/*Flash Work around Completed */"};


/*! \brief Example to show how to read and write to the flash.
*/
ISR(NVM_SPM_vect)
{
	/* Disable the SPM interrupt */
	NVM.INTCTRL = (NVM.INTCTRL & ~NVM_SPMLVL_gm);
	/* Restore sleep settings */
	SLEEP.CTRL = sleepCtr;
	/* Restore PMIC status and control registers */
	PMIC.STATUS = statusStore;
	PMIC.CTRL = pmicStore;
	/* Restore SPM interruptsettings */
	NVM.INTCTRL = spmintStore;
	/* Restore global interrupt settings */
	SREG = globalInt;
	return;
}
void PMIC_SetVectorLocationToBoot( void )
{
	uint8_t temp = PMIC.CTRL | PMIC_IVSEL_bm;
	CCP = CCP_IOREG_gc;
	PMIC.CTRL = temp;
}
void PMIC_SetVectorLocationToApplication( void )
{
	uint8_t temp = PMIC.CTRL & ~PMIC_IVSEL_bm;
	CCP = CCP_IOREG_gc;
	PMIC.CTRL = temp;
}
void Prepare_to_Sleep( void )
{
	sleepCtr = SLEEP.CTRL;
	/* Set sleep mode to IDLE */
	SLEEP.CTRL =  0x00; 
	/* Save the PMIC Status and control registers */
	statusStore = PMIC.STATUS;								
	pmicStore = PMIC.CTRL;		
	
	/* Enable only the highest level of interrupts */									
	PMIC.CTRL = (PMIC.CTRL & ~PMIC_HILVLEN_bm) | PMIC_HILVLEN_bm;
	/* Save SREG for later use */
	globalInt = SREG;
	/* Enable global interrupts */
	sei();
	
	/* Save SPM interrupt settings for later */ 
	spmintStore = NVM.INTCTRL;
}
void EraseApplicationPage(uint16_t address)
{
	/*Set the correct settings and store critical registers before NVM-workaround*/
	Prepare_to_Sleep();
	/*Assembly "function" to preform page erase*/
	SP_EraseApplicationPage(address);
}

void EraseWriteApplicationPage(uint16_t address)
{
	/*Set the correct settings and store critical registers before NVM-workaround*/
	Prepare_to_Sleep(); 
	/*Assembly "function" to preform page erase-write*/
	SP_EraseWriteApplicationPage(address);
}
int main(void)
{
	/*CCP = CCP_IOREG_gc;
	PMIC.CTRL = (PMIC.CTRL & ~PMIC_HILVLEN_bm) | PMIC_HILVLEN_bm | PMIC_IVSEL_bm;
	NVM.INTCTRL = NVM_SPMLVL0_bm | NVM_SPMLVL1_bm;
	
	sei();*/
	/* Assume success until proven otherwise. */
	bool success = true;
	PMIC_SetVectorLocationToBoot();
	for (uint8_t j = 0; j < 6; j++) {
		// Erase page with address j. 
		EraseApplicationPage(j*FLASH_PAGE_SIZE);
		
		// Load 100 bytes. 
		
		for (uint16_t i = 0; i < FLASH_PAGE_SIZE; i += 2) {
			uint8_t lowByte = i;
			uint8_t highByte = i+1;
			
			SP_LoadFlashWord(i, ((uint16_t) highByte << 8) | lowByte);
			SP_WaitForSPM();
		}
		
		/* Perform erase-page write. */ 
		EraseWriteApplicationPage(j*FLASH_PAGE_SIZE);
		
		/* Assume success until proven otherwise. */
	}
	
	/* Allow for breakpoint to check the value of "success". */
	PORTE.DIR = 0xFF;
	if (success) {
		PORTE.OUT = 0xFF;
		while(true){
			PORTE.OUT = ~PORTD.OUT;
			_delay_ms(500);
			nop();
		}
	} else {
		PORTE.OUT = 0xAA;
		while(true){
			PORTE.OUT = ~PORTD.OUT;
			_delay_ms(500);

			nop();
		}
	}
	
	
	
}


