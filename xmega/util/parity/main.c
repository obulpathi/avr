#define F_CPU 2000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <util/parity.h>
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

int main(void)
{
	unsigned char c;

	init();

	for(c = 0; c < 255; c++)
	{
		PORTE.OUT = ~parity_even_bit(c);
		_delay_ms(1000);
	}

	// write your code here
	while(1)
	{
		PORTE.OUT = ~PORTE.OUT ;
		_delay_ms(500);
		PORTE.OUT = ~PORTE.OUT;
		_delay_ms(500);
	}

	return 0;
}
