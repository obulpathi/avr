#include "main.h"

void init(void)
{
	DDRA = 0xFF;
	PORTA = 0xFF;

	DDRD = 0xFF;
	PORTD = 0xFF;

	delay_ms(1000);
	
	// give interrupt on any logical change on INT0 ... 
	MCUCR = MCUCR | ( 1 << ISC00 );
	
	// enable interrupt 0 ... 
	GICR = GICR | 0x40;
	
	// global interrupts enable ...
	SREG = SREG | 0x80;

	return;
}

SIGNAL(SIG_INTERRUPT0)
{ 
	// clear the interrupt ...
	GIFR = GIFR | 0x20;
	    
	// do action ...
	PORTA = ~PORTA;
	delay_ms(1000);
	PORTA = ~PORTA;
	delay_ms(1000);
}

int main(void)
{
	int i;

	init();

	delay_ms(1000);

	while(1)
	{
		PORTD = ~PORTD;
		delay_ms(1000);
	}

	while(1);

	return;
}
