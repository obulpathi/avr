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
	float f1, f2, f3;

	f1 = 1.0;
	f2 = 3.14;
	f3 = f1 * f2;

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
