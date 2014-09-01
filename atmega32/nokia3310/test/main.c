#include "global.h"
#include "main.h"

#include "spi.h"
#include "spi.c"

#include "nokia3310.h"
#include "nokia3310.c"

void init(void)
{
	// allow power to stabilize
	_delay_ms(250);

	// disable jtag
	MCUCSR = MCUCSR | 0x80;
	MCUCSR = MCUCSR | 0x80;

	// port settings
	DDRD = 0xFF;
	PORTD = 0x00;

	// init lcd
	lcd_init();

	return;
}

int main(void)
{
	init();

//  write your code here
	lcd_putc('4');

	while(1);

	return 0;
}
