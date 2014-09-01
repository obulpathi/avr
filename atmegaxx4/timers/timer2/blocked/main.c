#include "main.h"

void init(void)
{
	DDRB = 0xFF;
	PORTB = 0xFF;

	tctr2_init();

	return;
}

int main(void)
{
	int i;

	init();

	// code goes here

	while(1)
	{
		PORTB = ~ PORTB;
		delay_ms(1000);
	}

	while(1);

	return 0;
}
