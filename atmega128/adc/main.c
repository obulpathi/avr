#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;
	
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
		delay_ms(1000);
	}

	while(1);

	return 0;
}
