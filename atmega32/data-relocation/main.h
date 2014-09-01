#include <avr/io.h>

#include "delay.h"
#include "delay.c"

#define ARRAY __attribute__ ((section (".array")))

const unsigned char data[] ARRAY = {0x01, 0x02, 0x03, 0x04};

/*
Of course AVRGCC doesn’t support such commands but there are another way – Use memory sections. Using them is not very hard.

The memory space “seen” by AVRGCC runs from addresses:

…………………………………………………………………

0×00000000 up to 0×0007FFFF for Flash memory,
0×00800000 up to 0×0080FFFF for RAM, and
0×00810000 up to 0×0081FFFF for EEPROM. */
