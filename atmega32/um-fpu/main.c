#include "main.h"

void init(void)
{
	// allow poer to stabilize
	delay_ms(250);

	// port settings
	DDRD = 0xFF;
	PORTD = 0x00;

	return;
}

int main(void)
{
	init();

//  write your code here
	if (fpu_reset() == SYNC_CHAR)
		while(1)
		{
			PORTD = ~PORTD;
			delay_ms(250);
		}

	PORTD = 0xAA;
	while(1);

	return 0;
}
