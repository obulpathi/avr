#include <avr/io.h>

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0xFF;

	return;
}

int main(void)
{
	init();

	while(1)
	{
		PORTD = ~PORTD;
	}

	while(1);

	return 0;
}	
