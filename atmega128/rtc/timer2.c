// set timer2 in asychronous mode, clocked from external 32KHz source ... 
void timer2_init(void)
{
	// select external crystal oscillator
	ASSR = 1 << AS2;

	// set mode : prescalar = 128.
	TCCR2A = 0x00;
	TCCR2B = ( 1 << CS22 ) | ( 1 << CS20 );

	// clear timer
	TCNT2 = 0;

	// enable interrupt
	TIMSK2 = ( 1 << TOIE2 );

	return;
}
