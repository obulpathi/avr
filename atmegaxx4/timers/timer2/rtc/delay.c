void tctr2_init(void)
{
	// select external clock
	ASSR = 1 << EXCLK ;

	// set mode : prescalar = 1.
//	TCCR2B = (1 << CS20);

	return;
}

void delay_us(int us)
{
	int count;

	//intialize timer
	TCNT2 = (us / 8 ) - 125 ;

	//clear flag
	TIFR2 = TIFR2 | (1 << TOV2) ;

	//wait for flag
	while(!(TIFR2 & (1 << TOV2)));
	
	return;
}
	
void delay_ms(int ms)
{
	int count;
	
	for(count = 0 ; count < ms; count++)
	{
		//intialize timer
		TCNT2 = 0x82;

		//clear flag
		TIFR2 = TIFR2 | (1 << TOV2) ;

		//wait for flag
		while(!(TIFR2 & (1 << TOV2)));
	}
	
	return;
}
