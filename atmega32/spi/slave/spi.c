void spi_slave_init(void)
{
	/* set MOSI in ; MISO out ; SCK in ; SS in ; */
	DDR_SPI = DDR_SPI | (1 << MISO);
	/*Enable SPI; set Slave ; f' = f/128 ; */
	SPCR = (1 << SPE) | (1 << SPR1) | (1 << SPR0);
	
	return;
}

unsigned char spi_trx(unsigned char data)
{
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));

	/* Return data register */
	return SPDR;
}
