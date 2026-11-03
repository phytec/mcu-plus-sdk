/******************************************************************************
 * Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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

#define ELEMENT_COUNT(x) c7x::element_count_of<x>::value

/******************************************************************************/
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/******************************************************************************/

#include "MATHLIB_ilut.h"
#include "MATHLIB_log10_scalar.h"
#include "MATHLIB_lut.h"
#include "MATHLIB_permute.h"
#include "MATHLIB_types.h"
#include "MATHLIB_utility.h"

/******************************************************************************/
/*                                                                            */
/* MATHLIB_log10                                                               */
/*                                                                            */
/******************************************************************************/

// Division function for double precision
static inline c7x::double_vec cmn_DIVDP_opt(c7x::double_vec a, c7x::double_vec b)
{

   c7x::double_vec Two = (c7x::double_vec)(2.0f);
   c7x::double_vec X;
   X = __recip(b);
   X = X * (Two - (b * X));
   X = X * (Two - (b * X));
   X = X * (Two - (b * X));
   X = a * X;

   return X;
}

// for length greater than 1 and less than 33 use split - 1 function for better optimization
static inline void MATHLIB_log10_vector_split1(size_t length, double *restrict pSrc, double *restrict pDst)
{

   // variables
   size_t numBlocks    = 0; // compute loop's iteration count
   size_t remNumBlocks = 0; // when numBlocks is not a multiple of SIMD width

   // derive c7x vector type from template typename
   typedef typename c7x::make_full_vector<double>::type vec;

   __SE_TEMPLATE_v1 se0Params = __gen_SE_TEMPLATE_v1();
   __SA_TEMPLATE_v1 sa0Params = __gen_SA_TEMPLATE_v1();

   MATHLIB_SE0SA01DSequentialInit(&se0Params, &sa0Params, length, pSrc, pDst);

   // calculate compute loop's iteration counter
   numBlocks    = length / c7x::element_count_of<vec>::value;
   remNumBlocks = length % c7x::element_count_of<vec>::value;
   if (remNumBlocks) {
      numBlocks++;
   }

   // open SE0, SE1, and SA0 for reading and writing operands
   MATHLIB_SE0SA0Open(&se0Params, &sa0Params, pSrc);

   /***********************************************************************/
   /* Create and assign values for constants employed on log10 computation */
   /***********************************************************************/

   vec Half, MAXe, srHalf, Half_sq, MINe, a0, a1, a2, b0, b1, b2, c1, c2, c10e, W, X, Y, Z, zn, zd, Rz, Sa, Bd, Cn, Da;

   Half    = (vec) 0.5;
   Half_sq = (vec) 0.5 * 0.5;
   MAXe    = (vec) 1.7976931348623157e+308;
   srHalf  = (vec) 0.70710678118654752440; /* sqrt(0.5) */
   MINe    = (vec) 2.2250738585072014e-308;
   a0      = (vec) -0.64124943423745581147e+2;
   a1      = (vec) 0.16383943563021534222e+2;
   a2      = (vec) -0.78956112887491257267e+0;
   b0      = (vec) -0.76949932108494879777e+3;
   b1      = (vec) 0.31203222091924532844e+3;
   b2      = (vec) -0.35667977739034646171e+2; /* Note b3 = 1.0 */
   c1      = (vec) 0.693359375;                /*  355/512      */
   c2      = (vec) -2.121944400546905827679e-4;
   c10e    = (vec) 0.43429448190325182765; /* log (base 10) of e */

   c7x::long_vec long_zero_vec   = (c7x::long_vec) 0;
   vec           double_zero_vec = (vec) 0.0;
   vec           outMAX          = (vec)(308.254715974092);

   // compute loop to perform vector log10
   for (size_t i = 0; i < numBlocks; i++) {

      vec a = c7x::strm_eng<0, vec>::get_adv();

      Y                  = a;
      c7x::long_vec exp_ = c7x::as_long_vec((c7x::as_ulong_vec(Y) << 1) >> 53);

      c7x::ulong_vec upper = c7x::as_ulong_vec(Y) & (0x000FFFFF00000000u);
      upper                = 0x3FE0000000000000u | upper;

      Z = c7x::as_double_vec((0x00000000FFFFFFFFu & c7x::as_ulong_vec(Y)) | upper);

      __vpred cmp1 = __cmp_eq_pred(exp_, long_zero_vec);
      Z            = __select(cmp1, double_zero_vec, Z);

      vec     z_minus_half = Z - Half;
      vec     z_mul_half   = (Z * Half) + Half;
      __vpred cmp2         = __cmp_lt_pred(srHalf, Z);
      zn                   = __select(cmp2, (z_minus_half - Half), z_minus_half);
      zd                   = __select(cmp2, z_mul_half, (z_mul_half - Half_sq));

      X  = cmn_DIVDP_opt(zn, zd);
      W  = X * X;
      Bd = ((((W + b2) * W) + b1) * W) + b0;
      Cn = (((W * a2) + a1) * W) + a0;
      Rz = W * cmn_DIVDP_opt(Cn, Bd);
      Sa = X + (X * Rz);

      __vpred tmp  = c7x::strm_agen<0, vec>::get_vpred();
      vec *   addr = c7x::strm_agen<0, vec>::get_adv(pDst);
      __vstore_pred(tmp, addr, Sa);
   }

   MATHLIB_SE0SA0Close();

   MATHLIB_SE0SA0Open(&se0Params, &sa0Params, pSrc);
   __SE1_OPEN(pDst, se0Params);

   for (size_t i = 0; i < numBlocks; i++) {

      vec a  = c7x::strm_eng<0, vec>::get_adv();
      Sa = c7x::strm_eng<1, vec>::get_adv();

      Y                  = a;
      c7x::long_vec exp_ = c7x::as_long_vec((c7x::as_ulong_vec(Y) << 1) >> 53);
      c7x::long_vec N    = exp_ - 1022;

      c7x::ulong_vec upper = c7x::as_ulong_vec(Y) & (0x000FFFFF00000000u);
      upper                = 0x3FE0000000000000u | upper;

      Z = c7x::as_double_vec((0x00000000FFFFFFFFu & c7x::as_ulong_vec(Y)) | upper);

      __vpred cmp1 = __cmp_eq_pred(exp_, long_zero_vec);
      Z            = __select(cmp1, double_zero_vec, Z);

      __vpred cmp2 = __cmp_lt_pred(srHalf, Z);

      N = __select(cmp2, N, (N - 1));

      Cn = __low_int_to_double(c7x::as_int_vec(N));
      Da = ((Cn * c2) + Sa) + (Cn * c1);
      Da = c10e * Da;

      /**********************************************************************/
      /* Bounds checking                                                    */
      /**********************************************************************/

      // if (Y < MINe) {
      //     Da = -MAXe;
      // }
      __vpred cmp_min = __cmp_lt_pred(Y, MINe);
      Da              = __select(cmp_min, -MAXe, Da);

      // if (Y > MAXe) {
      //     Da = 308.254715974092;
      // }
      __vpred cmp_max = __cmp_lt_pred(MAXe, Y);
      Da              = __select(cmp_max, outMAX, Da);

      __vpred tmp  = c7x::strm_agen<0, vec>::get_vpred();
      vec *   addr = c7x::strm_agen<0, vec>::get_adv(pDst);
      __vstore_pred(tmp, addr, Da);
   }

   __SE1_CLOSE();
   MATHLIB_SE0SA0Close();
}

