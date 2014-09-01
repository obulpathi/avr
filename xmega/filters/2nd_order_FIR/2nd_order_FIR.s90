/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief
 *      2nd order FIR filter
 *
 *      Contains the assembly code for the 2nd order FIR filtering algorithm,
 *      which is called by the main program in FIR2.c\n
 *      The implementation is made so it can be used for different filters by
 *      passing the address of the filter struct, and input sample as arguments.\n
 *      Note that the filter structs should be initialized prior to calling the
 *      FIR2-function (the filter nodes should be initialized to zero).
 *      Input samples are 10-bit signed, coefficients are 13-bit signed.
 *
 * \par Application note:
 *      AVR223: Digital Filters with AVR\n
 *
 * \par Register usage:
 *      R0-4, R16-23, Z (All scratch/volatile registers)
 *      
 * \par Performance:
 *      Filtering: 60 instructions, 86 cycles (excluding ret)
 *
 * \par Documentation
 *      For comprehensive code documentation, supported compilers, compiler 
 *      settings and supported devices see readme.html
 *
 * \author
 *      Atmel Corporation: http://www.atmel.com \n
 *      Support email: avr@atmel.com
 *
 * 
 * $Name$
 * $Revision: 4187 $
 * $RCSfile$
 * $URL: $
 * $Date: 2008-07-15 15:22:38 +0200 (ti, 15 jul 2008) $
 ******************************************************************************/

 NAME	assembly(16)
 PUBLIC	FIR2
	RSEG	CODE

#include <ioavr.h>

//! ZERO register (used to add carry flag)
#define ZERO R2

// 24-bit accumulator.
#define AC2 R17  //!< High byte of accumulator.
#define AC1 R16  //!< Middle byte of accumulator.
#define AC0 R3   //!< Low byte of accumulator.

//! The first argument to the function is the (16-bit) address of the filter struct.
#define FILTER_POINTER r16

#define NDATAL R18  //!< Low byte of input sample passed as second argument.
#define NDATAH R19  //!< High byte of input sample passed as second argument.

#define DATAL R20  //!< Low byte of work register for samples.
#define DATAH R21  //!< High byte of work register for samples.

#define COEFL R22  //!< Low byte of work register for coefficients.
#define COEFH R23  //!< High byte of work register for coefficients.

// Memory offsets for the filter nodes in the filter struct.
#define X1  0*2  //!< Offset for first filter node.
#define X2  1*2  //!< Offset for second filter node.

// Memory offsets for the coefficients in the filter struct.
#define B0  2*2  //!< Offset for first filter coefficient.
#define B1  3*2  //!< Offset for second filter coefficient.
#define B2  4*2  //!< Offset for third filter coefficient.

/**************************************************/
// MACROS
/**************************************************/
LOAD_NODE MACRO
	ldd  DATAL, Z+\1    // Load low byte of node.
	ldd  DATAH, Z+\1+1  // Load high byte of node.
    ENDM


UPDATE_NODE MACRO
	std  Z+\1, DATAL    // Update low byte of node.
	std  Z+\1+1, DATAH  // Update high byte of node.
    ENDM


LOAD_COEF MACRO
	ldd  COEFL, Z+\1    // Load low byte of coefficient.
	ldd  COEFH, Z+\1+1  // Load high byte of coefficient.
    ENDM


MUL_MOV_24 MACRO
 // Multiply (signed) high bytes of both coefficient and sample work registers.
 // Then copy the resulting low byte into the accumulator's high byte
 // (sign bit will be correct).
	muls  COEFH, DATAH
	mov   AC2, R0

 // Multiply (unsigned) low bytes of the coefficient and sample work registers.
 // Copy the resulting high & low byte to the accumulator's low & middle bytes.
	mul  COEFL, DATAL
	mov  AC0, R0
	mov  AC1, R1
	
 // Multiply (signed-unsigned) high coefficient byte and low sample byte.
 // Add resulting low byte to accumulator's middle byte. (May generate carry!)
 // Add, with carry, resulting high byte to accumulator's high byte.
	mulsu  COEFH, DATAL
	add    AC1, R0
	adc    AC2, R1

 // Multiply (signed-unsigned) high sample byte and low coefficient byte.
 // Add resulting low byte to accumulator's middle byte. (May generate carry!)
 // Add, with carry, resulting high byte to accumulator's high byte.
	mulsu  DATAH, COEFL
	add    AC1, R0
	adc    AC2, R1
    ENDM


// SMAC_24 does the same thing as MUL_MOV_24 except it adds to the accumulator
// from the start, instead of overwriting.
SMAC_24 MACRO
	muls  COEFH, DATAH
	add   AC2, R0

	mul   COEFL, DATAL
	add   AC0, R0
	adc   AC1, R1    // This may generate a carry..
	adc   AC2, ZERO  // ..which must be added to accumulator's high byte!

	mulsu  COEFH, DATAL
	add    AC1, R0
	adc    AC2, R1

	mulsu  DATAH, COEFL
	add    AC1, R0
	adc    AC2, R1
    ENDM


/*****************************************************/
// FIR filter function
/****************************************************/
FIR2:
	clr   ZERO                // For safety, clear the ZERO register.
	movw  ZL, FILTER_POINTER  // Copy struct address to the Z-pointer.
	
// Calculate B2*x[n-2]
	LOAD_COEF B2
	LOAD_NODE X2
	MUL_MOV_24

// Calculate B1*x[n-1]
	LOAD_COEF   B1
	LOAD_NODE   X1
	UPDATE_NODE X2
	SMAC_24
	
// Calculate B0*x[n]
	LOAD_COEF   B0
	movw        DATAL, NDATAL  // For this coefficient, the new sample is used.
	UPDATE_NODE X1
	SMAC_24

// Due to the coefficient scaling by a factor 2^12, the output requires
// downscaling. Instead of right-shifting the 24-bit result 12 times, simply
// shift the 16 most significant bits (high and middle byte) 4 times.
	asr  AC2  // Arithmetic right-shift, preserves sign bit, LSB goes to carry.
	ror  AC1  // Binary rotation, carry is shifted into MSB.

	asr  AC2
	ror  AC1

	asr  AC2
	ror  AC1

	asr  AC2
	ror  AC1
	
// Return the value stored in the return registers R16 and R17, which happens
// to be AC1 and AC2; the middle and high byte of accumulator.
	ret
    
    END
