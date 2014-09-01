#include "global.h"

void init(void)
{
	// allow power to stabilize
	//_delay_ms(250);

	// disable jtag
	//MCUCSR = MCUCSR | 0x80;
	// MCUCSR = MCUCSR | 0x80;

	// port settings
	DDRB = 0xFF;
	PORTB = 0x00;

	return;
}

int main(void)
{
	init();

	// write your code here
	while(1)
	{
		PORTB = ~PORTB;
		_delay_ms(250);
	}
	// never die
	while(1);

	return 0;
}
