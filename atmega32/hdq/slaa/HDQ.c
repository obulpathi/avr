//------------------------------------------------------------------------------
// Library to implement the HDQ single wire interface on MSP430 devices using
// the P1.1 / TA0 pin. Note that an external pull-up resistor is necessary.
//
// A. Dannenberg
// Texas Instruments Inc.
// February 2004
// Built with IAR Embedded Workbench Version: 2.21B
//------------------------------------------------------------------------------
// Include the following line to toggle P1.0 on Timer_A ISR entry/exit
// for use as scope trigger or for measuring ISR execution time.
//#define DEBUG_HDQ
//------------------------------------------------------------------------------
#include "msp430x11x1.h"
#include "HDQ.h"
//------------------------------------------------------------------------------
// Local definitions
enum
{
  imWrite,
  imWriteE,
  imRead,
  imReadE,
  imDelay
};

// Local variables
static unsigned char ISRMode;
static unsigned char Xfer;
static unsigned char BitCnt;
static unsigned int Ticks;
//------------------------------------------------------------------------------
// void HDQBreak(void)
//
// Local function to send a HDQ break-transmission for providing a safe
// communication start.
//------------------------------------------------------------------------------
static void HDQBreak(void)
{
  TACCR0 = TAR + tBreak * 2;                    // Use double break time
  TACCTL0 = OUTMOD_0 + CCIE;                    // Reset OUT0, enable int
  ISRMode = imDelay;                            // Set ISR mode
  LPM0;                                         // Wait for ISR completion
  TACCR0 += tBR;                                // Break recovery time
  TACCTL0 = OUTMOD_0 + OUT + CCIE;              // Set OUT0, enable int
  LPM0;                                         // Wait for ISR completion
}
//------------------------------------------------------------------------------
// void HDQBasicWrite(unsigned char Data)
//
// Local function to output the 8-bit variable 'Data' to the Timer_A.OUT0
// output using the HDQ protocol.
//------------------------------------------------------------------------------
static void HDQBasicWrite(unsigned char Data)
{
  Xfer = Data;
  TACCTL0 = OUTMOD_0;                           // Reset OUT0

  TACCR0 = TAR;
  Ticks = TACCR0;                               // Bit start time stamp

  if (Xfer & 0x01)                              // LSB == 1?
    TACCR0 += tHW1;                             // Output '1'
  else
    TACCR0 += tHW0;                             // Output '0'
  
  TACCTL0 = OUTMOD_4 + CCIE;                    // Toggle OUT0 on EQU0, en. int
  BitCnt = 8;                                   // 8 bits to transfer
  ISRMode = imWrite;                            // Set ISR mode
  LPM0;                                         // Wait for ISR completion
}
//------------------------------------------------------------------------------
// void HDQSetup(void)
//
// Exported function to initialize the Timer_A port pin (TA0) that
// is used for HDQ communication
//------------------------------------------------------------------------------
void HDQSetup(void)
{
  P1DIR &= ~0x02;                               // P1.1 as input
  P1SEL |= 0x02;                                // Select TA0 function
  
#ifdef DEBUG_HDQ
  P1OUT &= ~0x01;                               // P1.0 is scope trigger
  P1DIR |= 0x01;
#endif  
}
//------------------------------------------------------------------------------
// void HDQWrite(unsigned char Addr, unsigned char Data)
//
// Exported function to write the 8-bit word 'Data' into the 8-bit register
// 'Addr' of the attached HDQ-enabled device.
//------------------------------------------------------------------------------
void HDQWrite(unsigned char Addr, unsigned char Data)
{
  TACTL = TASSEL_2 + MC_2;                      // SMCLK, continuous mode
  P1DIR |= 0x02;                                // P1.1 as in output
  HDQBreak();                                   // Send HDQ break
  HDQBasicWrite(Addr | 0x80);                   // Write to Addr
  
  TACCR0 += tCYCH;                              // Insert delay
  TACCTL0 = OUTMOD_0 + OUT + CCIE;              // Set OUT0, enable int
  ISRMode = imDelay;                            // Set ISR mode
  LPM0;                                         // Wait for ISR completion  
  
  HDQBasicWrite(Data);                          // Write Data
  P1DIR &= ~0x02;                               // P1.1 as in input
  TACTL = 0;                                    // Stop Timer_A
}
//------------------------------------------------------------------------------
// unsigned int HDQRead(unsigned char Addr)
//
// Exported function to read an 8-bit value from the address 'Addr' out of
// the attached HDQ-enabled device. The function will return 0xffff in the
// case of a communication failure (Time-Out).
//------------------------------------------------------------------------------
unsigned int HDQRead(unsigned char Addr)
{
  TACTL = TASSEL_2 + MC_2;                      // SMCLK, continuous mode
  P1DIR |= 0x02;                                // P1.1 as in output
  HDQBreak();
  HDQBasicWrite(Addr);
  P1DIR &= ~0x02;                               // P1.1 as in input

  BitCnt = 8;                                   // 8 bits to transfer
  ISRMode = imRead;                             // Set ISR mode

  TACCTL0 = CM_2 + CCIS_0 + SCCI + CAP + CCIE;  // Capt. falling edge of P1.1
  TACCR1 = TAR + tTO;                           // Time-Out
  TACCTL1 = CCIE;                               // Enable Time-Out

  LPM0;                                         // Wait for ISR completion

  TACTL = 0;                                    // Stop Timer_A

  if (BitCnt)                                   // All bits received?
    return 0xffff;                              // Error condition (Time-Out)
  else
    return Xfer;                                // OK
}
//------------------------------------------------------------------------------
// void Timer_A0_ISR(void)
//
// Timer_A.CCR0 interrupt service function
//------------------------------------------------------------------------------
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A0_ISR(void)
{
#ifdef DEBUG_HDQ
  P1OUT ^= 0x01;                                // Toggle scope trigger
#endif

  switch (ISRMode)
  {
    case imWrite :
      if (--BitCnt)                             // Decr and check
      {
        TACCR0 = Ticks + tCYCH;                 // Time to cycle completion
        ISRMode = imWriteE;                     // Switch ISR mode
      }
      else
      {
        TACCTL0 = OUTMOD_0 + OUT;               // Set OUT0, disable int
        __bic_SR_register_on_exit(LPM0_bits);   // Return active
      }
      break;
    case imWriteE :
      Ticks = TACCR0;                           // Bit start time stamp
        
      if ((Xfer >>= 1) & 0x01)                  // Process next bit
        TACCR0 += tHW1;                         // Output '1'
      else
        TACCR0 += tHW0;                         // Output '0'
        
      ISRMode = imWrite;                        // Switch ISR mode
      break;
    case imRead :
      TACCTL1 = 0;                              // Disable Time-Out
      TACCR0 += (tDW0 + tDW1) / 2;              // Time to middle of bit
      TACCTL0 &= ~CAP;                          // Compare mode
      ISRMode = imReadE;                        // Switch ISR mode
      break;
    case imReadE :
      Xfer >>= 1;                               // Process next bit
      if (TACCTL0 & SCCI)                       // Check Timer_A latch
        Xfer |= 0x80;
      if (--BitCnt)                             // Decr and check
      {
        TACCTL0 |= CAP;                         // Capture mode
        TACCR1 = TAR + tTO;                     // Time-Out
        TACCTL1 = CCIE;                         // Enable Time-Out
        ISRMode = imRead;                       // Switch ISR mode     
      }
      else
      {
        TACCTL0 = OUTMOD_0 + OUT;               // Set OUT0, disable int
        __bic_SR_register_on_exit(LPM0_bits);   // Return active
      }
      break;
    case imDelay :
      TACCTL0 &= ~CCIFG;                        // Disable int
      __bic_SR_register_on_exit(LPM0_bits);     // Return active
      break;
  }

#ifdef DEBUG_HDQ
  P1OUT ^= 0x01;                                // Toggle scope trigger
#endif
}
//------------------------------------------------------------------------------
// void Timer_A1_ISR(void)
//
// Timer_A.CCR1-2, TA interrupt service function
//------------------------------------------------------------------------------
#pragma vector = TIMERA1_VECTOR
__interrupt void Timer_A1_ISR(void)
{
  if (TAIV == 0x02)                             // Timer_A.CCR1
  {
    TACCTL0 = 0;                                // Disable receiption
    TACCTL1 = 0;                                // Disable Time-Out
    __bic_SR_register_on_exit(LPM0_bits);       // Return active
  }
}
