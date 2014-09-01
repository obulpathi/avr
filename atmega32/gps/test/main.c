#include "main.h"

int main(void)
{
	// initialize GPS ...
	gps_init();
	// check gps
	gps_check();
	// read gps
	gps_read();
	
	while(1);

	return 0;
}
