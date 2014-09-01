void tctr2_init(void)
{
	// select external crystal oscillator
	ASSR = 1 << AS2;

	// set mode : prescalar = 128.
	TCCR2B = ( 1 << CS22 ) | ( 1 << CS20 );

	return;
}

void delay_sec(void)
{
	// wait for TCNT2 ready
	while( ASSR & ( 1 << TCN2UB ) );

	// initialize timer/counter2
	TCNT2 = 0x00;

	//clear flag
	TIFR2 = TIFR2 | (1 << TOV2) ;

	//wait for flag
	while( ! ( TIFR2 & ( 1 << TOV2 ) ) );

	return;
}
