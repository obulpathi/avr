void pwm0_init(void)
{
	DDRB = (1 << PB3);
	OCR0 = 0x00;
	TCCR0 = (1 << WGM00) | (1 << COM01) | (1 << CS00);
	
	return;
}

void pwm0_set_duty_cycle(unsigned char dc)
{
	OCR0 = dc;

	return;
}

void pwm0_deinit(void)
{
	return;
}
