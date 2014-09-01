#define F_CPU 2000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

void init(void)
{
	// allow power to stabilize
	_delay_ms(250);

	// port settings
	PORTE.DIR	 	= 0xFF;
	PORTE.OUT		= 0xA5;

	return;
}

int blink(void)
{
	unsigned char c;

	init();

	// write your code here
	while(1)
	{
		PORTE.OUT = ~PORTE.OUT ;
		_delay_ms(250);
		_delay_ms(250);
		PORTE.OUT = ~PORTE.OUT;
		_delay_ms(250);
		_delay_ms(250);
	}

	// never die
	while(1);

	return 0;
}
