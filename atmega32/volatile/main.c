#include "global.h"
#include "main.h"

volatile unsigned char v_char = 0;

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
	init();

	// write your code here
  while( v_char != 1)
  {
    PORTD = ~PORTD;
    _delay_ms(250);
  }

	// never die
	while(1);

	return 0;
}
