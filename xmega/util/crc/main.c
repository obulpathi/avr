#define F_CPU 2000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <util/crc16.h>


void init(void)
{
	// allow power to stabilize
	_delay_ms(250);

	// port settings
	PORTE.DIR	 	= 0xFF;

	return;
}

int checkcrc(void)
{
	int i;
	uint16_t crc = 0;
	uint8_t data[] = {0x02, 0x1c, 0xb8, 0x01, 0, 0, 0, 0xa2};
 
	for (i = 0; i < 8; i++)
		crc = _crc16_update(crc, data[i]);

	return crc; // must be 0
}


int main(void)
{
	init();
//	PORTE.OUT = ~0xC0;
	PORTE.OUT = ~0x17;
//	PORTE.OUT = ~_crc16_update(0, 0x05);
//	PORTE.OUT = ~_crc16_update(0, 0x05) >> 8;
	while(1);

	if(checkcrc() == 0)
		PORTE.OUT = 0xFF;
	else
		PORTE.OUT = 0xF0;

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
