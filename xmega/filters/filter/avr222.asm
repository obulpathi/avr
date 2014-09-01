;**** A P P L I C A T I O N   N O T E   A V R 2 2 2 ************************
;*
;* Title:		8-Point Moving Average Filter
;* Version:		1.0
;* Last updated:	97.07.04
;* Target:		AT90Sxx1x (Devices with SRAM)
;*
;* Support E-mail:	avr@atmel.com
;*
;* DESCRIPTION
;* This Application note shows an implementation of an 8-point Moving
;* Average (MAV) filter. The program filters a data array containing SIZE
;* elements starting at T_START. The App. note contains a test
;* program which copies a 60-byte block of data from program memory to 
;* SRAM and filters the data. Note that the ends of the data array are not
;* filtered.
;* 
;***************************************************************************

.include "8515def.inc"

.equ	SIZE	=60		;data array size
.equ	TABLE_L	=$60		;Low SRAM address of first data element
.equ	TABLE_H =$00		;High SRAM address of first data element

	rjmp	RESET		;Reset Handle

;***************************************************************************
;*
;* "mav8"
;*
;* This subroutine filters SIZE bytes with the first element in SRAM
;* location T_START. The filter routine uses an 8-byte ring buffer which
;* occupies working registers r0-r7. As filtering progresses, this ring 
;* buffer always contains the 8-byte window to be averaged.
;*
;* Number of words	:31 + return
;* Number of cycles	:59 + (SIZE-7)*75 + return
;* Low registers used	:11 (r0-r7,mav_tmp,AL,AH)
;* High registers used	:1 (t_size)
;* Pointers used	:X,Y,Z
;*
;***************************************************************************

;***** Subroutine Register Variables

.def	mav_tmp	=r8			;temprary storage register
.def	AL	=r9			;ring buffer sum, low byte
.def	AH	=r10			;ring buffer sum, high byte
.def	t_size	=r16			;size of table

;***** Code

mav8:
	clr	YH
	clr	YL			;init pointers
	clr	XH
	clr	XL

;***** Fill ring buffer with first-8 byte data segment

mav8_1:	ld	mav_tmp,Z+		;get SRAM data
	st	Y+,mav_tmp		;store in register
	cpi	YL,8			;got all?
	brne	mav8_1			;if not, loop more
	sbiw	ZL,5			;Z points to first value to filter

mav8_2:
;***** Find average
	clr	AH			;Clear avg High byte
	clr	AL			;Clear avg Low byte
	clr	YL			;init Y-pointer
mav8_3:	ld	mav_tmp,Y+		;
	add	AL,mav_tmp		;add value to AL
	adc	AH,XH			;add carry to AH (XH is zero)
	cpi	YL,8			;added all ?
	brne	mav8_3			;if not, loop again	
	lsr	AH			;divide by 8
	ror	AL			;
	lsr	AH			;
	ror	AL			;
	lsr	AH			;
	ror	AL			;
	ldd	mav_tmp,Z+5		;get next value to buffer
	st	X+,mav_tmp		;store to buffer
	andi	XL,$07			;mask away pointer upper bits
	st	Z+,AL			;store average
	dec	t_size
	cpi	t_size,4		;end of array?
	brne	mav8_2			;if not, loop more	
	ret

;***************************************************************************
;*
;* Test Program
;*
;* This program copies 60 bytes of data from  Program memory to SRAM. It 
;* then calls "mav8" to get the data filtered.
;*
;***************************************************************************

RESET:

;***** Main program Register variables

.def	temp	=r16

;***** Code

	ldi	temp,low(RAMEND)
	out	SPL,temp
	ldi	temp,high(RAMEND)
	out	SPH,temp	;init Stack Pointer

;***** Memory fill
	
	clr	ZH
	ldi	ZL,tableend*2+1	;Z-pointer <- ROM table end + 1
	ldi	YL,low(256*TABLE_H+TABLE_L+SIZE)
	ldi	YH,high(256*TABLE_H+TABLE_L+SIZE)	
				;Y pointer <- SRAM table end + 1
loop:	lpm			;get ROM constant
	st	-Y,r0		;store in SRAM and decrement Y-pointer
	sbiw	ZL,1		;decrement Z-pointer
	cpi	YL,TABLE_L	;if not done
	brne	loop		;    loop more
	cpi	YH,TABLE_H
	brne	loop

;***** Filter data

	ldi	ZL,TABLE_L
	ldi	ZH,TABLE_H
	ldi	T_size,SIZE
	rcall	mav8

forever:rjmp	forever	



;***** 60 ROM Constants

table:
.db	120,196
.db	78,216
.db	78,100
.db	43,39
.db	241,43
.db	62,172
.db	109,69
.db	48,184
.db	215,231
.db	63,133
.db	216,8
.db	121,126
.db	188,98
.db	168,205
.db	157,172
.db	108,233
.db	80,255
.db	252,102
.db	198,0
.db	171,239
.db	107,114
.db	172,170
.db	17,45
.db	42,55
.db	34,174
.db	229,250
.db	12,179
.db	187,243
.db	44,231
tableend:
.db	76,48

