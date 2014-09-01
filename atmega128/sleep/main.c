#include "main.h"

void
init (void)
{
  // set up interrupt5
  EICRB = (1 << ISC51) | (1 << ISC50);
  EIMSK = (1 << INT5);

  // enable interrupt
  sei ();

  return;
}

int
main (void)
{
  init ();

  // enter in to sleep mode
  sleep ();

  // good morning ... 
  while (1)
    {
      PORTD = ~PORTD;
      _delay_ms (250);
    }

  return 0;
}
