#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;

	rtc_init();
	
	return;
}

int main(void)
{
	int i;

	init();

	rtc_start();
	delay_ms(1000);

	// write time to data reg's
	time[0] = 0;
	time[1] = 0;
	time[2] = 2;
	time[3] = 4;
	time[4] = 2;
	time[5] = 3;

	date[0] = 0;	
	date[0] = 0;	
	date[0] = 0;	
	date[0] = 0;	
	date[0] = 0;	
	date[0] = 0;	
	
	rtc_set_time();

	rtc_read_time();
	
	PORTD = 0xFF;
	while(1);

	while(1)
	{
		rtc_read_time();
		PORTD = time[4];
	}
	
	while(1);

	return;
}
