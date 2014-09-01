// base functions start here

// sets  the pointer to a register
int rtc_set_pointer(unsigned char pointer)
{
	if(twi_start())
	{
		return 1;
	}

	if(twi_tx_slave_address(TIMER, TWI_WRITE_MODE) )
	{
		return 2;
	}
	
	if(twi_transmit(pointer))
	{
		return 3;
	}
	
	twi_stop();
	
	return 0;
}

// reads a register
unsigned char rtc_read_reg(unsigned char address)
{
	unsigned char data;
	
	rtc_set_pointer(address);

	delay_ms(100);

	if(twi_start())
	{
		return 1;
	}

	if(twi_tx_slave_address(TIMER, TWI_READ_MODE) )
	{
		return 2;
	}
	
	data = twi_receive_last_byte();
	
	twi_stop();

	return data;
}

// write data to a register
int rtc_write_reg(unsigned char address, unsigned char data)
{
	if(twi_start())
	{
		return 1;
	}

	if(twi_tx_slave_address(TIMER, TWI_WRITE_MODE) )
	{
		return 2;
	}
	
	if(twi_transmit(address))
	{
		return 3;
	}
	
	if(twi_transmit(data))
	{
		return 3;
	}
	
	twi_stop();
	
	return 0;
}

// check if rtc is busy ...
int rtc_busy(void)
{
	if( twi_start() )
		return 1;
	
	if( twi_tx_slave_address(TIMER, TWI_READ_MODE) )
		return 2;
	
	twi_receive_last_byte();
		
	twi_stop();
	
	return 0;
}

// rtc interface functions start from here ...

// initializes rtc
void rtc_init(void) // complete ...
{
	twi_init(TWI_BAUD_4800, TWI_PRESCALAR_4800);
	
	return;
}

// starts rtc ...
int rtc_start(void)
{
	rtc_write_reg(REG_STATUS, RTC_START);
	
	return 0;
}

// reads sec
int rtc_read_sec(void) 
{
	PORTD = rtc_read_reg(REG_SEC);
	
	return 0;
}

// reads time
void rtc_read_time(unsigned char *time)
{
	unsigned char c;
	int i;
	
	if(!twi_start())
	
	if(!twi_tx_slave_address(TIMER, TWI_READ_MODE) )
	
	//start counting here ...
	
	for( i = 0 ; i < 18 ; i++ )
	{
		( twi_receive() );
	}
	
	c = twi_receive_last_byte();
		
	twi_stop();
	
	return c;
}

// write time real time in nature ... call thi function from init before starting the oscillator ...
void rtc_write_time(unsigned char *time)
{
	
	return;
}
