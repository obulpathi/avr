/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief
 *      4th order FIR filter demonstration
 *
 *      Program that demonstrates digital filtering on AVR devices using two
 *      cascaded 2nd order high pass FIR filters.\n
 *      The actual filter code is implemented in assembly, and resides in
 *      \ref 2nd_order_FIR.s90.\n
 *      This code was developed using IAR EWAVR C compiler v5.03A.
 *      Input samples are 10-bit signed, coefficients are 13-bit signed.
 *
 * \par Application note:
 *      AVR223: Digital Filters with AVR\n
 *
 * \par Memory usage:
 *      2*4 bytes SRAM for filter nodes (input samples).\n
 *      2*6 bytes SRAM for filter coefficients.
 *
 * \par Performance:
 *      Initialization: depends on compiler settings.\n
 *      Filtering (per filter): 60 instructions, 86 cycles (excluding ret)
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

/* ************************************************************************ *\

Copyright (c) 2008, Atmel Corporation All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

3. The name of ATMEL may not be used to endorse or promote products derived
from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY ATMEL ``AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

\* ************************************************************************ */

#include <stdbool.h>

//! Define the filter order for the FIR_filter struct.
#define FILTER_ORDER 2


/**********************************************************/
// Filter coefficients
/**********************************************************/
// HP filter with cut off at 0.4*(fs/2)
#define B10   -153  //!< First coefficient for filter 1.
#define B11   3790  //!< Second coefficient for filter 1.
#define B12   -153  //!< Third coefficient for filter 1.

// HP filter with cut off at 0.6*(fs/2)
#define B20   -222  //!< First coefficient for filter 2.
#define B21   3653  //!< Second coefficient for filter 2.
#define B22   -222  //!< Third coefficient for filter 2.


/**********************************************************/
// Struct declaration
/**********************************************************/
//! Filter struct that holds coefficients and previous input samples.
struct FIR_filter{
	   int filterNodes[FILTER_ORDER];			  //!< Memory nodes for previous input.
	   int filterCoefficients[(FILTER_ORDER)+1]; //!< Filter coefficients.
	   };


/**********************************************************/
// Globals
/**********************************************************/
  // Initialize the filter structs.
  struct FIR_filter
    filter04 = {0,0, B10, B11, B12},  //!< Filter No. 1.
    filter06 = {0,0, B20, B21, B22};  //!< Filter No. 2.

  //! Input signal (set to highest positive value for signed 10-bit integers).
  int filterInput = 511;

  //! Buffer for filter output (10 samples).
  volatile int filterOutput[10];

  //! Correct filter output, used for comparison.
  int impulseResponse[10] = {1, -44, 423, -44, 1, 0, 0, 0, 0, 0};


/**********************************************************/
// Function declarations
/**********************************************************/
//! The actual filtering function (resides in 2nd_order_FIR.s90).
extern int FIR2( struct FIR_filter *thisFilter, int newSample );


/**********************************************************/
// Main function
/**********************************************************/
void main(void)
{
  //! Flag for impulse response check. Start by assuming it is correct.
  bool correctResponse = true;

  // Feed input to the filter. (We use filterInput as an impulse.)
  filterOutput[0] = FIR2((struct FIR_filter*)&filter04, filterInput);
  // Cascade, feed output of first filter into the second.
  filterOutput[0] = FIR2((struct FIR_filter*)&filter06, filterOutput[0]);

  // Fill the filter output buffer.
  int i;
  for (i = 1; i < 10; i++) {
    // Feed input to the filter cascade.
    filterOutput[i] = FIR2((struct FIR_filter*)&filter04, 0);
    filterOutput[i] = FIR2((struct FIR_filter*)&filter06, filterOutput[i]);
  }

  // Compare the filter output with the correct filter response.
  // Flag match/mismatch.
  for (i = 0; i < 10; i++) {
    if (filterOutput[i] != impulseResponse[i])
      correctResponse = false;
  }

  // Do nothing..
  for(;;){ }
}
