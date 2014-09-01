#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;

	tctr0_init();

	return;
}

int main(void)
{
	init();

	//prog code
	PORTD = parity( 0x01 );
	delay_ms(1000);

	PORTD = 0xFF;
	delay_ms(1000);

	PORTD = parity( 0x03 );
	delay_ms(1000);

	PORTD = 0xFF;
	delay_ms(1000);

	PORTD = parity( 0x02 );
	delay_ms(1000);

	while(1);

	return 0;
}	
