void tctr0_init(void)
{
	// set mode : prescalar = 8.
	TCCR0A = (1 << CS01);

	return;
}

void delay_us(int us)
{
	int count;

	//intialize timer
	TCNT0 = (us / 8 ) - 125 ;

	//clear flag
	TIFR0 = TIFR0 | (1 << TOV0) ;

	//wait for flag
	while(!(TIFR0 & (1 << TOV0)));
	
	return;
}
	
void delay_ms(int ms)
{
	int count;
	
	for(count = 0 ; count < ms; count++)
	{
		//intialize timer
		TCNT0 = 0x82;

		//clear flag
		TIFR0 = TIFR0 | (1 << TOV0) ;

		//wait for flag
		while(!(TIFR0 & (1 << TOV0)));
	}
	
	return;
}
