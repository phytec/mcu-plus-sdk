/******************************************************************************/
/*!
 * \file DSPLIB_UTIL_SE0AloadSE1BloadComputeCSA0Cstore.c
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

#ifndef COMMON_DSPLIB_UTIL_SE0ALOADSE1BLOADCOMPUTECSA0CSTORE_H_
#define COMMON_DSPLIB_UTIL_SE0ALOADSE1BLOADCOMPUTECSA0CSTORE_H_ 1

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
 * \param[in] cBackDst
 * \return  void
 */
/******************************************************************************/

__INLINE_FUNC(DSPLIB_UTIL_SE0AloadSE1BloadComputeCSA0Cstore)
template <typename dataType>
static inline void DSPLIB_UTIL_SE0AloadSE1BloadComputeCSA0Cstore(int32_t numRows, uint8_t cBackDst)
{

   _nassert(numRows > 0);

   int32_t r;

   typedef typename c7x::make_full_vector<dataType>::type vec;

   /* Load A and B vectors numRows times into respective MMA panels */
   for (r = 0; r < numRows; r++) {

      /* Fetch A vector from SE0 */
      vec vA = c7x::strm_eng<0, vec>::get_adv();

      /* Fetch B vector from SE1 */
      vec vB = c7x::strm_eng<1, vec>::get_adv();

      /* Load vA into A vector panel and vB into B matrix panel */
      HWALDAB(c7x::reinterpret<__mma_vec>(vA), c7x::reinterpret<__mma_vec>(vB));

      /* Compute C vector into C panel and move C back panel to transfer buffer */
      /* Perform OP with values from A panel, not ARF */
      HWAOPXFER(__MMA_A_LDA);

      /* Move Xfer buffer to VB0 */
      __mma_vec VB0 = __HWARCV((uint32_t) 0);

      /* Advance HWA State Machine */
      HWAADV();

      /* Store VB0 to memory via SA0 */
      __vpred pred = c7x::strm_agen<0, vec>::get_vpred();
      vec*    VB1  = c7x::strm_agen<0, vec>::get_adv(cBackDst);

      __vstore_pred(pred, VB1, c7x::reinterpret<vec>(VB0));
   }

   return;
}

#endif // COMMON_DSPLIB_UTIL_SE0ALOADSE1BLOADCOMPUTECSA0CSTORE_H_
