#include <avr/io.h>

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0xAA;
	PORTD = 0x55;
	PORTD = 0xAA;
	PORTD = 0x55;

	while(1);

	return 0;
}
