#define F_CPU 2000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define nop(); asm("nop");

void init(void)
{
	// allow power to stabilize
	_delay_ms(250);

	// port settings
	PORTE.DIR	 	= 0xFF;
	PORTE.OUT		= 0xA5;

	nop();

	return;
}

int main(void)
{
	unsigned char c;

	init();

	// write your code here
	while(1)
	{
		PORTE.OUT = 0xA5 ;
		_delay_ms(50);
		PORTE.OUT = 0xFF ;
		_delay_ms(450);
		PORTE.OUT = 0x5A ;
		_delay_ms(50);
		PORTE.OUT = 0xFF ;
		_delay_ms(450);
	}

	// never die
	while(1);

	return 0;
}
