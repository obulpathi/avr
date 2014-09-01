void tctr0_init(void)
{
	// set mode : external clk source.
	TCCR0 = ( 1 << CS02 | 1 << CS01 | CS00 );

	return;
}
