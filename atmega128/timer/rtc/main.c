#include "main.h"

void init(void)
{
	// allow poer to stabilize
	_delay_ms(250);

	// port settings
	DDRD = 0xFF;
	PORTD = 0x00;

	return;
}

int main(void)
{
	init();

//  write your code here
	while(1);

	return 0;
}
