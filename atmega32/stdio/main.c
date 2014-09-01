#include "global.h"

void init (void)
{
  // allow power to stabilize
  _delay_ms (250);

  // disable jtag
  MCUCSR = MCUCSR | 0x80;
  MCUCSR = MCUCSR | 0x80;

  // port settings
  DDRD = 0xFF;
  PORTD = 0xFF;

  return;
}

#include <stdio.h>

static int uart_putchar (char c, FILE * stream);

static FILE mystdout = FDEV_SETUP_STREAM (uart_putchar, NULL,
					  _FDEV_SETUP_WRITE);

static int uart_putchar (char c, FILE * stream)
{

  if (c == '\n')
    uart_putchar ('\r', stream);
  loop_until_bit_is_set (UCSRA, UDRE);
  UDR = c;
  return 0;
}

int main (void)
{
  init_uart ();
  stdout = &mystdout;
  printf ("Hello, world!\n");

  return 0;
}

int main (void)
{
  init ();

  // write your code here
  while (1)
  {
    PORTD = ~PORTD;
    _delay_ms (250);
  }

  // never die
  while (1);

  return 0;
}
