/******************************************************************************/
/*!
 * \file DSPLIB_UTIL_Q_SE0AloadSE1BloadComputeCSA0Cstore.c
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

#ifndef COMMON_DSPLIB_UTIL_Q_SE0ALOADSE1BLOADCOMPUTECSA0CSTORE_H_
#define COMMON_DSPLIB_UTIL_Q_SE0ALOADSE1BLOADCOMPUTECSA0CSTORE_H_ 1

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

__INLINE_FUNC(DSPLIB_UTIL_Q_SE0AloadSE1BloadComputeCSA0CstoreUnroll3)
static inline void
DSPLIB_UTIL_Q_SE0AloadSE1BloadComputeCSA0CstoreUnroll3(int32_t numRows, c7x::float_vec vQFactor, float *cBackDst)
{

   _nassert(numRows > 0);

   int32_t        r;
   c7x::float_vec vRQFactor = __recip(vQFactor);

   int32_t numRowsUnroll = DSPLIB_ceilingDiv(numRows, 3);

   /* Load A and B vectors numRows times into respective MMA panels */
   for (r = 0; r < numRowsUnroll; r++) {

      /* Fetch A vector from SE0 */
      c7x::float_vec vA_0 = c7x::strm_eng<0, c7x::float_vec>::get_adv();

      /*Convert to Q Format */
      c7x::int_vec vAQ_0 = __float_to_int((vA_0 * vQFactor));

      /* Fetch B vector from SE1 */
      c7x::float_vec vB_0 = c7x::strm_eng<1, c7x::float_vec>::get_adv();

      /*Convert to Q Format */
      c7x::int_vec vBQ_0 = __float_to_int((vB_0 * vQFactor));

      /* Load vA into A vector panel and vB into B matrix panel */
      __HWALDAB(c7x::reinterpret<__mma_vec>(vAQ_0), c7x::reinterpret<__mma_vec>(vBQ_0));

      /* Compute C vector into C panel and move C back panel to transfer buffer */
      /* Perform OP with values from A panel, not ARF */
      __HWAOPXFER(__MMA_A_LDA);

      /* Move Xfer buffer contents to C7x register VB0 */
      __mma_vec VB0_0 = __HWARCV((uint32_t) 0);

      c7x::float_vec VB0sp_0   = __int_to_float(c7x::reinterpret<c7x::int_vec>(VB0_0));
      c7x::float_vec vResult_0 = VB0sp_0 * vRQFactor;

      /* Advance HWA State Machine */
      __HWAADV();

      /* Store VB0 to memory via SA0 */
      __vpred         pred_0 = c7x::strm_agen<0, c7x::float_vec>::get_vpred();
      c7x::float_vec *VB1_0  = c7x::strm_agen<0, c7x::float_vec>::get_adv(cBackDst);

      __vstore_pred(pred_0, VB1_0, c7x::reinterpret<c7x::float_vec>(vResult_0));

      /* Fetch A vector from SE0 */
      c7x::float_vec vA_1 = c7x::strm_eng<0, c7x::float_vec>::get_adv();

      /*Convert to Q Format */
      c7x::int_vec vAQ_1 = __float_to_int((vA_1 * vQFactor));

      /* Fetch B vector from SE1 */
      c7x::float_vec vB_1 = c7x::strm_eng<1, c7x::float_vec>::get_adv();

      /*Convert to Q Format */
      c7x::int_vec vBQ_1 = __float_to_int((vB_1 * vQFactor));

      /* Load vA into A vector panel and vB into B matrix panel */
      __HWALDAB(c7x::reinterpret<__mma_vec>(vAQ_1), c7x::reinterpret<__mma_vec>(vBQ_1));

      /* Compute C vector into C panel and move C back panel to transfer buffer */
      /* Perform OP with values from A panel, not ARF */
      __HWAOPXFER(__MMA_A_LDA);

      /* Move Xfer buffer contents to C7x register VB0 */
      __mma_vec VB0_1 = __HWARCV((uint32_t) 0);

      c7x::float_vec VB0sp_1   = __int_to_float(c7x::reinterpret<c7x::int_vec>(VB0_1));
      c7x::float_vec vResult_1 = VB0sp_1 * vRQFactor;

      /* Advance HWA State Machine */
      __HWAADV();

      /* Store VB0 to memory via SA0 */
      __vpred         pred_1 = c7x::strm_agen<0, c7x::float_vec>::get_vpred();
      c7x::float_vec *VB1_1  = c7x::strm_agen<0, c7x::float_vec>::get_adv(cBackDst);

      __vstore_pred(pred_1, VB1_1, c7x::reinterpret<c7x::float_vec>(vResult_1));

      /* Fetch A vector from SE0 */
      c7x::float_vec vA_2 = c7x::strm_eng<0, c7x::float_vec>::get_adv();

      /*Convert to Q Format */
      c7x::int_vec vAQ_2 = __float_to_int((vA_2 * vQFactor));

      /* Fetch B vector from SE1 */
      c7x::float_vec vB_2 = c7x::strm_eng<1, c7x::float_vec>::get_adv();

      /*Convert to Q Format */
      c7x::int_vec vBQ_2 = __float_to_int((vB_2 * vQFactor));

      /* Load vA into A vector panel and vB into B matrix panel */
      __HWALDAB(c7x::reinterpret<__mma_vec>(vAQ_2), c7x::reinterpret<__mma_vec>(vBQ_2));

      /* Compute C vector into C panel and move C back panel to transfer buffer */
      /* Perform OP with values from A panel, not ARF */
      __HWAOPXFER(__MMA_A_LDA);

      /* Move Xfer buffer contents to C7x register VB0 */
      __mma_vec VB0_2 = __HWARCV((uint32_t) 0);

      c7x::float_vec VB0sp_2   = __int_to_float(c7x::reinterpret<c7x::int_vec>(VB0_2));
      c7x::float_vec vResult_2 = VB0sp_2 * vRQFactor;

      /* Advance HWA State Machine */
      __HWAADV();

      /* Store VB0 to memory via SA0 */
      __vpred         pred_2 = c7x::strm_agen<0, c7x::float_vec>::get_vpred();
      c7x::float_vec *VB1_2  = c7x::strm_agen<0, c7x::float_vec>::get_adv(cBackDst);

      __vstore_pred(pred_2, VB1_2, c7x::reinterpret<c7x::float_vec>(vResult_2));
   }

   return;
}

#endif // COMMON_DSPLIB_UTIL_Q_SE0ALOADSE1BLOADCOMPUTECSA0CSTORE_H_
