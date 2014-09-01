#include <avr/io.h>
#include <stdbool.h>

#include "dac.h"
#include "dac.c"

void init(void)
{
	PORTB.DIR = 0xFF;
	PORTB.OUT = 0x00;
	
	PORTQ.DIR = 0x08;
	PORTQ.OUT = 0x08;
}

int main( void )
{
	uint16_t angle;

	init();
	
	/*  Given 2 MHz CPU speed, this is configured to 2µs separation time and
	 *  16µs refresh time.
	 */
	DAC_DualChannel_Enable();

	init();

	/*  Use a 12 bit variable to output two triangle waves, separated by
	 *  180 degrees phase, as fast as possible. */
	 
	while (1) {
		for ( angle = 0; angle < 0x1000; ++angle ) {
			while ( DAC_Channel0_Ready() == false );
			/* Blocking code waiting for empty register. */
			DAC_Channel0_Write(angle);

			while ( DAC_Channel1_Ready()== false );
			/* Blocking code waiting for empty register. */
			DAC_Channel1_Write( 0xFFF - angle);
		}

		for ( angle = 0; angle < 0x1000; ++angle ) {
			while ( DAC_Channel0_Ready() == false );
			/* Blocking code waiting for empty register. */
			DAC_Channel0_Write(0xFFF - angle);

			while ( DAC_Channel1_Ready()== false );
			/* Blocking code waiting for empty register. */
			DAC_Channel1_Write(angle);
		}
	}
}
