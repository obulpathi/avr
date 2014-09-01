#include <avr/io.h>
#include "tick.h"

void tick(void)
{
  // swap processes .. 

  // save srec
  srec = SREC;
  // save other state regs
  // save other 32 state regs
  for (count = 0 ; count < 32 ; count++)
    reg_bal[count] = R1 ... R32

  // load srec
  SREC = srec_default
  // load old 32 state regs
  for (count = 0 ; count < 32 ; count++)
    R1 ... R32 = default
  // load pc

  return;
}
