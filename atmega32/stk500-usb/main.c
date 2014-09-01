#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0xAA;

	return;
}

int main(void)
{
	init();

	//prog code
	while(1)
	{
		PORTD = ~PORTD;
		_delay_ms(1000);
	}

	while(1);

	return 0;
}	
