#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0xFF;

	// init timer
	tctr2_init();

	return;
}

int main(void)
{
	init();

	//prog code
	while(1)
	{
		PORTD = ~ PORTD;
		delay_ms(1000);
	}

	while(1);

	return 0;
}	
