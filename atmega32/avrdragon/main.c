#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0xAA;

	MCUCSR = MCUCSR | 0x80;
	MCUCSR = MCUCSR | 0x80;

	tctr0_init();

	return;
}

int main(void)
{
	init();

	//prog code

	while(1)
	{
		delay_ms(1000);
		PORTD = ~PORTD;
	}

	while(1);

	return 0;
}	
