void pwm1b_init(void)
{
	DDRD = DDRD | (1 << PD4);
	OCR1BL = 0x00;
	TCCR1A = TCCR1A | (1 << COM1B1);
	TCCR1B = TCCR1B | (1 << CS10);
	
	return;
}

void pwm1b_set_duty_cycle(unsigned char dc)
{
	OCR1BL = dc;

	return;
}

void pwm1b_deinit(void)
{
	pwm1b_set_duty_cycle(0);
	
	return;
}
