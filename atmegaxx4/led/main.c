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
	init();

	//prog code
	
	while(1)
	{
		PORTD = ~PORTD;
		delay_ms(1000);
	}

	while(1);

	return 0;
}	
