#include "blink.h"

int main(void)
{
	blink();

	for(int i =0; i < 10; i++)
		nop();
	
	return 0;
}
