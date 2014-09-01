// base functions
//
// reads status of the flash device
// returns when flash device is ready
void flash_device_ready(void)
{
	while((flash_status_read() & FLASH_MASK_BUSY) == FLASH_BUSY);
	
	return;
}

// interface functions start from here ... 
//
// initializes the flash device
void flash_init(void)
{
	//intialize flash here ...
	//write protect bits ...
	//reset and others ... k
	
	return;
}

// de initializes the flash device
void flash_deinit(void)
{
	// de intialize flash and disalloate the ports ...
	
	return;
}

// flash interface starts
/*
*/
// erase and wite data to flash page
void flash_page_write(unsigned int address)
{
	int i;
	
	flash_device_ready();
	
	spi_start();
	spi_tx( FLASH_PW_TH_BUFFER1 );
	spi_tx( address >> 8 );
	spi_tx( address );
	spi_tx( FLASH_PAGE_START );
	for(i = 0 ; i < 528 ; i++)
		spi_tx(data[i]);
	spi_end();

	return;
}

// reads data from flash page
void flash_page_read(unsigned int address)
{
	int i;
	
	flash_device_ready();
	
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

	return;
}
/*
*/

// verifies if data is written correctly to flash
//int flash_verify_page_write(void)
//{
	/*
	spi_start();
	device_ready();
	spi_tx(MM_PAGE_BUF_COM);
	// get this thing ready only if necessary ...
	// it should be a part of file system for marking bad blocks and so on ...
	spi_end();
	*/
	
//	return FLASH_TRUE;
//}

// write commands
int flash_buffer1_write(void)
{
	return 0;
}

int flash_buffer2_write(void)
{
	return 0;
}

int flash_buffer1_to_main_mem_with_erase(void)
{
	return 0;

}

int flash_buffer2_to_main_mem_with_erase(void)
{
	return 0;
}

// read commands
unsigned char flash_status_read(void)
{
	unsigned char status;
	
	spi_start();
	spi_tx(FLASH_SR_READ);
	status =  spi_rx();
	spi_end();

	return status;
}

int flash_read_buffer1(void)
{
	return 0;
}

int flash_read_buffer2(void)
{
	return 0;
}

int flash_read_main_mem_thr_buffer1(void)
{
	return 0;
}

int flash_read_main_mem_thr_buffer2(void)
{
	return 0;
}

int flash_main_mem_page_read(void)
{
	return 0;
}

// erase commands
int flash_page_erase(void)
{
	return 0;
}

int flash_block_erase(void)
{
	return 0;
}

// additional commads
//
