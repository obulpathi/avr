#include "main.h"

void init(void)
{
	DDRD = 0x00;
	PORTD = 0x00;
	
	return;
}

int main(void)
{
	init();
	
	// write a data byte at address 0
	eeprom_write(0,'4');
	
	// read data byte stored at address 0
	PORTD = eeprom_read(0);

	while(1);

	return 0;
}	
