void twi_init(unsigned char baud, unsigned char prescalar)
{
	// initialize the controll registers and set up the port.
	TWBR = baud;
	TWSR = prescalar;
	TWCR = TWI_INIT;

	// enabling the pull up registers on SDA and SCL.
	PORTC = PORTC | TWI_ENABLE_PULL_UP;
	
	return;
}

int twi_start(void)
{
	// start session
	TWCR = TWI_START;
	// wait till master gains bus controll
	while (!(TWCR & (1<<TWINT)));
	// check status code
	if((TWSR & 0xF8) != TWI_START_SUCESS )
		return 1;
	      
	return 0 ;
}

int twi_restart(void) 
{
	// restart session
	TWCR = TWI_RESTART;
	// wait till master regains bus controll
	while (!(TWCR & (1<<TWINT)));
	// check status code
	if ((TWSR & 0xF8) != TWI_RESTART_SUCESS )
		return 1;
	      
	return 0 ;
}

int twi_tx_slave_address(unsigned char address, unsigned char mode) 
{
	// transmit slave address and mode.
	twi_tx(address | mode);
	if ((TWSR & 0xF8) != TWI_TX_SL_ADD_SUCESS)
	      return 1;
	      
	return 0;
}

int twi_tx(unsigned char data) 
{
	// write data to TWI data register
	TWDR = data;
	// start transmission
	TWCR = TWI_TRANSMIT;
	// wait for data to be transmitted
	while (!(TWCR & (1<<TWINT)));
	// check status code
	if ((TWSR & 0xF8) != TWI_TRANSMIT_SUCESS)
      		return 1;
      
	return 0;
}

unsigned char twi_rx(void)
{
	// start data reception
	TWCR = TWI_RECEIVE;
	// wait till data is received
	while (!(TWCR & (1<<TWINT)));
		
	return TWDR;
}

unsigned char twi_rx_last_byte(void)
{
	// start data reception
	TWCR = TWI_RECEIVE_LAST_BYTE;
	// wait till data is received
	while (!(TWCR & (1<<TWINT)));
		
	return TWDR;
}

void twi_stop(void)
{
	// issue stop command
	TWCR = TWI_STOP;
	  
	return;
}

void twi_deinit(void)
{
	// reset all registers ...
	// pullup's etc .,
	/*
	TWBR
	TWCR
	TWSR
	*/

	return;
}
