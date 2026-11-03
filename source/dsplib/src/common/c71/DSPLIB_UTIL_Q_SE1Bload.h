/******************************************************************************/
/*!
 * \file DSPLIB_UTIL_Q_SE1Bload.h
 */
/* Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

#ifndef COMMON_DSPLIB_UTIL_Q_SE1BLOAD_H_
#define COMMON_DSPLIB_UTIL_Q_SE1BLOAD_H_ 1

/*******************************************************************************
 *
 * INCLUDES
 *
 ******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/*!
 * \ingroup dsplib_util_q
 * \brief   load numRows of B into the Bload buffer
 * \details use streaming engine 1 to load numRows of B into the Bload buffer
 * \param  numRows, vQFactor
 * \return  void
 */
/******************************************************************************/
__INLINE_FUNC(DSPLIB_UTIL_Q_SE1Bload)
template <uint32_t UNROLL_FACTOR> static inline void DSPLIB_UTIL_Q_SE1Bload(int32_t numRows, c7x::float_vec vQFactor)
{
   _nassert(numRows > 0);

   int32_t r;

   DSPLIB_UNROLL(UNROLL_FACTOR)
   /* Load numRows vectors into B panel */
   for (r = 0; r < numRows; r++) {

      /* Fetch B vector from SE1 into C7x register */
      c7x::float_vec vB = c7x::strm_eng<1, c7x::float_vec>::get_adv();

      /* Convert to Q */
      c7x::int_vec vBQ = __float_to_int((vB * vQFactor));

      /* Load B matrix panel with B vector */
      __HWALDB(c7x::reinterpret<__mma_vec>(vBQ));

      /* Advance HWA State Machine */
      __HWAADV();
   }

   return;
}
#endif /* COMMON_DSPLIB_UTIL_Q_SE1BLOAD_H_ */
