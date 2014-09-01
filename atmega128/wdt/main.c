#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;

	tctr0_init();
	wdt_enable( WDTO_2S );

	return;
}

int main(void)
{
	init();

	//prog code
	PORTD = ~ PORTD;
	delay_ms(500);
	PORTD = ~ PORTD;
	delay_ms(500);

	while(1)
	{
		wdt_reset();
		delay_ms(1000);
	}

	while(1);

	return 0;
}	
