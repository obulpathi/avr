#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;

	tctr0_init();

	return;
}

int main(void)
{
	init();

	//prog code

	srand(100);

	while(1)
	{
			PORTD = rand();
			delay_ms(1000);
	}

	while(1);

	return 0;
}	
