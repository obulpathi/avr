#include "global.h"
#include "main.h"

void init(void)
{
	// allow power to stabilize
	_delay_ms(250);

	// port settings
	DDRB = 0xFF;
	PORTB = 0xFF;

	return;
}

int main(void)
{
	init();

	// write your code here
  while(1)
  {
    PORTB = ~PORTB;
    _delay_ms(250);
  }

	// never die
	while(1);

	return 0;
}
