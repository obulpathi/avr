/**************************************/
/* BLOCKING - NON INTERRUPT BASES ADC */
/**************************************/

#include<avr/io.h>
#include<inttypes.h> 

void initADC(void);
uint8_t readADC(void);

int main(void)
{
	initADC();

	while(1)
		readADC();
		
	return 0;
}

void initADC(void)
{
	ADMUX = (1 << ADLAR) | (1 << MUX0);
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (ADPS0) ;
	
	return;
}

uint8_t readADC(void)
{
	ADCSRA = ADCSRA | (1 << ADSC);
	while(bit_is_set(ADCSRA,ADSC));
	
	return ADCH;
}
