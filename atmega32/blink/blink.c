void pulse()
{
	PORTD = 0xFF;
	delay_ms(1000);
	PORTD = ~ PORTD;
	delay_ms(1000);

	return ;
}

void blink(void)
{
	while(1)
	{
		PORTD = ~ PORTD;
		delay_ms(1000);
	}
}
