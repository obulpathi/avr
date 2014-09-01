#include <avr/io.h>

#include "delay.h"
#include "delay.c"

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0xFF;


	while(1)
	{
		delay_ms(1000);
		PORTD = ~PORTD;
	}

	return ;
}
