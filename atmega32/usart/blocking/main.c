#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;

	tctr0_init();
	usart_init( USART_BAUD_2400, USART_FRAME_8N1 );

	return;
}

int main(void)
{
	init();

	while(1)
	{
		PORTD = ~ PORTD;
		delay_ms(1000);
	}

	unsigned char c;

//  write your code here
	while(1)
	{
		usart_tx('1');
		c = usart_rx();
		delay_ms(100);
		usart_tx('2');
		delay_ms(100);
		usart_tx('3');
		delay_ms(100);
		usart_tx('4');
		delay_ms(100);
		usart_tx( 0x10);
		delay_ms(1000);
	}

	while(1);

	return 0;
}
