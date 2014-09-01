void blink_init(void)
{
	// port settings
	PORTE_DIRSET	= 0x0F;
	PORTE_OUT	= 0x00;

	return;
}

void blink(void)
{
	while(1)
	{
		PORTE_OUT = 0x0F;
		_delay_ms(250);
		_delay_ms(250);
		PORTE_OUT = 0x00;
		_delay_ms(250);
		_delay_ms(250);
	}
}
