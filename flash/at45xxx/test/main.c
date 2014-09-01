#include "main.h"

unsigned char data[528];

int init(void)
{
	// let the power stabilize
	delay_ms(250);

	spi_init();
	flash_init();
	
	DDRD = 0xFF;
	PORTD = 0xFF;
	
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
	
	// write data to flash page
	flash_page_write(0);

	// nullify the data[]
	for( i = 0 ; i < 528 ; i++)
	{
		data[i] = 0x00;
	}

	// wait ...
	delay_ms(250);	

	// read data from flash page
	flash_page_read(0);
/*	
	PORTD = 0x02;
	while(1);
*/
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
/*
	for( i = 0 ; i < 528 ; i++)
	{
			PORTD = data[i];
			delay_ms(250);
			delay_ms(250);
	}
*/
	// errors
	if(flag == 1)
	{
		PORTD = 0xA5;
		while(1);
	}

	// sucess
	while(1)
	{	
		delay_ms(250);
		PORTD = ~PORTD;
	}
	
	while(1);

	return 0;
}
