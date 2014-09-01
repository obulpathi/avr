#include <avr/io.h>
#include <avr/pgmspace.h>

#include "delay.h"
#include "delay.c"

const uint8_t data[] PROGMEM = { 0x01, 0x02, 0x03, 0x04 };

PGM_P array[1] PROGMEM = { data};

// expample for storing stirngs ... 
//const char foo[] PROGMEM = "Foo";
//PGM_P array[1] PROGMEM = { foo};

