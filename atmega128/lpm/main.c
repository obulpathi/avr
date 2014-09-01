#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0xFF;
	
	return;
}

int main(void)
{
	uint32_t i;
	char *buf;
	
	init();

	boot_page_erase(1);

	
	while(1)
	{
		delay_ms(100);
		PORTD = ~PORTD;
	}

	return 0;
}	
