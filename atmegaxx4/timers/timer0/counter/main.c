#include "main.h"

void init(void)
{
	// port init
	DDRD = 0xFF;
	PORTD = 0x00;
	
	//counter0 init
	tctr0_init();

	return;
}

int main(void)
{
	// init
	init();

	// code goes here
	while(1)
		PORTD = TCNT0;

	while(1);
	
	return 0;
}
