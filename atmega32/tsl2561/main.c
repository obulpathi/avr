#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0xFF;

	light_init();
	
	return;
}

int main(void)
{
	int i,j;

	init();

	while(1)
	{
		for(i = 0 ; i < 1000 ; i++)
		for(j = 0 ; j < 1000 ; j++)
		{
			// do nothing
		}

		PORTD = light_read();
	}
	
	return 0;
}
