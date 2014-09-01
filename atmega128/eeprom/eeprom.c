// writes "data" to "address"
void eeprom_write(unsigned int address, unsigned char data)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE));
	/* Set up address and data registers */
	EEAR = address;
	EEDR = data;
	/* write logical one to EEMWE */
	EECR = EECR | (1<<EEMWE);
	/* Start eeprom write by setting EEWE */
	EECR  = EECR | (1<<EEWE);

	return;
}

// returns "data" at "address"
unsigned char eeprom_read(unsigned int address)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE));
	/* Set up address register */
	EEAR = address;
	/* Start eeprom read by writing EERE */
	EECR = EECR | (1<<EERE);
	
	/* Return data from data register */
	return EEDR;
}
