#include "main.h"

ISR( TIMER2_OVF_vect )
{
	rtc_tick();

	PORTD = ~PORTD;

	return;
}

void init(void)
{
	int i;

	// start up delay ... 1 min.
	//for( i = 0 ; i < 240 ; i++ )
		_delay_ms(250);

	// port init
	DDRD = 0xFF;
	PORTD = 0x00;

	// enable timer2
	timer2_init();

	rtc_init();

	// enable interrupts
	sei();

	return;
}

int main(void)
{
	// init
	init();

	while(1);

	return 0;
}
