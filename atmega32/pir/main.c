#include "main.h"

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

//  write your code here
	while(1)
		if( PINA & 0x80 )
			PORTD = 0xFF;
		else
			PORTD = 0x00;
	
	while(1);	

	return 0;
}
