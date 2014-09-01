#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0xFF;

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
		PORTD = ~ PORTD;
		delay_sec();
	}

	while(1);

	return 0;
}
