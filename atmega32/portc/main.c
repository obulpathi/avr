// please use the two code lines (code line-1 n code line-2) in other programs if you want all your led's to get lighted

#include <avr/io.h>

void delay_ms(int ms);

int main(void)
{
	int i,j;
	
	DDRC = 0xFF;
	PORTC = 0x0F;
	
	DDRA = 0xFF;
	PORTA = MCUCSR;
	delay_ms(10);

	MCUCSR = MCUCSR | 0x80; // code line-1
	MCUCSR = MCUCSR | 0x80; // code line-2

	delay_ms(10);

	while(1)
	{
		PORTC = ~ PORTC;
		delay_ms(1);
	}

	return 0;
}

	
void delay_ms(int ms)
{
	int i,j,k;
	
	for(i = 0 ; i < ms ; i++)
	{
		for(j = 0 ; j < 1000 ; j++)
		{
			for(k = 0 ; k < 1000 ; k++)
			{
				// do nothing
			}
		}
	}		
	
	return;
}

