#include "main.h"

void init(void)
{
	DDRC = 0xFF;
	PORTC = 0xAA;

	tctr2_init();

	return;
}

int main(void)
{
	// int i;

	// init();
	DDRC = 0xFF;
	PORTC = 0xFF;

	// select external clock
	ASSR = 1 << EXCLK ;

	PORTC = ~ PORTC;

	// code goes here

	//TCNT2 = 0x00;
//	while( TCNT2 == 0x00 );

	while(1)
	{
		PORTC = ~ PORTC;
	//	delay_ms(1);
	}

	while(1);

	return 0;
}
