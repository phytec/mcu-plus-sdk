
/******************************************************************************/
/*!
 * \file DSPLIB_svd_small_v_process.h
 */
/* Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/
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

/******************************************************************************
 * Version 1.0  Date Aug 2023      Author: Asheesh Bhardwaj
 *****************************************************************************/

/*******************************************************************************
 *
 * INCLUDES
 *
 ******************************************************************************/

#include "DSPLIB_svd_small_priv.h"

/* *****************************************************************************
 *
 * IMPLEMENTATION
 *
 ***************************************************************************** */
#if (__C7X_VEC_SIZE_BITS__ == 512)


template <typename dataType> static inline void v_process_1st_iter(dataType *U,
                                                                   dataType *V,
                                                                   const int colUStride,
                                                                   const int colVStride,
                                                                   dataType *s);
template <> inline void v_process_1st_iter<float>(float *U,
                                                  float *V,
                                                  const int colUStride,
                                                  const int colVStride,
                                                  float *s)
{
  return;
}
template <> inline void v_process_1st_iter<double>(double *U,
                                                   double *V,
                                                   const int colUStride,
                                                   const int colVStride,
                                                   double *s)
{
   /* -------------------------------------------------- */
   /* For i = 1 */
   /* -------------------------------------------------- */
   {
      typedef typename c7x::make_full_vector<double>::type vec;
      __vpred pred_2_elem = __create_vpred(0x000000000000FFFFU);
      __vpred pred_2_elem_u = __create_vpred(0x000000000000FF00U);


      vec vec_top_row = (vec)0.0;
      vec_top_row.s[0] = 1.0;

      vec vec_in0 = __vload_pred(pred_2_elem_u, (vec *)&V[0 + 1 * colVStride]);

      vec vec_u_row = __vload_pred(pred_2_elem_u, (vec *)U);

      double normFactor = vec_u_row.s[1] * (*s);
      vec vec_invNorm    = (vec)getRecip(normFactor);

      vec vec_v_col = vec_u_row * vec_invNorm;

      vec vec_si = (vec)0.0;
      vec_si += vec_u_row * vec_in0;

      vec_in0 += vec_si * vec_v_col;

      __vstore_pred(pred_2_elem, (vec *)&V[0 + 0 * colVStride], vec_top_row);
      __vstore_pred(pred_2_elem, (vec *)&V[0 + 1 * colVStride], vec_in0);
   }
  return;
}





template <typename dataType> static inline void v_process_2nd_iter(dataType *U,
                                                                   dataType *V,
                                                                   const int colUStride,
                                                                   const int colVStride,
                                                                   dataType *s);
template <> inline void v_process_2nd_iter<float>(float *U,
                                                  float *V,
                                                  const int colUStride,
                                                  const int colVStride,
                                                  float *s)
{
  return;
}
template <> inline void v_process_2nd_iter<double>(double *U,
                                                   double *V,
                                                   const int colUStride,
                                                   const int colVStride,
                                                   double *s)
{
   /* -------------------------------------------------- */
   /* For i = 2 */
   /* -------------------------------------------------- */
   {
      typedef typename c7x::make_full_vector<double>::type vec;
      __vpred pred_3_elem = __create_vpred(0x0000000000FFFFFFU);
      __vpred pred_3_elem_u = __create_vpred(0x0000000000FFFF00U);


      vec vec_top_row = (vec)0.0;
      vec_top_row.s[0] = 1.0;

      vec vec_in0 = __vload_pred(pred_3_elem_u, (vec *)&V[0 + 1 * colVStride]);
      vec vec_in1 = __vload_pred(pred_3_elem_u, (vec *)&V[0 + 2 * colVStride]);

      vec vec_u_row = __vload_pred(pred_3_elem_u, (vec *)U);

      double normFactor = vec_u_row.s[1] * (*s);
      vec vec_invNorm    = (vec)getRecip(normFactor);

      vec vec_v_col = vec_u_row * vec_invNorm;

      vec vec_si = (vec)0.0;
      vec_si += vec_u_row.s[1] * vec_in0;
      vec_si += vec_u_row.s[2] * vec_in1;

      vec_in0 += vec_si * vec_v_col.s[1];
      vec_in1 += vec_si * vec_v_col.s[2];

      __vstore_pred(pred_3_elem, (vec *)&V[0 + 0 * colVStride], vec_top_row);
      __vstore_pred(pred_3_elem, (vec *)&V[0 + 1 * colVStride], vec_in0);
      __vstore_pred(pred_3_elem, (vec *)&V[0 + 2 * colVStride], vec_in1);


   }
  return;
}



