#include "main.h"

void init(void)
{
	USART_Init(USART_BAUD_4800, USART_FRAME_8N2);
	
	return;
}

int main(void)
{
	char c;
	
	init();

	delay_ms(5000);
	
	for( c = 0 ; c < 50 ; c++ )
		USART_Transmit(c);

	return 0;
}
