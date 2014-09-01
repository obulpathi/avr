#include "global.h"

void init(void)
{
	// allow power to stabilize
	_delay_ms(250);

	// disable jtag
	MCUCSR = MCUCSR | 0x80;
	MCUCSR = MCUCSR | 0x80;

	// port settings
	DDRD = 0xFF;
	PORTD = 0xFF;

	return;
}

int main(void)
{
	double d1, d2, d3;

	d1 = 1.0;
	d2 = 3.14;
	d3 = d1 * d2;

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
