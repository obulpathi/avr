/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief
 *      2nd order IIR filter demonstration
 *
 *      Program that demonstrates digital filtering on AVR devices using a
 *      2nd order band pass IIR filter with a Butterworth characteristic.\n
 *      The actual filter code is implemented in assembly, and resides in
 *      \ref 2nd_order_FIR.s90.\n
 *      This code was developed using IAR EWAVR C compiler v5.03A.
 *
 * \par Application note:
 *      AVR223: Digital Filters with AVR\n
 *
 * \par Memory usage:
 *      8 bytes SRAM for filter nodes (input and output samples).\n
 *      10 bytes SRAM for filter coefficients.
 *
 * \par Performance:
 *      Initialization: depends on compiler settings.\n
 *      Filtering: 94 instructions, 140 cycles (excluding ret)
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

//! Define the filter order for the IIR_filter struct.
#define FILTER_ORDER 2

/**********************************************************/
// Filter coefficients
/**********************************************************/
/* These coefficients will give the response of a Butterworth band pass filter.
 * A0 is not defined since it is the downscaling factor.
 *
 * Note that the sign is changed on the A*-coefficients, relative to the ones
 * presented in the appplication note. This is because only additions are used
 * in the filtering algorithm, while the difference equation requires
 * subtractions for the feedback-part.
 */
#define B0   280   //!< First feed-forward coefficient.
#define B1   0     //!< Second feed-forward coefficient.
#define B2   -280  //!< Third feed-forward coefficient.
#define A1   0     //!< Second feedback coefficient.
#define A2   -1488 //!< Third feedback coefficient.


/**********************************************************/
// Struct declarations
/**********************************************************/
//! Filter struct that holds coefficients and previous input samples.
struct IIR_filter{
    //! Memory nodes for previous input and output.
	   int filterNodes[FILTER_ORDER*2];
	   int filterCoefficients[(FILTER_ORDER*2)+1];  //!< Filter coefficients.
	   };


/**********************************************************/
// Globals
/**********************************************************/
  //! Buffer for filter output (40 samples).
  volatile int filterOutput[40];

  //! Correct impulse response, used for comparison.
  int impulseResponse[40] = {69, 0, -120, 0, 87, 0, -64, 0, 46, 0, -34, 0, 24,
                             0, -18, 0, 13, 0, -10, 0, 7, 0, -6, 0, 4, 0, -3,
                             0, 2, 0, -2, 0, 1, 0, -1, 0, 0, 0, 0, 0};

  // Initialize the filter struct.
  struct IIR_filter filter04_06 = {0,0,0,0, B0, B1, B2, A1, A2};
  
  //! Input signal (set to highest positive value for signed 10-bit integers).
  int filterInput = 511;

  
/**********************************************************/
// Function declarations
/**********************************************************/
//! The actual filtering function (resides in 2nd_order_IIR.s90).
extern int IIR2( struct IIR_filter *thisFilter, int newSample );


/**********************************************************/
// Main function
/**********************************************************/
void main(void)
{
  //! Flag for impulse response check. Start by assuming it is correct.
  bool correctResponse = true;

  // Feed input to the filter. (We use filterInput as an impulse.)
  filterOutput[0] = IIR2((struct IIR_filter*)&filter04_06, filterInput);

  // Fill the output buffer.
  int i;
  for (i = 1; i < 40; i++) {
    // Feed 0 to the filter, to get the filter's impulse response.
    filterOutput[i] = IIR2((struct IIR_filter*)&filter04_06, 0);
  }

  // Compare the filter output with the correct filter response.
  // Flag match/mismatch.
  for (i = 0; i < 40; i++) {
    if (filterOutput[i] != impulseResponse[i])
      correctResponse = false;
  }

  // Do nothing..
  for(;;){ }
}
