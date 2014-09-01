#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0xFF;
	
	return;
}

int main(void)
{
	int i;
	unsigned char c;
	uint8_t buf[256];

	c = 0x00;
	for( i = 0 ; i < 256 ; i++ )
		buf[i] = c++;

	init();

	boot_program_page (50, buf);
        //boot_read_page(50, buf);
	pgm_read_byte_near(50);
	// display this stuff on to port and see what is being read on to port ... 
	
	while(1)
	{
		delay_ms(100);
		PORTD = ~PORTD;
	}

	return 0;
}	
