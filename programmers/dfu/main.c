#include "global.h"
#include "main.h"

void init(void)
{
	// allow power to stabilize
	_delay_ms(250);

	// port settings
	DDRC = 0xFF;
	PORTC = 0xFF;

	return;
}

int main(void)
{
	init();

	// write your code here
  while(1)
  {
    PORTC = ~PORTC;
    _delay_ms(250);
  }

	// never die
	while(1);

	return 0;
}
