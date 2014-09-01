#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0xAA;

	return;
}

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0xFF;

	while(1)
	{
		PORTD = ~PORTD;

	}

	return 0;
}	
