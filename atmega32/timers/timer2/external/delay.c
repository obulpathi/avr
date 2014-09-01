void tctr2_init(void)
{
	// select external crystal oscillator
	ASSR = 1 << AS2;

	// set mode : prescalar = 128.
	TCCR2 = ( 1 << CS22 ) | ( 1 << CS20 );

	return;
}

/*
void delay_us(int us)
{
	int count;

	//intialize timer
	TCNT0 = (us / 8 ) - 125 ;

	//clear flag
	TIFR = TIFR | (1 << TOV0) ;

	//wait for flag
	while(!(TIFR & (1 << TOV0)));
	
	return;
}
	
void delay_ms(int ms)
{
	int count;
	
	for(count = 0 ; count < ms; count++)
	{
		// wait for TCNT2 ready
		while(! ( ASSR & ( 1 << TCN2UB ) ) );

		//intialize timer
		TCNT0 = 0x82;

		//clear flag
		TIFR = TIFR | (1 << TOV0) ;

		//wait for flag
		while(!(TIFR & (1 << TOV0)));
	}
	
	return;
}
*/

void delay_sec(void)
{
	// wait for TCNT2 ready
	while( ASSR & ( 1 << TCN2UB ) );

	// initialize timer/counter2
	TCNT2 = 0x00;

	//clear flag
	TIFR = TIFR | (1 << TOV2) ;

	//wait for flag
	while( ! ( TIFR & ( 1 << TOV2 ) ) );

	return;
}
