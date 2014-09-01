#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0xFF;
	delay_ms(10000);
	
	RTC_Init();
	
	return;
}

int main(void)
{
	int i;

	init();

	delay_ms(1000);

	RTC_Start();
	delay_ms(100);

	while(1)
	{
		RTC_ReadSec();
		delay_ms(100);
	}
	
	while(1);

	return;
}
