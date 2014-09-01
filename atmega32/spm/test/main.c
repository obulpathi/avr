#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;

	return;
}

int main(void)
{
	int i;
	uint16_t page;
	uint8_t data[SPM_PAGESIZE];

	init();

	page = 0;
	for( i = 0 ; i < SPM_PAGESIZE ; i++ )
		data[i] = 0x00;
	
	//prog code
	boot_program_page( page, data);

	PORTD = 0xA5;
	while(1);

	return 0;
}	
