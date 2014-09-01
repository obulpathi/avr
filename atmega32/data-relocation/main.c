to be continued ... 

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
	int i;

	init();

	delay_ms(2500);

	for( i = 0 ; i < 4 ; i++ )
	{
		PORTD = data[i];
		delay_ms(1000);
	}

	while(1);

	return 0;
}
