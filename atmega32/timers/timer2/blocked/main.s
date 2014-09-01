	.file	"main.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__tmp_reg__ = 0
__zero_reg__ = 1
	.global __do_copy_data
	.global __do_clear_bss
	.stabs	"/media/sda4/code/atmel/atmega32/timers/timer0/blocked/",100,0,2,.Ltext0
	.stabs	"main.c",100,0,2,.Ltext0
	.text
.Ltext0:
	.stabs	"gcc2_compiled.",60,0,0,0
	.stabs	"int:t(0,1)=r(0,1);-32768;32767;",128,0,0,0
	.stabs	"char:t(0,2)=r(0,2);0;127;",128,0,0,0
	.stabs	"long int:t(0,3)=@s32;r(0,3);020000000000;017777777777;",128,0,0,0
	.stabs	"unsigned int:t(0,4)=r(0,4);0;0177777;",128,0,0,0
	.stabs	"long unsigned int:t(0,5)=@s32;r(0,5);0;037777777777;",128,0,0,0
	.stabs	"long long int:t(0,6)=@s64;r(0,6);01000000000000000000000;0777777777777777777777;",128,0,0,0
	.stabs	"long long unsigned int:t(0,7)=@s64;r(0,7);0;01777777777777777777777;",128,0,0,0
	.stabs	"short int:t(0,8)=r(0,8);-32768;32767;",128,0,0,0
	.stabs	"short unsigned int:t(0,9)=r(0,9);0;0177777;",128,0,0,0
	.stabs	"signed char:t(0,10)=@s8;r(0,10);-128;127;",128,0,0,0
	.stabs	"unsigned char:t(0,11)=@s8;r(0,11);0;255;",128,0,0,0
	.stabs	"float:t(0,12)=r(0,1);4;0;",128,0,0,0
	.stabs	"double:t(0,13)=r(0,1);4;0;",128,0,0,0
	.stabs	"long double:t(0,14)=r(0,1);4;0;",128,0,0,0
	.stabs	"void:t(0,15)=(0,15)",128,0,0,0
	.stabs	"main.h",130,0,0,0
	.stabs	"/usr/local/lib/gcc/avr/4.2.1/../../../../avr/include/avr/io.h",130,0,0,0
	.stabs	"/usr/local/lib/gcc/avr/4.2.1/../../../../avr/include/avr/sfr_defs.h",130,0,0,0
	.stabs	"/usr/local/lib/gcc/avr/4.2.1/../../../../avr/include/inttypes.h",130,0,0,0
	.stabs	"/usr/local/lib/gcc/avr/4.2.1/../../../../avr/include/stdint.h",130,0,0,0
	.stabs	"int8_t:t(5,1)=(0,10)",128,0,116,0
	.stabs	"uint8_t:t(5,2)=(0,11)",128,0,117,0
	.stabs	"int16_t:t(5,3)=(0,1)",128,0,118,0
	.stabs	"uint16_t:t(5,4)=(0,4)",128,0,119,0
	.stabs	"int32_t:t(5,5)=(0,3)",128,0,120,0
	.stabs	"uint32_t:t(5,6)=(0,5)",128,0,121,0
	.stabs	"int64_t:t(5,7)=(0,6)",128,0,122,0
	.stabs	"uint64_t:t(5,8)=(0,7)",128,0,123,0
	.stabs	"intptr_t:t(5,9)=(5,3)",128,0,135,0
	.stabs	"uintptr_t:t(5,10)=(5,4)",128,0,140,0
	.stabs	"int_least8_t:t(5,11)=(5,1)",128,0,152,0
	.stabs	"uint_least8_t:t(5,12)=(5,2)",128,0,157,0
	.stabs	"int_least16_t:t(5,13)=(5,3)",128,0,162,0
	.stabs	"uint_least16_t:t(5,14)=(5,4)",128,0,167,0
	.stabs	"int_least32_t:t(5,15)=(5,5)",128,0,172,0
	.stabs	"uint_least32_t:t(5,16)=(5,6)",128,0,177,0
	.stabs	"int_least64_t:t(5,17)=(5,7)",128,0,182,0
	.stabs	"uint_least64_t:t(5,18)=(5,8)",128,0,187,0
	.stabs	"int_fast8_t:t(5,19)=(5,1)",128,0,200,0
	.stabs	"uint_fast8_t:t(5,20)=(5,2)",128,0,205,0
	.stabs	"int_fast16_t:t(5,21)=(5,3)",128,0,210,0
	.stabs	"uint_fast16_t:t(5,22)=(5,4)",128,0,215,0
	.stabs	"int_fast32_t:t(5,23)=(5,5)",128,0,220,0
	.stabs	"uint_fast32_t:t(5,24)=(5,6)",128,0,225,0
	.stabs	"int_fast64_t:t(5,25)=(5,7)",128,0,230,0
	.stabs	"uint_fast64_t:t(5,26)=(5,8)",128,0,235,0
	.stabs	"intmax_t:t(5,27)=(5,7)",128,0,249,0
	.stabs	"uintmax_t:t(5,28)=(5,8)",128,0,254,0
	.stabn	162,0,0,0
	.stabs	"int_farptr_t:t(4,1)=(5,5)",128,0,76,0
	.stabs	"uint_farptr_t:t(4,2)=(5,6)",128,0,80,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.stabs	"init:F(0,15)",36,0,4,init
.global	init
	.type	init, @function
init:
	.stabd	46,0,0
	.stabn	68,0,4,.LM0-.LFBB1
.LM0:
.LFBB1:
/* prologue: frame size=0 */
/* prologue end (size=0) */
	.stabn	68,0,5,.LM1-.LFBB1
.LM1:
	ldi r24,lo8(-1)
	out 49-0x20,r24
	.stabn	68,0,6,.LM2-.LFBB1
.LM2:
	ldi r24,lo8(-86)
	out 50-0x20,r24
	.stabn	68,0,8,.LM3-.LFBB1
.LM3:
	call tctr0_init
/* epilogue: frame size=0 */
	ret
/* epilogue end (size=1) */
/* function init size 7 (6) */
	.size	init, .-init
.Lscope1:
	.stabs	"",36,0,0,.Lscope1-.LFBB1
	.stabd	78,0,0
	.stabs	"main:F(0,1)",36,0,14,main
.global	main
	.type	main, @function
main:
	.stabd	46,0,0
	.stabn	68,0,14,.LM4-.LFBB2
.LM4:
.LFBB2:
/* prologue: frame size=0 */
	ldi r28,lo8(__stack - 0)
	ldi r29,hi8(__stack - 0)
	out __SP_H__,r29
	out __SP_L__,r28
/* prologue end (size=4) */
	.stabn	68,0,15,.LM5-.LFBB2
.LM5:
	call init
.L4:
	.stabn	68,0,19,.LM6-.LFBB2
.LM6:
	in r24,50-0x20
	com r24
	out 50-0x20,r24
	.stabn	68,0,20,.LM7-.LFBB2
.LM7:
	ldi r24,lo8(1000)
	ldi r25,hi8(1000)
	call delay_us
	rjmp .L4
/* epilogue: frame size=0 */
/* epilogue: noreturn */
/* epilogue end (size=0) */
/* function main size 14 (10) */
	.size	main, .-main
.Lscope2:
	.stabs	"",36,0,0,.Lscope2-.LFBB2
	.stabd	78,0,0
	.stabs	"",100,0,0,.Letext0
.Letext0:
/* File "main.c": code   21 = 0x0015 (  16), prologues   4, epilogues   1 */
