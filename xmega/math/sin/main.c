#define F_CPU 2000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <math.h> 
#include <inttypes.h>

#define PI 3.14

void init(void)
{
	// allow power to stabilize
	_delay_ms(250);

	// port settings
	PORTE.DIR	 	= 0xFF;
	PORTE.OUT		= 0x00;

	return;
}

int main(void)
{
	double f = 10, n;
	double T = 0.001;
	double d;
	char c = 0

	d = 1.2345;

	init();

	n = 0;
	while(1)
	{
		//PORTE.OUT = sin(2 * PI * f * n *T);
		d = sin(d * n + 3.1234);
		c = (char) (d & ;
		PORTE.OUT = c;
		_delay_ms(500);
		n++;
	}

	// never die
	while(1);

	return 0;
}
