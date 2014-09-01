#include "main.h"

#include <avr/wdt.h>

void soft_reset(void)
{                           
    wdt_enable(WDTO_15MS);  
	while(1);

	return;
}

void init(void)
{
	// allow power to stabilize
	_delay_ms(250);

	// disable jtag
	MCUCSR = MCUCSR | 0x80;
	MCUCSR = MCUCSR | 0x80;

	// port settings
	DDRD = 0xFF;
	PORTD = 0x00;

	return;
}

int main(void)
{
	init();

	PORTD = ~ PORTD;
	_delay_ms(250);
	PORTD = ~ PORTD;
	_delay_ms(250);

	// do soft reset
	soft_reset();

	while(1);

	return 0;
}
