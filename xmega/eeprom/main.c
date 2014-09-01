#define F_CPU 2000000UL

#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>

void init(void)
{
	// allow power to stabilize
	_delay_ms(250);

	// port settings
	PORTE.DIR	 	= 0xFF;
	PORTE.OUT		= 0xA5;

	return;
}

int main(void)
{
	unsigned char c;
	unsigned int i;

	init();

	for(i = 0, c = 0; i <= 255; i++, c++)
		eeprom_write_byte(i, c);
		
	for(i = 0; i <= 255; i++)
	{
		PORTE.OUT = ~ eeprom_read_byte(i);
		_delay_ms(500);
	}
	
	// write your code here
	while(1)
	{
		PORTE.OUT = ~PORTE.OUT ;
		_delay_ms(500);
		PORTE.OUT = ~PORTE.OUT;
		_delay_ms(500);
	}

	// never die
	while(1);

	return 0;
}
