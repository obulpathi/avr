SIGNAL(SIG_OVERFLOW0)
{
	PORTA = ~PORTA;
}

void TCTR0_Init(void)
{
	// check the clock source ...
	TCCR0 = (1 << CS02) | (1 << CS00); // F' = F/1024;
	TIMSK = TIMSK | (1 << TOIE0);      // OVERFLOW INTERRUPT ENABLED;

	return;
}


