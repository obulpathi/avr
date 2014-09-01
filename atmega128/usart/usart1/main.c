#include "main.h"

void init(void)
{
	// allow poer to stabilize
	_delay_ms(250);

	// port settings
	DDRC = 0xFF;
	PORTC = 0x00;

	// init usart
	usart1_init( USART_BAUD_4800, USART_FRAME_8N1 );

	return;
}

int main(void)
{
	init();

	// write your code here
	usart1_tx('+');
	_delay_ms(100);
	usart1_tx('+');
	_delay_ms(100);
	usart1_tx('+');
	_delay_ms(100);

	if ( usart1_rx() == 'O' )
	if ( usart1_rx() == 'K' )
	{
		while(1)
		{
			PORTC = ~ PORTC ;
			_delay_ms(250);
		}
	}

	PORTC = 0xFF;
	while(1);

	return 0;
}
