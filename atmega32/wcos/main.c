#include "global.h"
#include "main.h"
#include "process.h"
#include "tick.h"

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

  // declare tasks here
  // tick function
  // start sheduler

	return;
}

int main(void)
{
	init();

	// write your code here

	// never die
	while(1);

	return 0;
}
