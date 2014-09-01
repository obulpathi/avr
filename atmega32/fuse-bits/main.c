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

	//prog code
	PORTD = boot_lock_fuse_bits_get( GET_LOW_FUSE_BITS );

	while(1);

	return 0;
}	