template <typename dataType> static inline void v_process_3rd_iter(dataType *U,
                                                                   dataType *V,
                                                                   const int colUStride,
                                                                   const int colVStride,
                                                                   dataType *s);
template <> inline void v_process_3rd_iter<float>(float *U,
                                                  float *V,
                                                  const int colUStride,
                                                  const int colVStride,
                                                  float *s)
{
  return;
}
template <> inline void v_process_3rd_iter<double>(double *U,
                                                   double *V,
                                                   const int colUStride,
                                                   const int colVStride,
                                                   double *s)
{
   /* -------------------------------------------------- */
   /* For i = 3 */
   /* -------------------------------------------------- */
   {
      typedef typename c7x::make_full_vector<double>::type vec;
      __vpred pred_4_elem = __create_vpred(0x00000000FFFFFFFFU);
      __vpred pred_4_elem_u = __create_vpred(0x00000000FFFFFF00U);


      vec vec_top_row = (vec)0.0;
      vec_top_row.s[0] = 1.0;

      vec vec_in0 = __vload_pred(pred_4_elem_u, (vec *)&V[0 + 1 * colVStride]);
      vec vec_in1 = __vload_pred(pred_4_elem_u, (vec *)&V[0 + 2 * colVStride]);
      vec vec_in2 = __vload_pred(pred_4_elem_u, (vec *)&V[0 + 3 * colVStride]);

      vec vec_u_row = __vload_pred(pred_4_elem_u, (vec *)U);

      double normFactor = vec_u_row.s[1] * (*s);
      vec vec_invNorm    = (vec)getRecip(normFactor);

      vec vec_v_col = vec_u_row * vec_invNorm;

      vec vec_si = (vec)0.0;
      vec_si += vec_u_row.s[1] * vec_in0;
      vec_si += vec_u_row.s[2] * vec_in1;
      vec_si += vec_u_row.s[3] * vec_in2;

      vec_in0 += vec_si * vec_v_col.s[1];
      vec_in1 += vec_si * vec_v_col.s[2];
      vec_in2 += vec_si * vec_v_col.s[3];


      __vstore_pred(pred_4_elem, (vec *)&V[0 + 0 * colVStride], vec_top_row);
      __vstore_pred(pred_4_elem, (vec *)&V[0 + 1 * colVStride], vec_in0);
      __vstore_pred(pred_4_elem, (vec *)&V[0 + 2 * colVStride], vec_in1);
      __vstore_pred(pred_4_elem, (vec *)&V[0 + 3 * colVStride], vec_in2);

   }
  return;
}


template <typename dataType> static inline void v_process_4th_iter(dataType *U,
                                                                   dataType *V,
                                                                   const int colUStride,
                                                                   const int colVStride,
                                                                   dataType *s);
template <> inline void v_process_4th_iter<float>(float *U,
                                                  float *V,
                                                  const int colUStride,
                                                  const int colVStride,
                                                  float *s)
{
  return;
}
template <> inline void v_process_4th_iter<double>(double *U,
                                                   double *V,
                                                   const int colUStride,
                                                   const int colVStride,
                                                   double *s)
{
   /* -------------------------------------------------- */
   /* For i = 4 */
   /* -------------------------------------------------- */
   {
      typedef typename c7x::make_full_vector<double>::type vec;
      __vpred pred_5_elem = __create_vpred(0x000000FFFFFFFFFFU);
      __vpred pred_5_elem_u = __create_vpred(0x000000FFFFFFFF00U);


      vec vec_top_row = (vec)0.0;
      vec_top_row.s[0] = 1.0;

      vec vec_in0 = __vload_pred(pred_5_elem_u, (vec *)&V[0 + 1 * colVStride]);
      vec vec_in1 = __vload_pred(pred_5_elem_u, (vec *)&V[0 + 2 * colVStride]);
      vec vec_in2 = __vload_pred(pred_5_elem_u, (vec *)&V[0 + 3 * colVStride]);
      vec vec_in3 = __vload_pred(pred_5_elem_u, (vec *)&V[0 + 4 * colVStride]);

      vec vec_u_row = __vload_pred(pred_5_elem_u, (vec *)U);

      double normFactor = vec_u_row.s[1] * (*s);
      vec vec_invNorm    = (vec)getRecip(normFactor);

      vec vec_v_col = vec_u_row * vec_invNorm;

      vec vec_si = (vec)0.0;
      vec_si += vec_u_row.s[1] * vec_in0;
      vec_si += vec_u_row.s[2] * vec_in1;
      vec_si += vec_u_row.s[3] * vec_in2;
      vec_si += vec_u_row.s[4] * vec_in3;

      vec_in0 += vec_si * vec_v_col.s[1];
      vec_in1 += vec_si * vec_v_col.s[2];
      vec_in2 += vec_si * vec_v_col.s[3];
      vec_in3 += vec_si * vec_v_col.s[4];


      __vstore_pred(pred_5_elem, (vec *)&V[0 + 0 * colVStride], vec_top_row);
      __vstore_pred(pred_5_elem, (vec *)&V[0 + 1 * colVStride], vec_in0);
      __vstore_pred(pred_5_elem, (vec *)&V[0 + 2 * colVStride], vec_in1);
      __vstore_pred(pred_5_elem, (vec *)&V[0 + 3 * colVStride], vec_in2);
      __vstore_pred(pred_5_elem, (vec *)&V[0 + 4 * colVStride], vec_in3);

   }
  return;
}




