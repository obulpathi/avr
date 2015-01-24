#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

void init(void)
{
	// allow power to stabilize
	_delay_ms(250);

	// port settings
	DDRD = 0xFF;
	PORTD = 0xFF;

	return;
}

int main(void)
{
    int count = 0;
	init();

	// write your code here
	while(count < 10)
	{
		PORTD = ~PORTD;
		_delay_ms(5000);
		PORTD = ~PORTD;
		_delay_ms(10);
        count++;
	}

    PORTD = 0x00;
	// never die
	while(1);

	return 0;
}
