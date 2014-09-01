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
	PORTD = 0x00;

	// init ds2782
	ds2782_init();

	return;
}

int main(void)
{
	init();

//  write your code here
	while(1);

	return 0;
}
