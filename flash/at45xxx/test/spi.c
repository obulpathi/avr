void spi_init(void)
{	
	/*set MOSI out ; SCK out ; SS out ;*/
	DDR_SPI = DDR_SPI | (1 << MOSI) | (1 << SCK) | (1 << SS);
	/*Set MISO in */
	DDR_SPI = DDR_SPI & ~(1 << MISO);
	/*Enable SPI; set Master mode; SPI Mode = 3; f' = f/128 */
	SPCR = (1 << SPE) | (1 << MSTR) | ( 1 << CPOL) | ( 1 << CPHA) | (1 << SPR1) | (1 << SPR0);
	
	return;
}

void spi_tx(unsigned char data)
{
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));

	return;
}

unsigned char spi_rx(void)
{
	/*Send a dummy character */
	SPDR = DUMMY;
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)));
	/* Return data register */
	return SPDR;
}

void spi_start(void)
{
	/*End, if any, previous session */
	spi_end();
	/*Set SS low - start a new session */
	PORT_SPI = PORT_SPI & ~(1 << SS);

	return;
}

void spi_end(void)
{
	/*Set SS high */
	PORT_SPI = PORT_SPI | (1 << SS);

	return;
}
