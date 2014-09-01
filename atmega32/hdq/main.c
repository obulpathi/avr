#include "main.h"

void init(void)
{
	hdq_init();
	
	return;
}

int main(void)
{
	init();

	hdq_reset();

	hdq_tx_byte('4');
	
//	PORTD = hdq_rx_byte();

	while(1);

	return 0;
}	
