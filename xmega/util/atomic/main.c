#define F_CPU 2000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>

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
	unsigned char ctr = 0, ctr_copy;

	init();

	// write your code here
	while(1)
	{
		PORTE.OUT = ~PORTE.OUT ;
		_delay_ms(500);
		PORTE.OUT = ~PORTE.OUT;
		_delay_ms(500);
	}

	// never die
	while(1);
	do
	{
    	ATOMIC_BLOCK(ATOMIC_FORCEON)
		{
			ctr_copy = ctr;
		}
	}
	while (ctr_copy != 0);

	return 0;
}
