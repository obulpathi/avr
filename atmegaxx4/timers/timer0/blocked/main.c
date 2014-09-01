#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0xFF;

	tctr0_init();

	return;
}

int main(void)
{
	int i;

	init();

	// code goes here

	while(1)
	{
		PORTD = ~ PORTD;
		delay_ms(1000);
	}

	while(1);

	return 0;
}
