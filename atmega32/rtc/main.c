#include "main.h"

void init(void)
{
	// allow power to stabilize
	_delay_ms(250);

	// port settings
	DDRD = 0xFF;
	PORTD = 0x00;

	rtc_init();

	sei();

	return;
}

int main(void)
{
	init();

//  write your code here
	while(1);

	return 0;
}
