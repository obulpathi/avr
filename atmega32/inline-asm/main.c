#include "main.h"

void inline_asm(void);
void init(void);

void init(void)
{
	return;
}

int main(void)
{
	init();

	inline_asm();

	while(1);

	return 0;
}	

void inline_asm(void)
{
	unsigned char c;

	c = 0x00;

	PORTD = c;
	PORTA = ~PORTD;

	asm(	"	push	R24	;\n"
		"	push	R4	;\n"
		"	pop	R4	;\n"
		"	pop	R24       ");

	return;	
}
