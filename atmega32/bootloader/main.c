#define F_CPU 1000000

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/boot.h>
#include <util/delay.h>

#include "my_boot.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;

	return;
}

int main(void)
{
	init();

	//prog code
	my_boot();

	while(1)
	{
		PORTD = ~PORTD;
		_delay_ms(250);
		PORTD = ~PORTD;
		_delay_ms(250);
	}

	// never die
	while(1);

	return 0;
}	
