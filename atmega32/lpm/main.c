#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;

	// power up delay
	delay_ms(100);
		
	return;
}

int main(void)
{
	uint32_t i = 0;
	unsigned char buf;
	
	init();
	
	while(1)
	{
		PORTD = 0xFF;
		_delay_ms(250);
		PORTD = 0x00;
		_delay_ms(250);
		_delay_ms(250);
		_delay_ms(250);
		_delay_ms(250);

		for( i = 0 ; i < 10 ; i++ )
		{
			PORTD = pgm_read_byte(i);
			delay_ms(250);
			delay_ms(250);
			delay_ms(250);
			delay_ms(250);
			delay_ms(250);
			delay_ms(250);
			delay_ms(250);
			delay_ms(250);
		}
	}

	 // buf = pgm_read_word(i);

	while(1);

	return 0;
}
