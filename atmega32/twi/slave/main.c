#include<avr/io.h>

#define SL_ADDRESS 1

void TWI_SlaveInit(void);
char TWI_ReceiveChar(void);
char TWI_ReceiveStart(void);

int main(void)
{
	TWI_SlaveInit();				// cehck the status code for init
	TWI_ReceiveStart(); 			// check the status code for slave addressed
	TWI_ReceiveChar();			//here receive your data

	return 0;
}

void TWI_SlaveInit(void)
{
	/*set bit rate */
	TWBR = 0x10;
	/* set prescalar */
	TWSR = (1 << TWPS1) | (1 << TWPS0);
	/*set address */
	TWAR = SL_ADDRESS;
	/*Enable TWI and Enable Ack */
	TWCR = (1 << TWEN) | (1 << TWEA);
	
	return;
}

char TWI_ReceiveChar(void)
{
	char data;
	/*wait for data reception */
	while(!(TWCR & ( 1 << TWINT)));
	//	check for status code ...
	data = TWDR;
	/*celar the TWINT */
	TWCR = TWCR | (1 << TWINT);
	
	return data;
}

char TWI_ReceiveStart(void)
{
	char status;
	
	/*wait for start condition */
	while(!(TWCR & (1 << TWINT)));
	/*store the status */
	status = TWSR & 0xF8; 
	/*clear TWINT */
	TWCR = TWCR | (1 << TWINT);
	/*Return the status code */
	return status;
}