// for length greater than 32 use split - 2 function for better optimization
static inline void MATHLIB_log10_vector_split2(size_t length, double *restrict pSrc, double *restrict pDst)
{
   // variables
   size_t numBlocks    = 0; // compute loop's iteration count
   size_t remNumBlocks = 0; // when numBlocks is not a multiple of SIMD width

   // derive c7x vector type from template typename
   typedef typename c7x::make_full_vector<double>::type vec;

   __SE_TEMPLATE_v1 se0Params = __gen_SE_TEMPLATE_v1();
   __SA_TEMPLATE_v1 sa0Params = __gen_SA_TEMPLATE_v1();

   MATHLIB_SE0SA01DSequentialInit(&se0Params, &sa0Params, length, pSrc, pDst);

   // calculate compute loop's iteration counter
   numBlocks    = length / c7x::element_count_of<vec>::value;
   remNumBlocks = length % c7x::element_count_of<vec>::value;
   if (remNumBlocks) {
      numBlocks++;
   }

   // open SE0, SE1, and SA0 for reading and writing operands
   MATHLIB_SE0SA0Open(&se0Params, &sa0Params, pSrc);

   /***********************************************************************/
   /* Create and assign values for constants employed on log10 computation */
   /***********************************************************************/

   vec Half, MAXe, srHalf, Half_sq, MINe, a0, a1, a2, b0, b1, b2, c1, c2, c10e, W, X, Y, Z, zn, zd, Rz, Sa, Bd, Cn, Da;

   Half    = (vec) 0.5;
   Half_sq = (vec) 0.5 * 0.5;
   MAXe    = (vec) 1.7976931348623157e+308;
   srHalf  = (vec) 0.70710678118654752440; /* sqrt(0.5) */
   MINe    = (vec) 2.2250738585072014e-308;
   a0      = (vec) -0.64124943423745581147e+2;
   a1      = (vec) 0.16383943563021534222e+2;
   a2      = (vec) -0.78956112887491257267e+0;
   b0      = (vec) -0.76949932108494879777e+3;
   b1      = (vec) 0.31203222091924532844e+3;
   b2      = (vec) -0.35667977739034646171e+2; /* Note b3 = 1.0 */
   c1      = (vec) 0.693359375;                /*  355/512      */
   c2      = (vec) -2.121944400546905827679e-4;
   c10e    = (vec) 0.43429448190325182765; /* log (base 10) of e */

   c7x::long_vec long_zero_vec   = (c7x::long_vec) 0;
   vec           double_zero_vec = (vec) 0.0;
   vec           outMAX          = (vec)(308.254715974092);

   // compute loop to perform vector log10
   for (size_t i = 0; i < numBlocks; i++) {

      vec a = c7x::strm_eng<0, vec>::get_adv();

      Y                  = a;
      c7x::long_vec exp_ = c7x::as_long_vec((c7x::as_ulong_vec(Y) << 1) >> 53);

      c7x::ulong_vec upper = c7x::as_ulong_vec(Y) & (0x000FFFFF00000000u);
      upper                = 0x3FE0000000000000u | upper;

      Z = c7x::as_double_vec((0x00000000FFFFFFFFu & c7x::as_ulong_vec(Y)) | upper);

      __vpred cmp1 = __cmp_eq_pred(exp_, long_zero_vec);
      Z            = __select(cmp1, double_zero_vec, Z);

      vec     z_minus_half = Z - Half;
      vec     z_mul_half   = (Z * Half) + Half;
      __vpred cmp2         = __cmp_lt_pred(srHalf, Z);
      zn                   = __select(cmp2, (z_minus_half - Half), z_minus_half);
      zd                   = __select(cmp2, z_mul_half, (z_mul_half - Half_sq));

      X = cmn_DIVDP_opt(zn, zd);

      __vpred tmp  = c7x::strm_agen<0, vec>::get_vpred();
      vec *   addr = c7x::strm_agen<0, vec>::get_adv(pDst);
      __vstore_pred(tmp, addr, X);
   }

   MATHLIB_SE0SA0Close();

   MATHLIB_SE0SA0Open(&se0Params, &sa0Params, pDst);

   for (size_t i = 0; i < numBlocks; i++) {

      X = c7x::strm_eng<0, vec>::get_adv();

      W  = X * X;
      Bd = ((((W + b2) * W) + b1) * W) + b0;
      Cn = (((W * a2) + a1) * W) + a0;
      Rz = W * cmn_DIVDP_opt(Cn, Bd);
      Sa = X + (X * Rz);

      __vpred tmp  = c7x::strm_agen<0, vec>::get_vpred();
      vec *   addr = c7x::strm_agen<0, vec>::get_adv(pDst);
      __vstore_pred(tmp, addr, Sa);
   }

   MATHLIB_SE0SA0Close();

   MATHLIB_SE0SA0Open(&se0Params, &sa0Params, pSrc);

   __SE1_OPEN(pDst, se0Params);

   for (size_t i = 0; i < numBlocks; i++) {

      vec a  = c7x::strm_eng<0, vec>::get_adv();
      Sa = c7x::strm_eng<1, vec>::get_adv();

      Y                  = a;
      c7x::long_vec exp_ = c7x::as_long_vec((c7x::as_ulong_vec(Y) << 1) >> 53);
      c7x::long_vec N    = exp_ - 1022;

      c7x::ulong_vec upper = c7x::as_ulong_vec(Y) & (0x000FFFFF00000000u);
      upper                = 0x3FE0000000000000u | upper;

      Z = c7x::as_double_vec((0x00000000FFFFFFFFu & c7x::as_ulong_vec(Y)) | upper);

      __vpred cmp1 = __cmp_eq_pred(exp_, long_zero_vec);
      Z            = __select(cmp1, double_zero_vec, Z);

      __vpred cmp2 = __cmp_lt_pred(srHalf, Z);

      N = __select(cmp2, N, (N - 1));

      Cn = __low_int_to_double(c7x::as_int_vec(N));
      Da = ((Cn * c2) + Sa) + (Cn * c1);
      Da = c10e * Da;

      /**********************************************************************/
      /* Bounds checking                                                    */
      /**********************************************************************/

      // if (Y < MINe) {
      //     Da = -MAXe;
      // }
      __vpred cmp_min = __cmp_lt_pred(Y, MINe);
      Da              = __select(cmp_min, -MAXe, Da);

      // if (Y > MAXe) {
      //     Da = 308.254715974092;
      // }
      __vpred cmp_max = __cmp_lt_pred(MAXe, Y);
      Da              = __select(cmp_max, outMAX, Da);

      __vpred tmp  = c7x::strm_agen<0, vec>::get_vpred();
      vec *   addr = c7x::strm_agen<0, vec>::get_adv(pDst);
      __vstore_pred(tmp, addr, Da);
   }

   __SE1_CLOSE();

   MATHLIB_SE0SA0Close();
}


