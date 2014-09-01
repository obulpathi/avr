void SPI_Init(void)
{
	// Set MOSI and SCK output, all others input
	SPIF_DDR = (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS);
	
	// Enable SPI, Master, set clock rate fck/16
	SPIF.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm | 0x01; // prescalar

	// select slave
	SPIF_OUT = SPIF_OUT | (1 << DD_SS);
}

void SPI_Tx(char data)
{
	/* Start transmission */
	SPIF.DATA = data;
	
	/* Wait for transmission complete */
	while(!(SPIF.STATUS & SPI_IF_bp));
	
	return;
}

unsigned char SPI_Rx(void)
{
	char dummy = 0xAA;
	
	/* Start transmission */
	SPIF.DATA = dummy;
	
	/* Wait for transmission complete */
	while(!(SPIF.STATUS & SPI_IF_bp));
	
	return SPIF.DATA;
}

unsigned char SPI_TRx(unsigned char data)
{
	/* Start transmission */
	SPIF.DATA = data;
	
	/* Wait for transmission complete */
	while(!(SPIF.STATUS & SPI_IF_bp));
	
	return SPIF.DATA;
}
