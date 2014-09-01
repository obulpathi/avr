// this program is a interrupt based adc ...

#include<inttypes.h>

void ADC_init(void);
volatile uint8_t result;

void ADC_init(void)
{
        ADMUX = (1 << ADLAR) | (1 << MUX0);
        ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) ;

	return;
}

SIGNAL(SIG_ADC)
{
	result = ADCH;
}
