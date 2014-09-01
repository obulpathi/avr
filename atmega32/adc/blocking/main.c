#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0xFF;
	
	// initialize adc
	adc_init();

	return;
}

int main(void)
{
	init();

	// code goes here ...
	
	while(1)
	{
		PORTD = adc_read();
		delay_ms(250);
	}

	while(1);

	return 0;
}
