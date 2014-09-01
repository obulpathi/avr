SIGNAL(SIG_OVERFLOW0)
{
	PORTD = ~PORTD;
}

void tctr0_init(void)
{
	TCCR0 = (1 << CS02) | (1 << CS00); // F' = F/1024;
	TIMSK = TIMSK | (1 << TOIE0);      // OVERFLOW INTERRUPT ENABLED;

	return;
}
