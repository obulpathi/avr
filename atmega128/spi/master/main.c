#include "main.h"

int init(void)
{
	/*Intialize SPI on master side*/
	spi_init();
	
	return 0;
}

int main(void)
{
	init();

	//code goes here

	return 0;
}
