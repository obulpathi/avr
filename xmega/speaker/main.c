#define F_CPU 2000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

void init(void)
{
	// allow power to stabilize
	_delay_ms(250);

	// port settings
	PORTB.DIR	 	= 0xFF;
	PORTB.OUT		= 0x00;

	PORTQ.DIR	 	= 0x08;
	PORTQ.OUT	 	= 0x08;

	return;
}

int main(void)
{
	int i ;

	init();

	// write your code here
	while(1)
	{
		for(i = 0; i < 255; i++)
		{
			PORTB.OUT = i;
			_delay_ms(1);
		}
	}

	// never die
	while(1);

	return 0;
}
