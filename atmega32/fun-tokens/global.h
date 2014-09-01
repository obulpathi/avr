#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

enum
{
  MAIN,
  INIT,
  FUN_TOKEN_ERROR,
} fun_token;
