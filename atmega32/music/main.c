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

	while(1)
	{
		PORTD = ~PORTD;
		delay_ms(10);
	}

	while(1);

	return 0;
}	
