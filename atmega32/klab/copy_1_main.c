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
	init();

//  write your code here
	while(1);

	return 0;
}