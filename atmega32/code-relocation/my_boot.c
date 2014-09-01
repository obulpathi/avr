#include <avr/io.h>
#include "my_boot.h"

void my_boot(void)
{
		PORTD = ~ PORTD;

		return;
}
