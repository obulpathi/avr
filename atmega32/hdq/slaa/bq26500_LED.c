//------------------------------------------------------------------------------
// Example software to demonstrate the usage of the HDQ communication library.
// The temperature from an bq26500 gas-gauge IC that is connected via HDQ is
// read out periodically and temperature changes are indicated by operating
// the GPIO pin of the bq26500 device. See application report for more details.
//
// A. Dannenberg
// Texas Instruments Inc.
// February 2004
// Built with IAR Embedded Workbench Version: 2.21B
//------------------------------------------------------------------------------
#include <stdlib.h>
#include "msp430x11x1.h"
#include "HDQ.h"
//------------------------------------------------------------------------------
// bq26500 Registers
#define MODE                  0x01
#define TEMPL                 0x06
#define TEMPH                 0x07

// bq26500 Bit Definitions
#define GPSTAT                0x40

// Global Vars
static unsigned int Counter;

// Function Prototypes
static void Delay(unsigned int Counts);
//------------------------------------------------------------------------------
void main(void)
{
  unsigned int FirstTEMPL;
  unsigned int Data;

  WDTCTL = WDTPW + WDTTMSEL;                    // WDT as interval timer,
                                                // f = SMCLK / 32768
  BCSCTL2 |= DCOR;                              // Activate ROSC (Pin 2.5)
  HDQSetup();                                   // Do basic HDQ setup
  __enable_interrupt();

  // Give the bq26500 time to do its first temperature measurement
  // for the case it is powered on together with the MSP430
  Delay(3 * 60);                                // Wait 3s

  // Take initial temperature measurement, wait for first
  // successful readout
  while ((FirstTEMPL = HDQRead(TEMPL)) == 0xffff);

  while (1)
  {
    Delay(1 * 60);                              // Wait 1s
    
    if ((Data = HDQRead(TEMPL)) == 0xffff)      // Read data
      continue;                                 // Timeout, read again

    if (abs(Data - FirstTEMPL) >= 4)            // Delta >= 1K?
      HDQWrite(MODE, 0x00);                     // Turn GPIO-LED on
    else
      HDQWrite(MODE, GPSTAT);                   // Turn GPIO-LED off
  }
}
//------------------------------------------------------------------------------
// void Delay(unsigned int Counts)
//
// Delays the program flow by Counts * 1/60s (with SMCLK = 2MHz) using the
// WDT in interval mode. Power is saved by using LPM0 instead of a simple
// for(;;) loop.
//------------------------------------------------------------------------------
static void Delay(unsigned int Counts)
{
  Counter = Counts;                             // Set global var
  IE1 |= WDTIE;                                 // Enable WDT int
  __bis_SR_register(LPM0_bits);                 // Enter LPM0
  __no_operation();
  IE1 &= ~WDTIE;                                // Disable WDT int
}
//------------------------------------------------------------------------------
// void WDT_ISR(void)
//
// Watchdog-Timer Interrupt Service Function. Called every 1/60s
// with SMCLK = 2MHz. Returns active if Counter = 0.
//------------------------------------------------------------------------------
#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR(void)
{
  if (!--Counter)                               // Decrement and check
    __bic_SR_register_on_exit(LPM0_bits);       // Return active
}
