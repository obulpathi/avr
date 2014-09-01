void pwm1a_init(void)
{
	DDRD = DDRD | (1 << PD5);
	OCR1AL = 0x00;
	TCCR1A = TCCR1A | (1 << WGM10) | (1 << COM1A1);
	TCCR1B = TCCR1B | (1 << CS10);
	
	return;
}

void pwm1a_set_duty_cycle(char dc)
{
	OCR1AL = dc;

	return;
}

void pwm1a_deinit(void)
{
	return;
}
