void micromag3_init(void)
{
		// init

		return;
}

int micromag3_read(unsigned char axis)
{
		int result;

		// pulse
		PORTC = 0xFF;
		delay_ms(1);
		PORTC = 0x00;
		delay_ms(1);

		// send command
		spi_tx(axis);

		// wait for data ready
		delay_ms(10);

		// read the data 
		result = spi_rx();
		result = ( result << 8 ) | spi_rx();

		return result;
}
