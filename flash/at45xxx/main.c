#include "main.h"

unsigned char data[528];

int init(void)
{
	tctr0_init();
	spi_init();
	at45xxx_init();
	
	DDRD = 0xFF;
	PORTD = 0x0F;
	
	return 0;
}

int main(void)
{
	int i, flag;
	unsigned char c;
	
	init();

	// writing all possible combo's to data[]
	c = 0x00;
	for( i = 0 ; i < 528 ; i++)
	{
		data[i] = c;
		c++;
	}
	
	// write data to at45xxx page
	at45xxx_page_write(0);

	// nullify the data[]
	for( i = 0 ; i < 528 ; i++)
	{
		data[i] = 0x00;
	}
	
	// read data from at45xxx page
	at45xxx_page_read(0);
	
	// compare for correctness
	flag = 0;
	c = 0x00;
	for( i = 0 ; i < 528 ; i++)
	{
		if(data[i] != c)
		{
			flag = 1;
		}

		c++;
	}

	// testing for boundary errors
	if ( !at45xxx_page_write( 10000 ) )
		flag = 1;

	if ( !at45xxx_page_read( 10000 ) )
		flag = 1;

	if ( !at45xxx_page_write( 8192 ) )
		flag = 1;

	if ( !at45xxx_page_read( 8192 ) )
		flag = 1;

	// errors
	if(flag == 1)
	{
		PORTD = 0xA5;
		while(1);
	}

	// sucess
	while(1)
	{	
		delay_ms(1000);
		PORTD = ~PORTD;
	}
	
	while(1);

	return 0;
}
