void light_init(void)
{
	TWI_Init(TWI_BAUD_4800,TWI_PRESCALAR_4800);
	
	// start
	if(TWI_Start())
	{
		PORTD = 0x01;
		while(1);
	}

	// go to write mode
	if(TWI_TxSlaveAddress(LIGHT_SENSOR , TWI_WRITE_MODE))
	{
		PORTD = 0x02;
		while(1);
	}

	// send controller register addressas command byte
	if(TWI_Transmit(CONTROL_REG))
	{
		PORTD = 0x03;
		while(1);
	}

	// send start byte to controller register
	if(TWI_Transmit(POWER_UP))
	{
		PORTD = 0x04;
		while(1);
	}

	// stop
	TWI_Stop();
	
	return;
}

unsigned char light_read(void)
{
	unsigned char data;
	
	// start
	TWI_Start();

	// go to write mode
	if(TWI_TxSlaveAddress(LIGHT_SENSOR , TWI_WRITE_MODE))
	{
		PORTD = 0x05;
		while(1);
	}

	// send ADC channel0 high register addressas command byte
	if(TWI_Transmit(ADC_CHANNEL0_HIGH))
	{
		PORTD = 0x06;
		while(1);
	}

	// restart
	if(TWI_Restart())
	{
		PORTD = 0x07;
		while(1);
	}
		

	// go to read mode
	if(TWI_TxSlaveAddress(LIGHT_SENSOR, TWI_READ_MODE))
	{
		PORTD = 0x08;
		while(1);
	}

	// read the data
	data = TWI_ReceiveLastByte();

	// stop
	TWI_Stop();
	
	return data;
}
