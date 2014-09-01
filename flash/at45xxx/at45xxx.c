// base functions

// reads status of the flash device
unsigned char at45xxx_status_read(void)
{
	unsigned char status;
	
	spi_start();
	spi_tx(FLASH_SR_READ);
	status =  spi_rx();
	spi_end();

	return status;
}

// returns when flash device is ready
int at45xxx_device_ready(void)
{
	while((at45xxx_status_read() & FLASH_MASK_BUSY) == FLASH_BUSY);
	
	return 0;
}

// initializes the flash device
void at45xxx_init(void)
{
	//intialize at45xxx here ...
	//write protect bits ...
	//reset and others ... k
	
	return;
}

// de initializes the at45xxx device
void at45xxx_deinit(void)
{
	// de intialize at45xxx and disalloate the ports ...
	
	return;
}

// at45xxx interface starts

// erase and wite data to at45xxx page
int at45xxx_page_write(unsigned int address)
{
	int i;

	// generate page address
	address = ( address << 2 );

	// check if device is busy
	if( at45xxx_device_ready() != 0 )
		return 1;

	// check if address is correct
	if( address < 0 || address >= NUM_PAGES )
		return 2;

	at45xxx_device_ready();
	
	spi_start();
	spi_tx( FLASH_PW_TH_BUFFER1 );
	spi_tx( address >> 8 );
	spi_tx( address );
	spi_tx( FLASH_PAGE_START );
	for(i = 0 ; i < 528 ; i++)
		spi_tx(data[i]);
	spi_end();

	return 0;
}

// reads data from at45xxx page
int at45xxx_page_read(unsigned int address)
{
	int i;
	
	// generate page address
	address = ( address << 2 ) ;

	// check if device is busy
	if( at45xxx_device_ready() != 0 )
		return 1;

	// check if address is correct
	if( address < 0 || address >= NUM_PAGES )
		return 2;

	at45xxx_device_ready();
	
	spi_start();
	spi_tx( FLASH_MM_PAGE_READ );
	spi_tx( address >> 8 );
	spi_tx( address );
	spi_tx( FLASH_PAGE_START );

	for(i = 0 ; i < 4; i++)
		spi_tx( FLASH_DONTCARE );

	for(i = 0 ; i < 528 ; i++)
		data[i] = spi_rx();
		
	spi_end();

	return 0;
}

// verifies if data is written correctly to at45xxx
int at45xxx_verify_page_write(void)
{
	/*
	spi_start();
	device_ready();
	spi_tx(MM_PAGE_BUF_COM);
	// get this thing ready only if necessary ...
	// it should be a part of file system for marking bad blocks and so on ...
	spi_end();
	*/
	
	return FLASH_TRUE;
}

