#include "main.h"

void init(void)
{	
	DDRD = 0xFF;
	PORTD = 0x00;
	
	TCTR0_Init();
	sei();
	
	return;
}

int main(void)
{
	init();

	while(1)
	{
		PORTD = ~PORTD;
		sleep();
	}
	
	return 0;
}	
