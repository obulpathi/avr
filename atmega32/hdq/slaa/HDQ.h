#ifndef HDQ_H
#define HDQ_H
//------------------------------------------------------------------------------
// Define the SMCLK frequency
//------------------------------------------------------------------------------
#define ClkFreq     2000000u                    // Timer clock frequency (Hz)
//------------------------------------------------------------------------------
// Define HDQ Protocol Related Timing Constants
//------------------------------------------------------------------------------
#define tBreak      (190 * ClkFreq / 1000000)   // HDQ Break Time (190us)
#define tBR         (40 * ClkFreq / 1000000)    // HDQ Break Recovery Time (40us)
#define tHW1        (40 * ClkFreq / 1000000)    // Host sends 1 time (40us)
#define tHW0        (123 * ClkFreq / 1000000)   // Host sends 0 time (123us)
#define tCYCH       (230 * ClkFreq / 1000000)   // Host bit window timing (230us)
#define tDW1        (41 * ClkFreq / 1000000)    // Slave sends 1 time (41us)
#define tDW0        (113 * ClkFreq / 1000000)   // Slave sends 0 time (113us)
#define tTO         (500 * ClkFreq / 1000000)   // Time-Out Bit Receiption (500us)
//------------------------------------------------------------------------------
// Exported functions (only for use with C)
//------------------------------------------------------------------------------
#ifdef __STDC__
extern void HDQSetup(void);
extern void HDQWrite(unsigned char Addr, unsigned char Data);
extern unsigned int HDQRead(unsigned char Addr);
#endif
//------------------------------------------------------------------------------
#endif

