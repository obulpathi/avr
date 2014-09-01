#include "global.h"
#include "main.h"

void init(void)
{
	// allow power to stabilize
	_delay_ms(250);

	// disable jtag
	MCUCSR = MCUCSR | 0x80;
	MCUCSR = MCUCSR | 0x80;

	// port settings
	DDRD = 0xFF;
	PORTD = 0xAA;

	return;
}

int main(void)
{
  register unsigned char counter asm("r3");
	init();

	// write your code here
  while(1)
  {
    PORTD = ~PORTD;
    _delay_ms(250);
  }

	// never die
	while(1);

	return 0;
}
