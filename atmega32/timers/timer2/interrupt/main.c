#include "main.h"

int init(void)
{
	DDRD = 0xFF;
	PORTD = 0xAA;

 	tctr0_init();

	SREG = SREG | 0x80;
}

int main(void)
{
	while(1)
	{
		// do nothing;
	}

	return ;
}
