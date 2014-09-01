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
	uint8_t data[] = {1,2,3,4,5,6,7,8,9,0};
	
	init();

	//prog code
	PORTD = crc( data, 10 );

	while(1);

	return 0;
}	
