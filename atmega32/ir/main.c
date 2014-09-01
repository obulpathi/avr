#include "main.h"

// base functions start

// produces a burst of 14 pulses ... 38KHz square wave ...
void burst(void)
{
	volatile unsigned char count;

	PORTC = 0x00;
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0xFF;	
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0x00;
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0xFF;	
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0x00;
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0xFF;	
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0x00;
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0xFF;	
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0x00;
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0xFF;	
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0x00;
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0xFF;	
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0x00;
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0xFF;	
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0x00;
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0xFF;	
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0x00;
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0xFF;	
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0x00;
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0xFF;	
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0x00;
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0xFF;	
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0x00;
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0xFF;	
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0x00;
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0xFF;	
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0x00;
	count=0;count=1;count=2;count=3;count=4;
	PORTC = 0xFF;	
	count=0;count=1;count=2;count=3;count=4;
	
	return;
}

// keeps off signal ...
void off(void)
{
	delay_us(40);

	return;
}

// init function
void init(void)
{
	MCUCSR = MCUCSR | 0x80;
	MCUCSR = MCUCSR | 0x80;

	DDRC = 0xFF;
	PORTC = 0x00;
	
	TCTR0_Init();

	return;
}

// main function
int main(void)
{
	init();

	while(1)
	{
		burst();
		burst();
		burst();

		off();
	}
	
	while(1);

	return 0;
}
