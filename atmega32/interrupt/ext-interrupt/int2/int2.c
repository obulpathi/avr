void int2_init(void)
{
	// give interrupt on raising edge on INT2 ... 
	MCUCSR = MCUCSR | ( 1 << ISC2 );
	
	// enable interrupt 2 ... 
	GICR = GICR | ( 1 << INT2 );
	
	// global interrupts enable ...
	SREG = SREG | 0x80;

	return;	
}

SIGNAL(SIG_INTERRUPT2)
{ 
	// do action ...
	PORTD = ~PORTD;
}
