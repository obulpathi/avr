// first read the hdq specs k ... and then read the HDQ.c and HDQ.h then go for writing the software ... k
// use timer 0 ... dedicated to hdq ...

void timer0_init(void)
{
	// set mode : prescalar = 1 ... no prescaling ...
	TCCR0 = (1 << CS00);

	return;
}

void hdq_init(void)
{
	// set up the port
	// enable the pull up's
	DDRD = 0x00;
	PORTD = 0xFF;
	// make the port output port
	DDRD = 0xFF;
	
	// set up the timer0
	timer0_init();
	
	return;
}

// hdq_break ...
static void hdq_reset(void)
{
	// set bit low ...
	PORTD = 0x00;
	
	// delay of Tb
	//intialize timer
	TCNT0 = 0xFF - HDQ_BREAK;
	//clear flag
	TIFR = TIFR | (1 << TOV0) ;
	//wait for flag
	while(!(TIFR & (1 << TOV0)));
	
	// set bit high ...
	PORTD = 0xFF;
	
	// delay of Tbr
	//intialize timer
	TCNT0 = 0xFF - HDQ_BREAK_RECOVERY;
	//clear flag
	TIFR = TIFR | (1 << TOV0) ;
	//wait for flag
	while(!(TIFR & (1 << TOV0)));

	return;
}

/*
unsigned char hdq_rx_byte(void)
{
	register unsigned char bit_count = 8;
	
	do
	{
		// keep watching for a transistion from high to low ... 
		// start timer : do this in interrupt  ... 
		// keep watching for transisiton from low to high ... 
		// if time > limit if else ... 
	        // store the bit
	        data = (data << 1) | ...; // fill in the stuff here ...
	}
	while (--bit_count);
	
	return '4';
}
*/

void hdq_tx_byte(unsigned char data)
{
	register unsigned char bit_count = 8;
	
	do
	{
		// set the bit
		PORTD = 0x00;
		if ( data & MSB == 0 )
		{
			// delay 25 us
			PORTD = 0xFF;
			//delay 175 us
		}
		else
		{
			// delay 100 us
			PORTD = 0xFF;
			// delay 100 us
		}
		
	        // get the next bit to send
	        data <<= 1;
	}
	while (--bit_count);

	return;	
}
