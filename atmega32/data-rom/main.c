#include "main.h"

int main (void)
{
	char buf[32];
	PGM_P p;
	int i;

	DDRD = 0xFF;

	tctr0_init();

	memcpy_P(&p, &array[0], sizeof(PGM_P));

	strcpy_P(buf, p);

	for( i = 0 ; i < 4 ; i++ )
	{
		PORTD = buf[i];
		delay_ms(1000);
	}

	return 0;
}
