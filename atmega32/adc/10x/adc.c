void adc_init(void)
{
	ADMUX = x10_10 ;
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (ADPS0);
	
	return;
}

uint8_t adc_read(void)
{
	ADCSRA = ADCSRA | (1 << ADSC);
	while(bit_is_set(ADCSRA,ADSC));
	
	return ADCH;
}

void adc_deinit(void)
{
	ADMUX = 0xFF;
	ADCSRA = 0xFF;
	
	return;
}
