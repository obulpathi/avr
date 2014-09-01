;; begin xram.S

#include <avr/io.h>

  .section .init1,"ax",@progbits

  ldi r16,_BV(SRE) | _BV(SRW)
  out _SFR_IO_ADDR(MCUCR),r16

;; end xram.S