template <typename dataType> static inline void v_process_5th_iter(dataType *U,
                                                                   dataType *V,
                                                                   const int colUStride,
                                                                   const int colVStride,
                                                                   dataType *s);
template <> inline void v_process_5th_iter<float>(float *U,
                                                  float *V,
                                                  const int colUStride,
                                                  const int colVStride,
                                                  float *s)
{
  return;
}
template <> inline void v_process_5th_iter<double>(double *U,
                                                   double *V,
                                                   const int colUStride,
                                                   const int colVStride,
                                                   double *s)
{
   /* -------------------------------------------------- */
   /* For i = 5 */
   /* -------------------------------------------------- */
   {
      typedef typename c7x::make_full_vector<double>::type vec;
      __vpred pred_6_elem = __create_vpred(0x0000FFFFFFFFFFFFU);
      __vpred pred_6_elem_u = __create_vpred(0x0000FFFFFFFFFF00U);


      vec vec_top_row = (vec)0.0;
      vec_top_row.s[0] = 1.0;

      vec vec_in0 = __vload_pred(pred_6_elem_u, (vec *)&V[0 + 1 * colVStride]);
      vec vec_in1 = __vload_pred(pred_6_elem_u, (vec *)&V[0 + 2 * colVStride]);
      vec vec_in2 = __vload_pred(pred_6_elem_u, (vec *)&V[0 + 3 * colVStride]);
      vec vec_in3 = __vload_pred(pred_6_elem_u, (vec *)&V[0 + 4 * colVStride]);
      vec vec_in4 = __vload_pred(pred_6_elem_u, (vec *)&V[0 + 5 * colVStride]);

      vec vec_u_row = __vload_pred(pred_6_elem_u, (vec *)U);

      double normFactor = vec_u_row.s[1] * (*s);
      vec vec_invNorm    = (vec)getRecip(normFactor);

      vec vec_v_col = vec_u_row * vec_invNorm;

      vec vec_si = (vec)0.0;
      vec_si += vec_u_row.s[1] * vec_in0;
      vec_si += vec_u_row.s[2] * vec_in1;
      vec_si += vec_u_row.s[3] * vec_in2;
      vec_si += vec_u_row.s[4] * vec_in3;
      vec_si += vec_u_row.s[5] * vec_in4;

      vec_in0 += vec_si * vec_v_col.s[1];
      vec_in1 += vec_si * vec_v_col.s[2];
      vec_in2 += vec_si * vec_v_col.s[3];
      vec_in3 += vec_si * vec_v_col.s[4];
      vec_in4 += vec_si * vec_v_col.s[5];


      __vstore_pred(pred_6_elem, (vec *)&V[0 + 0 * colVStride], vec_top_row);
      __vstore_pred(pred_6_elem, (vec *)&V[0 + 1 * colVStride], vec_in0);
      __vstore_pred(pred_6_elem, (vec *)&V[0 + 2 * colVStride], vec_in1);
      __vstore_pred(pred_6_elem, (vec *)&V[0 + 3 * colVStride], vec_in2);
      __vstore_pred(pred_6_elem, (vec *)&V[0 + 4 * colVStride], vec_in3);
      __vstore_pred(pred_6_elem, (vec *)&V[0 + 5 * colVStride], vec_in4);

   }
  return;
}




#endif /* #if (__C7X_VEC_SIZE_BITS__ == 512) */


/* ======================================================================== */
/*  End of file:  DSPLIB_svd_small_v_process.h                              */
/* ======================================================================== */

