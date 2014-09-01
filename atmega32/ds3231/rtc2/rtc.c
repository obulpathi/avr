// errors ... who will handle them????
// read a register
unsigned char rtc_read_reg(unsigned char address)
{
	unsigned char data;
	
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
	
	twi_restart();
	
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

// set the pointer to read / write 
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

// check if rtc is busy
int rtc_busy(void)
{
	return ( ( rtc_read_reg( RTC_REG_STATUS ) & RTC_BUSY_MASK ) == RTC_BUSY );
}

// rtc interface functions start from here ...

// initializes rtc
int rtc_init(void)
{
	twi_init(TWI_BAUD_4800, TWI_PRESCALAR_4800);
	// call rtc_set_time ... ??? 
	// this should erase all the interrupts first ... and then reset the time ... 
	
	return;
}

// starts rtc
void rtc_start(void)
{
	rtc_write_reg(RTC_REG_STATUS, RTC_START);
	
	return;
}

// enable interrupt setting 
void rtc_enable_interrupt1(void)
{
	unsigned char data;

	data = rtc_read_reg( RTC_REG_CTRL );
	rtc_write_reg( RTC_REG_CTRL, data | RTC_EN_INT1 );
	
	return;
}

// disable interrupt 1
void rtc_disable_interrupt1(void)
{
	unsigned char data;

	data = rtc_read_reg( RTC_REG_CTRL );
	rtc_write_reg( RTC_REG_CTRL, data & RTC_DIS_EN_INT1 );
	
	return;
}

// clears interrupt1 
void rtc_clear_interrupt1(void)
{
	unsigned char data;

	data = rtc_read_reg( RTC_REG_STATUS );
	rtc_write_reg( RTC_REG_STATUS , data & RTC_CLR_INT1 ) ;
	
	return;
}

// read sec's
unsigned char rtc_read_sec(void)
{
	return rtc_read_reg(RTC_REG_SEC);
}

// set interrupt 1 ... take date and time form the date and time varables ... 
// should one use time and date or time alone is sufficient ???
int rtc_set_interrupt1(void)
{
	// start
	twi_start();
	// tx slave address
	twi_tx_slave_address(TIMER, TWI_WRITE_MODE);
	// transmit address	
	twi_transmit( RTC_REG_ALARM1_SEC );
	// set time	
	// set sec
	twi_transmit( time[5] | ( time[4] << 4 ) );
	// set min
	twi_transmit( time[3] | ( time[2] << 4 ) );
	// set hour
	twi_transmit( time[1] | ( time[0] << 4 ) );
	// set date
	twi_transmit( ( date[1] << 4 ) | date[0] );
	
	// stop twi
	twi_stop();
	
	return 0;
}

// set rtc time ... done.
int rtc_set_time(void)
{
	
	// twi_start
	twi_start();
	
	// set in write mode
	if(twi_tx_slave_address(TIMER, TWI_WRITE_MODE) )
	{
		return 2;
	}
	
	// transmit address : RTC_REG_SEC
	twi_transmit( RTC_REG_SEC );
		
	// start sending time 
	// send sec
	twi_transmit( time[5] | ( time[4] << 4 ) );
	// send min
	twi_transmit( time[3] | ( time[2] << 4 ) );
	// send hour
	twi_transmit( time[1] | ( time[0] << 4 ) );
	// send day
	twi_transmit( day );
	// start sending date
	// send date
	twi_transmit( date[0] | ( date[1] << 4 ) );
	// send month
	twi_transmit( date[2] | ( date[3] << 4 ) );
	// send year
	twi_transmit( date[4] | ( date[5] << 4 ) );
		
	// stop twi
	twi_stop();
	
	
	return 0;
}
	
// read time to date and time reg's ... reframe this ... k but how???? ... here u can use set pointer ??? what say you???
int rtc_read_time(void)
{
	unsigned char data;
	
	
	twi_start();
	
	if(twi_tx_slave_address(TIMER, TWI_WRITE_MODE) )
	{
		return 2;
	}
	
	if(twi_transmit(RTC_REG_SEC))
	{
		return 3;
	}
	
	twi_restart();
	
	// set in read mode
	if(twi_tx_slave_address(TIMER, TWI_READ_MODE) )
	{
		return 2;
	}
	
	// start reading time 
	// read sec
	data = twi_receive();
	time[5] = data & LOW_NIBBLE ;
	time[4] = data >> 4 ;
	// read min
	data = twi_receive();
	time[3] = data & LOW_NIBBLE ;
	time[2] = data >> 4 ;
	// read hour
	data = twi_receive();
	time[1] = data & LOW_NIBBLE ;
	time[0] = data >> 4 ;
	// read day
	data = twi_receive();
	day = data;
	// start reading date
	// read date
	data = twi_receive();
	date[0] = data & LOW_NIBBLE ;
	date[1] = data >> 4 ;
	// read month
	data = twi_receive();
	date[2] = data & LOW_NIBBLE ;
	date[3] = data >> 4 ;
	// read year
	data = twi_receive();
	date[4] = data & LOW_NIBBLE ;
	date[5] = data >> 4 ;
		
	// stop twi
	twi_stop();
	
	
	return 1;
}

// here are a few cokkies ;)
// enable interrupt2
int rtc_enable_interrupt2(void)
{
	return 0;
}

// clear interrupt 2
int rtc_clear_interrupt2(void)
{
	return 0;
}

// disable interrupt 2
int rtc_disable_interrupt2(void)
{
	return 0;
}

// set interrupt 2
int rtc_set_interrupt2(void)
{
	return 0;
}

// stop the timer ... don't do any thing stupid ... just stop it ... k done ... 
// is this sufficient or more is needed????
// this thing is not working >>><<< or there's no possibility of doing this ... 
// there's no way of doing this ... k
int rtc_stop(void)
{
	// hey stupid this is not possible ... it like heart ... it can only start, can not be stopped.	
	return 1;
}

// deinit the rtc ... stop the rtc ... clear the interrupts ... 
// temporarly skip this ... coz its yet uncertain of what one should do here ... K
int rtc_deinit(void)
{
	return 0;
}
