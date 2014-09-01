#include "main.h"

void init(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;

	tctr0_init();
	pwm2_init();

	return;
}

int main(void)
{
	unsigned char dc;

	init();


	//prog code
	while(1);

//	pwm2_set_duty_cycle(250);
	while(1)
	{
		for( dc = 200 ; dc > 10 ; dc-- )
		{
			pwm2_set_duty_cycle(dc);
			delay_ms(10);
		}

		delay_ms(2500);
	}

	while(1);

	return 0;
}	
