#include<avr/io.h>

#include "spi.h"
#include "spi.c"

int main(void)
{
	spi_slave_init();
	//receive here;
	while(1)
		spi_trx('4');
	
	return 0;
}
