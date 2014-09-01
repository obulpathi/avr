#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;

	DDRC = 0xFF;
	PORTC = 0x00;

	tctr0_init();
	spi_init();
	micromag3_init();

	return;
}

int main(void)
{
	init( );

	//prog code

	spi_start( );

	while( 1 )
	{
			PORTD = micromag3_read( XAXIS );
			delay_ms( 100 );
	}

	while(1);

	return 0;
}
