#include "main.h"

int main(void)
{
	int i;
	double d1, d2;

	DDRD = 0x00;
	DDRC = 0xFF;
	
	d1 = 0;
  d1 = cos(1.4);

	for( i = 0 ; i < 10 ; i++ )	
	{
		d1 = d1 + PIND * 1.4321;
		d1 = sin(d1);
		PORTC = d1;
	}

	while(1);

	return 0;
}
