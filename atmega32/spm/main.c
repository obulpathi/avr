#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;

	return;
}

int main(void)
{
	init();

	PORTD = ~ PORTD;
	_delay_ms(250);
	PORTD = ~ PORTD;
	_delay_ms(250);

	my_boot();

	PORTD = 0xAA;

	while(1)
	{
		PORTD = ~ PORTD;
		_delay_ms(250);
	}

	return 0;
}
