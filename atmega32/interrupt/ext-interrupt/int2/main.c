#include "main.h"

void init(void)
{
	// port settings
	DDRD = 0xFF;
	PORTD = 0xFF;
	
	// interupt2 init
	int2_init();
	
	return;
}

int main(void)
{
	// init
	init();

	//prog code
	while(1)
		sleep();

	return 0;
}	
