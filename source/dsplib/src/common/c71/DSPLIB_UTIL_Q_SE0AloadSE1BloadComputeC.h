/******************************************************************************/
/*!
 * \file DSPLIB_UTIL_Q_SE0AloadSE1BloadComputeC.c
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

#ifndef COMMON_DSPLIB_UTIL_Q_SE0ALOADSE1BLOADCOMPUTEC_H_
#define COMMON_DSPLIB_UTIL_Q_SE0ALOADSE1BLOADCOMPUTEC_H_ 1

/*******************************************************************************
 *
 * INCLUDES
 *
 ******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/*!
 * \ingroup dsplib_util
 * \brief
 * \details
 * \param[in] numRows
 * \return  void
 */
/******************************************************************************/

__INLINE_FUNC(DSPLIB_UTIL_Q_SE0AloadSE1BloadComputeC)
template <uint32_t UNROLL_FACTOR>
static inline void DSPLIB_UTIL_Q_SE0AloadSE1BloadComputeC(int32_t numRows, c7x::float_vec vQFactor)
{

   _nassert(numRows > 0);

   int32_t r;

   DSPLIB_UNROLL(UNROLL_FACTOR)
   /* Load A and B vectors numRows times into respective MMA panels */
   for (r = 0; r < numRows; r++) {

      /* Fetch A vector from SE0 */
      c7x::float_vec vA = c7x::strm_eng<0, c7x::float_vec>::get_adv();

      /*Convert to Q Format */
      c7x::int_vec vAQ = __float_to_int((vA * vQFactor));

      /* Fetch B vector from SE1 */
      c7x::float_vec vB = c7x::strm_eng<1, c7x::float_vec>::get_adv();

      /*Convert to Q Format */
      c7x::int_vec vBQ = __float_to_int((vB * vQFactor));

      /* Load vA into A vector panel and vB into B matrix panel */
      __HWALDAB(c7x::reinterpret<__mma_vec>(vAQ), c7x::reinterpret<__mma_vec>(vBQ));

      /* Compute C vector into C panel */
      /* Perform OP with values from A panel, not ARF */
      __HWAOP(__MMA_A_LDA);

      /* Advance HWA State Machine */
      __HWAADV();
   }

   return;
}

#endif // COMMON_DSPLIB_UTIL_Q_SE0ALOADSE1BLOADCOMPUTEC_H_
