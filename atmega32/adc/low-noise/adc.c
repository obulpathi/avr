void adc_init(void)
{
        ADMUX = x10_10;
        ADCSRA = (1 << ADEN) | ( 1 << ADIE ) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) ;

	return;
}
