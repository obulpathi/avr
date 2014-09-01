void tctr2_init(void)
{
	// set mode : prescalar = 8.
	TCCR2B = (1 << CS21);

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
