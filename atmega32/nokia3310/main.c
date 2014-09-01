#include <avr/io.h>
#include <avr/wdt.h>

#include "nokia3310.h"
#include "nokia3310.c"

main ()
{

  LcdInit ();

//  LcdLine (1, 1, 30, 30, PIXEL_ON);

  LcdUpdate ();

}