template <typename T> static inline void MATHLIB_log10_vector(size_t length, T *pSrc, T *pDst);

// this method performs log10 computation of input vector
template <> inline void MATHLIB_log10_vector<float>(size_t length, float *restrict pSrc, float *restrict pDst)
{
   // Call scalar code
   for (uint32_t i = 0; i < length; i++) {
      pDst[i] = MATHLIB_log10_scalar_ci<float>(pSrc[i]);
   }
}


// this method performs log10 computation of input vector
template <> inline void MATHLIB_log10_vector<double>(size_t length, double *restrict pSrc, double *restrict pDst)
{
   if (length < 33) {
      MATHLIB_log10_vector_split1(length, pSrc, pDst);
   }
   else {
      MATHLIB_log10_vector_split2(length, pSrc, pDst);
   }
}

// this method performs exponential computation of input vector
template <typename T> MATHLIB_STATUS MATHLIB_log10(size_t length, T *restrict pSrc, T *restrict pDst)
{
   MATHLIB_STATUS status = MATHLIB_SUCCESS; // return function status

   // check for null pointers and non-zero length
   status = MATHLIB_checkParams(length, pSrc, pDst);
   
   // for length equal to 1 use scalar operations othewise use vector operations for better optimization
   if (status == MATHLIB_SUCCESS) {
      if (length < 2) {
         pDst[0] = MATHLIB_log10_scalar_ci<T>(pSrc[0]);
      }
      else {
         MATHLIB_log10_vector<T>(length, pSrc, pDst);
      }
   }
   return status;
}

/******************************************************************************/
/*                                                                            */
/* Explicit templatization for datatypes supported by MATHLIB_log10            */
/*                                                                            */
/******************************************************************************/

template MATHLIB_STATUS MATHLIB_log10<float>(size_t length, float *pSrc, float *pDst);
template MATHLIB_STATUS MATHLIB_log10<double>(size_t length, double *pSrc, double *pDst);

/******************************************************************************/
/*                                                                            */
/* C-interface wrapper functions                                              */
/*                                                                            */
/******************************************************************************/

extern "C" {

// single-precision wrapper
MATHLIB_STATUS MATHLIB_log10_sp(size_t length, float *pSrc, float *pDst)
{
   MATHLIB_STATUS status = MATHLIB_log10<float>(length, pSrc, pDst);
   return status;
}

// double-precision wrapper
MATHLIB_STATUS MATHLIB_log10_dp(size_t length, double *pSrc, double *pDst)
{
   MATHLIB_STATUS status = MATHLIB_log10<double>(length, pSrc, pDst);
   return status;
}


} // extern "C"
