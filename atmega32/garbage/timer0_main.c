/*************************************/
/* BLOCKED NON-INTERRUPT BASED DELAY */
/*************************************/

#include<avr/io.h>

void delay_ms(int ms);
void TCTR0_Init(void);

int main(void)
{
	DDRA = 0xFF;
	PORTA = 0x0F;
	
	TCTR0_Init();
	while(1)
	{
		delay_ms(1000);
		PORTA = ~PORTA;
	}
	
	return 0;
}

void delay_ms(int ms)
{
	int count;
	
	for(count = 0 ; count < ms; count++)
	{
		//intialize timer
		TCNT0 = 0x82;
		//clear flag
		TIFR = TIFR | (1 << TOV0) ;
		//wait for flag
		while(!(TIFR & (1 << TOV0)));
	}
	
	return;
}

void TCTR0_Init(void)
{
	// set mode : prescalar = 8.
	TCCR0 = (1 << CS01);

	return;
}
