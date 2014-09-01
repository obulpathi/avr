#include "main.h"

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;
  PORTD = 0xFF;
	PORTD = 0x00;
  PORTD = 0xFF;
	PORTD = 0x00;
  PORTD = 0xFF;

	while(1);

	return 0;
}
