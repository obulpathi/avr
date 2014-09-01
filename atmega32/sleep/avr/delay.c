SIGNAL(SIG_OVERFLOW0)
{
	PORTA = ~PORTA;
}

void TCTR0_Init(void)
{
	// check the clock source ...
	TCCR0 = (1 << CS01); // F' = F/8;
	TIMSK = TIMSK | (1 << TOIE0);      // OVERFLOW INTERRUPT ENABLED;

	return;
}


