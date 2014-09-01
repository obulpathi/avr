#include "main.h"

SIGNAL(SIG_ADC)
{
	result = ADCL | ( ADCH << 8 );
}

void init(void)
{
	// port initializations
	DDRC = 0xFF;
	PORTC = 0xFF;
	
	// initialize timer
	tctr0_init();

	// initialize sleep
	sleep_init();

	// initialize adc
	adc_init();
	
	// enable interrupts
	SREG = SREG | 0x80;
	
	return;
}

int main(void)
{
	// init
	init();
	
	while(1)
	{
		sleep();
		PORTD = result;
		delay_ms(1000);
	}

	return 0;
}	
