void TCTR0_Init(void)
{
	// set mode : prescalar = 1
	TCCR0 = (1 << CS00);

	return;
}

void delay_us()
{
	//intialize timer
	TCNT0 = 0xF0; // 0xF4;
	//clear flag
	TIFR = TIFR | (1 << TOV0) ;
	//wait for flag
	while(!(TIFR & (1 << TOV0)));
		
	return;
}

void delay_ms(int delay)
{
	int i;

	for( i = 0 ; i < 4 * delay ; i++ )
	{
		delay_us(250);
	}
	
	return;
}
