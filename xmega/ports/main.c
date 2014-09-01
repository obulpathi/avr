#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

void init(void)
{
	// allow power to stabilize
	_delay_ms(250);

	// port settings
	//PORTE_DIRSET 	= 0x0F;
	PORTE_DIR 	= 0x0F;
	PORTE_OUT	= 0x00;

	return;
}

int main(void)
{
	init();

	// write your code here
	while(1)
	{
		PORTE_OUT = 0x0F;
		_delay_ms(250);
		_delay_ms(250);
		PORTE_OUT = 0x00;
		_delay_ms(250);
		_delay_ms(250);
	}

	// never die
	while(1);

	return 0;
}
