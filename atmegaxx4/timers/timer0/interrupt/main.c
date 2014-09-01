#include "main.h"

int init(void)
{
	DDRD = 0xFF;
	PORTD = 0xAA;

	SREG = SREG | 0x80;

 	tctr0_init();
}

int main(void)
{
	while(1)
	{
		// do nothing;
	}

	return ;
}
