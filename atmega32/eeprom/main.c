#include <avr/io.h>
#include <avr/eeprom.h>

unsigned char EEMEM c = 0x04;

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;
	
	return;
}

int main(void)
{
	init();
	
	// read data byte stored at address 0
	PORTD = eeprom_read_byte(&c);

	while(1);

	return 0;
}	
