#include<avr/io.h>
#include<inttypes.h>

#define START				1
#define SL_ACK				1
// and other constants follow here ...

void TWI_MasterInit(void);
char TWI_Start(char);
void TWI_Stop(void);
char TWI_Transmit(char data); 					 // use proper data types.
char TWI_Receive(char address); 					 // it makes things incompiatable .....

int main(void)
{
	return 0;
}

void TWI_MasterInit(void)
{
	/*set bit rate */
	TWBR = 0x10;
	/* set prescalar */
	TWSR = (1 << TWPS1) | (1 << TWPS0);
	
	return;
}

char TWI_Start(char slave)
{
	/* Intiate START */
	TWCR = (1 << TWINT) | (1 << TWSTA) | ( 1 << TWEN );
	/* Wait for START to be transmited */
	while(~(TWCR & (1 << TWINT)));
	/* Check the Status Register */
	if((TWSR & 0xF8) != START)                       		
		return (TWSR & 0xF8);
		
	return TWI_Transmit(slave);
}

char TWI_Transmit(char data)
{
	/*Load data */
	TWDR = data;
	/*Transmit the data */
	TWCR = ( 1 << TWINT ) | ( 1 << TWEN );
	/*Wait for Ack */
	while(!(TWCR & (1 << TWINT)));

	/*return the status reg */
	return (TWSR & 0xF8);	
}

void TWI_Stop(void)
{
	/* Transmit Stop */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	
	return;
}
