#include<avr/io.h>
#include<inttypes.h>

void PWM_init(void);
void PWM_setDutyCycle(uint8_t dc);
void ADC_init(void);
uint8_t ADC_read(void);

int main(void)
{
	PWM_init();
	ADC_init();

	while(1)
		PWM_setDutyCycle(ADC_read()/3);

	return 0;
}

void PWM_setDutyCycle(uint8_t dc)
{
	OCR0 = dc;

	return;
}

void PWM_init(void)
{
	DDRB = (1 << PB3);
	OCR0 = 0x80;
	TCCR0 = (1 << WGM01) | (1 << WGM00) | (1 << COM01) | (1 << CS00);
	
	return;
}

void ADC_init(void)
{
        ADMUX = (1 << ADLAR) | (1 << MUX0);
        ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (ADPS0) ;

        return;
}

uint8_t ADC_read(void)
{
        ADCSRA = ADCSRA | (1 << ADSC);
        while(bit_is_set(ADCSRA,ADSC));

        return ADCH;
}

