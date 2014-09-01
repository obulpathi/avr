//------------------------------------------------------------------------------
// Example software to demonstrate the usage of the HDQ communication library.
// The bq26500 battery monitor IC internal registers can be accessed using a
// simple user interface (C-SPY debugger Terminal window, communication to
// host PC via JTAG interface)
//
// A. Dannenberg
// Texas Instruments Inc.
// February 2004
// Built with IAR Embedded Workbench Version: 2.21B
//------------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
//------------------------------------------------------------------------------
#include "msp430x11x1.h"
#include "HDQ.h"
//------------------------------------------------------------------------------
static unsigned int Addr, Data;
static char String[20];
//------------------------------------------------------------------------------
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                     // Stop watchdog timer
  BCSCTL2 |= DCOR;                              // Activate ROSC (Pin 25)
  HDQSetup();                                   // Do basic HDQ setup
  __enable_interrupt();

  while (1)                                     // Repeat forever
  {
    printf("r/w?\r\n");                         // 'r' and 'w' are valid cmds
    scanf("%s", String);
    
    if (String[0] == 'r')                       // Check for 'r' (read)
    {
      printf("addr?\r\n");                      // Get address from user
      scanf("%x", &Addr);
    
      Data = HDQRead(Addr);                     // Do HDQ register read          
    
      if (Data != 0xffff)                       // Timeout occured?
        printf("data: %x\r\n", Data);           // No
      else
        printf("timeout!\r\n");                 // Yes, report error
    }
    else                                        // Must be 'w' (write)
    {
      printf("addr?\r\n");                      // Get address from user
      scanf("%x", &Addr);
      
      printf("data?\r\n");                      // Get data from user
      scanf("%x", &Data);
    
      HDQWrite(Addr, Data);                     // Do HDQ register write
    }
  }
}
