#include "sscf.h"

void sscf( unsigned char xdiv)
{
	// disable sscf
	XDIV = 0x00;
	// scale the freequency.
	XDIV = xdiv;
	// enable sscf
	XDIV = XDIV | 0x80;
		
	return;
}
