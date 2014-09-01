#include "main.h"

ISR( __vector_default )
{
	PORTD = 0xA5;
	while(1);
}

ISR( INT5_vect )
{
	PORTD = ~ PORTD;
}

void init(void)
{
	// allow power to stabilize
	_delay_ms(250);

	// port settings
	DDRD = 0xFF;
	PORTD = 0x00;

	// set up interrupt5
	EICRB = ( 1 << ISC51 ) | ( 1 << ISC50 );
	EIMSK = ( 1 << INT5 );

	// enable interrupts
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
