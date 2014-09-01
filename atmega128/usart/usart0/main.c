#include "main.h"

void init(void)
{
	usart0_init(USART_BAUD_2400, USART_FRAME_8N1);

	return;
}

int main(void)
{
	
	init();

	usart0_rx();

	return 0;
}
