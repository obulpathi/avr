#include "main.h"

int init(void)
{
	DDRC = 0xFF;
	PORTC = 0x00;

	MCUCSR = MCUCSR | 0x80;  
	MCUCSR = MCUCSR | 0x80;  
	
	return 0;
}

int main(void)
{
	int i,j;
	
	init();
	
	while(1)
	{
		PORTC = ~PORTC;
		
		for( i = 0 ; i < 1000 ; i++)
		for( j = 0 ; j < 1000 ; j++)
		{
			//do nothing
		}
	}
	
	
	while(1);

	return 0;
}
