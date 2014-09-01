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

	_delay_ms(100);

	sleep();
	
	while(1)
	{
		PORTD = ~PORTD;
		_delay_ms(100);
	}
	
	return 0;
}	
