#include <avr/io.h>

int main(void)
{
	int i,j;
	
	DDRD = 0xFF;
	PORTD = 0xAA;

	while(1)
	{
		for( i = 0 ; i < 1000 ; i++)
		for( j = 0 ; j < 1000 ; j++)
		{
			// do nothing ...
		}
			
		PORTD = ~PORTD;
	}

	return ;
}
