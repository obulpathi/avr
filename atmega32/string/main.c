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
	char *cptr, cary[5] = "hi";
	cptr = cary;

	init();

	//prog code

	PORTD = strlen(cptr);

	while(1);

	return 0;
}	
