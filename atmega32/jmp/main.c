#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;

	tctr0_init();

	return;
}

int main(void)
{
	static void (* fun)(void) = 0x0000;
//	static void (* fun)(void) = main;

	init();

	//prog code

	delay_ms(1000);
	PORTD = ~ PORTD;
	delay_ms(1000);

	fun();

	while(1);

	return 0;
}	
