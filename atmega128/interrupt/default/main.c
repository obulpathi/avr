#include "main.h"

// default interrupt handler
ISR(__vector_default)
{
	PORTD = ~ PORTD;
}

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;

	tctr0_init();
	sei();

	return;
}

int main(void)
{
	init();

	//prog code

	while(1);

	return 0;
}	
