#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0xAA;

	tctr0_init();

	return;
}

int main(void)
{
	int i;

	init();

	while(1)
	{
		PORTD = ~PORTD;
		delay_ms(1000);
	}

	// code goes here

	return 0;
}
