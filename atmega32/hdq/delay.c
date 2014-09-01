void TCTR0_Init(void)
{
	// set mode : prescalar = 8.
	TCCR0 = (1 << CS01);

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
		TIFR = TIFR | (1 << TOV0) ;
		//wait for flag
		while(!(TIFR & (1 << TOV0)));
	}
	
	return;
}

void delay_us(unsigned char us)
{
	//intialize timer
	TCNT0 = 0xFF - us;
	//clear flag
	TIFR = TIFR | (1 << TOV0) ;
	//wait for flag
	while(!(TIFR & (1 << TOV0)));
	
	return;
}
