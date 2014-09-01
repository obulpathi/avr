void pwm2_init(void)
{
	DDRD = DDRD | (1 << PD7);
	OCR2 = 0x00;
	TCCR2 = (1 << WGM20) | (1 << COM21) | (1 << CS20);
	
	return;
}

void pwm2_set_duty_cycle(unsigned char dc)
{
	OCR2 = dc;

	return;
}

void pwm2_deinit(void)
{
	return;
}
