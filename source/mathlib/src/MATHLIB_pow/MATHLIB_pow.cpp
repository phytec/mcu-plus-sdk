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
#include "MATHLIB_lut.h"
#include "MATHLIB_permute.h"
#include "MATHLIB_pow_scalar.h"
#include "MATHLIB_types.h"
#include "MATHLIB_utility.h"

/******************************************************************************/
/*                                                                            */
/* MATHLIB_pow                                                                */
/*                                                                            */
/******************************************************************************/
template <typename T>
static inline void MATHLIB_pow_vector(size_t length, T *restrict pSrc0, T *restrict pSrc1, T *restrict pDst);

template <typename T>
static inline MATHLIB_STATUS MATHLIB_pow_exp(__SE_TEMPLATE_v1 *restrict se0Params,
                                             __SA_TEMPLATE_v1 *restrict sa0Params,
                                             size_t                     length,
                                             T *restrict                pSrc0,
                                             T *restrict                pDst);

template <typename T>
static inline MATHLIB_STATUS MATHLIB_pow_cond(size_t length, T *restrict pSrc0, T *restrict pSrc1, T *restrict pDst);

template <>
inline void MATHLIB_pow_vector<float>(size_t length, float *restrict pSrc0, float *restrict pSrc1, float *restrict pDst)
{
   // Call scalar code
   for (uint32_t i = 0; i < length; i++) {
      pDst[i] = MATHLIB_pow_scalar_ci(pSrc0[i], pSrc1[i]);
   }
}

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

template <typename T>
static inline void MATHLIB_pow_log_opt(size_t length, T *restrict pSrc0, T *restrict pSrc1, T *restrict pDst);

template <>
inline void
MATHLIB_pow_log_opt<double>(size_t length, double *restrict pSrc0, double *restrict pSrc1, double *restrict pDst)
{
   // variables
   size_t         numBlocks    = 0;               // compute loop's iteration count
   size_t         remNumBlocks = 0;               // when numBlocks is not a multiple of SIMD width

   // derive c7x vector type from template typename
   typedef typename c7x::make_full_vector<double>::type vec;

   __SE_TEMPLATE_v1 se0Params = __gen_SE_TEMPLATE_v1();
   __SA_TEMPLATE_v1 sa0Params = __gen_SA_TEMPLATE_v1();

   MATHLIB_SE0SA01DSequentialInit(&se0Params, &sa0Params, length, pDst, pDst);

   // calculate compute loop's iteration counter
   numBlocks    = length / c7x::element_count_of<vec>::value;
   remNumBlocks = length % c7x::element_count_of<vec>::value;
   if (remNumBlocks) {
      numBlocks++;
   }

   // open SE0, SE1, and SA0 for reading and writing operands
   MATHLIB_SE0SA0Open(&se0Params, &sa0Params, pSrc0);

   vec Half, MAXe, srHalf, Half_sq, MINe, a0, a1, a2, b0, b1, b2, c1_vec, c2_vec, W, X, Y, Z, zn, zd, Rz, Sa, Bd, Cn, Da;

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
   c1_vec      = (vec) 0.693359375;                /*  355/512      */
   c2_vec      = (vec) -2.121944400546905827679e-4;

   c7x::long_vec long_zero_vec   = (c7x::long_vec) 0;
   vec           double_zero_vec = (vec) 0.0;
   vec           outMAX          = (vec)(308.254715974092);

   for (size_t i = 0; i < numBlocks; i++) {

      vec a              = c7x::strm_eng<0, vec>::get_adv();
      Y                  = __abs(a);
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

      X            = cmn_DIVDP_opt(zn, zd);
      __vpred tmp  = c7x::strm_agen<0, vec>::get_vpred();
      vec *   addr = c7x::strm_agen<0, vec>::get_adv(pDst);
      __vstore_pred(tmp, addr, X);
   }
   MATHLIB_SE0SA0Close();

   MATHLIB_SE0SA0Open(&se0Params, &sa0Params, pDst);

   for (size_t i = 0; i < numBlocks; i++) {

      X = c7x::strm_eng<0, vec>::get_adv();

      W            = X * X;
      Bd           = ((((W + b2) * W) + b1) * W) + b0;
      Cn           = (((W * a2) + a1) * W) + a0;
      Rz           = W * cmn_DIVDP_opt(Cn, Bd);
      Sa           = X + (X * Rz);
      __vpred tmp  = c7x::strm_agen<0, vec>::get_vpred();
      vec *   addr = c7x::strm_agen<0, vec>::get_adv(pDst);
      __vstore_pred(tmp, addr, Sa);
   }

   MATHLIB_SE0SA0Close();

   MATHLIB_SE0SA0Open(&se0Params, &sa0Params, pSrc0);

   __SE1_OPEN(pDst, se0Params);
   for (size_t i = 0; i < numBlocks; i++) {

      vec a  = c7x::strm_eng<0, vec>::get_adv();
      Sa = c7x::strm_eng<1, vec>::get_adv();

      Y                  = a;
      c7x::long_vec exp_ = c7x::as_long_vec((c7x::as_ulong_vec(Y) << 1) >> 53);
      c7x::long_vec N_vec    = exp_ - 1022;

      c7x::ulong_vec upper = c7x::as_ulong_vec(Y) & (0x000FFFFF00000000u);
      upper                = 0x3FE0000000000000u | upper;

      Z = c7x::as_double_vec((0x00000000FFFFFFFFu & c7x::as_ulong_vec(Y)) | upper);

      __vpred cmp1 = __cmp_eq_pred(exp_, long_zero_vec);
      Z            = __select(cmp1, double_zero_vec, Z);

      __vpred cmp2 = __cmp_lt_pred(srHalf, Z);

      N_vec = __select(cmp2, N_vec, (N_vec - 1));

      Cn = __low_int_to_double(c7x::as_int_vec(N_vec));
      Da = ((Cn * c2_vec) + Sa) + (Cn * c1_vec);

      /**********************************************************************/
      /* Bounds checking                                                    */
      /**********************************************************************/

      // if (Y < MINe) {
      //     Da = -MAXe;
      // }
      __vpred cmp_min_vec = __cmp_lt_pred(Y, MINe);
      Da              = __select(cmp_min_vec, -MAXe, Da);

      // if (Y > MAXe) {
      //     Da = 308.254715974092;
      // }
      __vpred cmp_max_vec = __cmp_lt_pred(MAXe, Y);
      Da              = __select(cmp_max_vec, outMAX, Da);

      __vpred tmp  = c7x::strm_agen<0, vec>::get_vpred();
      vec *   addr = c7x::strm_agen<0, vec>::get_adv(pDst);
      __vstore_pred(tmp, addr, Da);
   }
   __SE1_CLOSE();
   MATHLIB_SE0SA0Close();
}

template <>
inline MATHLIB_STATUS
MATHLIB_pow_cond<double>(size_t length, double *restrict pSrc0, double *restrict pSrc1, double *restrict pDst)
{
   // variables
   MATHLIB_STATUS status       = MATHLIB_SUCCESS; // return function status
   size_t         numBlocks    = 0;               // compute loop's iteration count
   size_t         remNumBlocks = 0;               // when numBlocks is not a multiple of SIMD width

   // derive c7x vector type from template typename
   typedef typename c7x::make_full_vector<double>::type vec;

   __SE_TEMPLATE_v1 se0Params = __gen_SE_TEMPLATE_v1();
   __SE_TEMPLATE_v1 se1Params = __gen_SE_TEMPLATE_v1();
   __SA_TEMPLATE_v1 sa0Params = __gen_SA_TEMPLATE_v1();

   // calculate compute loop's iteration counter
   numBlocks    = length / c7x::element_count_of<vec>::value;
   remNumBlocks = length % c7x::element_count_of<vec>::value;
   if (remNumBlocks) {
      numBlocks++;
   }

   __SE_ELETYPE SE_ELETYPE;
   __SE_VECLEN  SE_VECLEN;
   __SA_VECLEN  SA_VECLEN;

   // assign SE and SA params based on vector type
   SE_VECLEN  = c7x::se_veclen<vec>::value;
   SA_VECLEN  = c7x::sa_veclen<vec>::value;
   SE_ELETYPE = c7x::se_eletype<vec>::value;

   se0Params.ICNT0   = length;
   se0Params.ELETYPE = SE_ELETYPE;
   se0Params.VECLEN  = SE_VECLEN;
   se0Params.DIMFMT  = __SE_DIMFMT_1D;

   se1Params.DIMFMT        = __SE_DIMFMT_3D;
   se1Params.ICNT0         = c7x::element_count_of<vec>::value;
   se1Params.ELETYPE       = SE_ELETYPE;
   se1Params.VECLEN        = SE_VECLEN;
   se1Params.ICNT1         = 2;
   se1Params.ICNT2         = numBlocks;
   se1Params.DIM2          = c7x::element_count_of<vec>::value;
   se1Params.DECDIM1       = __SE_DECDIM_DIM2;
   se1Params.DECDIM1_WIDTH = length;
   se1Params.DIM1          = ((double *) pSrc1) - ((double *) pSrc0);

   sa0Params.ICNT0  = length;
   sa0Params.DIM1   = length;
   sa0Params.VECLEN = SA_VECLEN;
   sa0Params.DIMFMT = __SA_DIMFMT_1D;

   __SE0_OPEN(pDst, se0Params);
   __SE1_OPEN(pSrc0, se1Params);
   __SA0_OPEN(sa0Params);

   vec zeroVec, one, X2;

   zeroVec                      = (vec) 0.0f;
   one                       = (vec) 1.0f;
   c7x::long_vec zero_int    = (c7x::long_vec)(0);
   c7x::long_vec one_int     = (c7x::long_vec)(1);
   c7x::int_vec  Sign        = (c7x::int_vec)(1);
   c7x::int_vec  negate_Sign = (c7x::int_vec)(-1);

   c7x::long_vec valueL1 = (c7x::long_vec)(0X7fffffffffffffff);
   c7x::long_vec valueL2 = (c7x::long_vec)(0X7ff0000000000000);

   for (size_t i = 0; i < numBlocks; i++) {
      vec inVec0 = c7x::strm_eng<1, vec>::get_adv();
      vec inVec1 = c7x::strm_eng<1, vec>::get_adv();
      vec W      = c7x::strm_eng<0, vec>::get_adv();

      c7x::int_vec y = __double_to_int(inVec1);

      __vpred cmp_cond1 = __cmp_lt_pred(inVec0, zeroVec);
      __vpred cmp_cond2 = __cmp_eq_pred(inVec1, __low_int_to_double(y));

      cmp_cond2 = __and(cmp_cond2, cmp_cond1);

      c7x::long_vec y_long    = c7x::as_long_vec(y);
      __vpred       cmp_cond3 = __cmp_eq_pred((y_long & one_int), zero_int);

      cmp_cond3 = __and(cmp_cond2, __negate(cmp_cond3));

      Sign = __select(cmp_cond3, negate_Sign, Sign);

      X2 = __low_int_to_double(Sign) * W;

      __vpred cmp_cond5 = __cmp_eq_pred(inVec1, __low_int_to_double(y));
      cmp_cond5         = __and(cmp_cond1, __negate(cmp_cond5));
      X2                = __select(cmp_cond5, c7x::as_double_vec(valueL1), X2);

      __vpred cmp_cond6 = __cmp_eq_pred(inVec0, zeroVec);
      __vpred cmp_cond7 = __cmp_lt_pred(inVec1, zeroVec);
      cmp_cond7         = __and(cmp_cond6, cmp_cond7);
      X2                = __select(cmp_cond7, c7x::as_double_vec(valueL2), X2);

      // Store log computation result in
      __vpred tmp  = c7x::strm_agen<0, vec>::get_vpred();
      vec *   addr = c7x::strm_agen<0, vec>::get_adv(pDst);
      __vstore_pred(tmp, addr, X2);
   }
   MATHLIB_SE0SE1SA0Close();
   return status;
}

template <>
inline MATHLIB_STATUS MATHLIB_pow_exp<double>(__SE_TEMPLATE_v1 *restrict se0Params,
                                              __SA_TEMPLATE_v1 *restrict sa0Params,
                                              size_t                     length,
                                              double *restrict           pSrc1,
                                              double *restrict           pDst)
{

   // variables
   MATHLIB_STATUS status       = MATHLIB_SUCCESS; // return function status
   size_t         numBlocks    = 0;               // compute loop's iteration count
   size_t         remNumBlocks = 0;               // when numBlocks is not a multiple of SIMD width

   // derive c7x vector type from template typename
   typedef typename c7x::make_full_vector<double>::type vec;

   // calculate compute loop's iteration counter
   numBlocks    = length / c7x::element_count_of<vec>::value;
   remNumBlocks = length % c7x::element_count_of<vec>::value;
   if (remNumBlocks) {
      numBlocks++;
   }

   // open SE0, SE1, and SA0 for reading and writing operands
   MATHLIB_SE0SA0Open(se0Params, sa0Params, pDst);

   __SE1_OPEN(pSrc1, *se0Params);

   vec Halfe, Maxe, LnMaxe, LnMine, a0e, a1e, a2e, b0e, b1e, b2e, c1e, C2e, L2e, Zero;

   Halfe  = (vec) 0.5;
   Maxe   = (vec) 1.7976931348623157e+308;
   LnMaxe = (vec) 709.78271289338;
   LnMine = (vec) -708.3964185322641;
   a0e    = (vec) 0.249999999999999993;
   a1e    = (vec) 0.694360001511792852e-2;
   a2e    = (vec) 0.165203300268279130e-4;
   b0e    = (vec) 0.5;
   b1e    = (vec) 0.555538666969001188e-1;
   b2e    = (vec) 0.495862884905441294e-3;
   c1e    = (vec) 0.693359375; /* 355/512 */
   C2e    = (vec) -2.1219444005469058277e-4;
   L2e    = (vec) 1.4426950408889634074;
   Zero   = (vec) 0.0f;

   vec Ye, Xe, We, Re, Se, Be, Ce, De;

   // compute loop to perform vector pow
   for (size_t i = 0; i < numBlocks; i++) {
      vec invec = c7x::strm_eng<0, vec>::get_adv();
      vec b     = c7x::strm_eng<1, vec>::get_adv();

      Ye = invec * b;
      Ce = Ye * L2e;

      c7x::int_vec Ne = __double_to_int(Ce);

      Se = __low_int_to_double(Ne);
      Xe = (Ye - (Se * c1e)) - (Se * C2e); /*  range reduction  */

      We = Xe * Xe;
      Be = (((b2e * We) + b1e) * We) + b0e;        /* denominator  */
      De = ((((a2e * We) + a1e) * We) + a0e) * Xe; /* numerator  */
      Re = Halfe + cmn_DIVDP_opt(De, Be - De);

      Ye = invec;

      Ce = Ye * L2e;

      c7x::int_vec upper = 1024 + (Ne);
      upper              = c7x::as_int_vec((c7x::as_uint_vec(upper) << 20));
      Se                 = c7x::as_double_vec(c7x::as_long_vec(upper) << 32);

      Ce = Re * Se;

      __vpred cmp_Max = __cmp_lt_pred(LnMaxe, invec);
      Ce              = __select(__negate(cmp_Max), Ce, Maxe);

      __vpred cmp_Min = __cmp_lt_pred(invec, LnMine);
      Ce              = __select(cmp_Min, Zero, Ce);

      // Store exp computation result in
      __vpred tmp  = c7x::strm_agen<0, vec>::get_vpred();
      vec *   addr = c7x::strm_agen<0, vec>::get_adv(pDst);
      __vstore_pred(tmp, addr, Ce);
   }

   MATHLIB_SE0SA0Close();
   __SE1_CLOSE();
   return status;
}

template <>
inline void
MATHLIB_pow_vector<double>(size_t length, double *restrict pSrc0, double *restrict pSrc1, double *restrict pDst)
{
   size_t numBlocks    = 0; // compute loop's iteration count
   size_t remNumBlocks = 0; // when numBlocks is not a multiple of SIMD width

   // derive c7x vector type from template typename
   typedef typename c7x::make_full_vector<double>::type vec;

   __SE_TEMPLATE_v1 se0Params = __gen_SE_TEMPLATE_v1();
   __SA_TEMPLATE_v1 sa0Params = __gen_SA_TEMPLATE_v1();

   // calculate compute loop's iteration counter
   numBlocks    = length / c7x::element_count_of<vec>::value;
   remNumBlocks = length % c7x::element_count_of<vec>::value;
   if (remNumBlocks) {
      numBlocks++;
   }
   MATHLIB_SE0SA01DSequentialInit(&se0Params, &sa0Params, length, pSrc0, pDst);

   /**********************************************************************/
   /* Create and assign values for constants employed on pow computation */
   /**********************************************************************/

   MATHLIB_pow_log_opt(length, pSrc0, pSrc1, pDst);

   MATHLIB_pow_exp(&se0Params, &sa0Params, length, pSrc1, pDst);

   MATHLIB_pow_cond(length, pSrc0, pSrc1, pDst);
}

// this method performs power computation of input vectors
template <typename T> MATHLIB_STATUS MATHLIB_pow(size_t length, T *restrict pSrc0, T *restrict pSrc1, T *restrict pDst)
{
   // variables
   MATHLIB_STATUS status = MATHLIB_SUCCESS; // return function status

   status = MATHLIB_checkParams(length, pSrc0, pSrc1, pDst);

   if (status == MATHLIB_SUCCESS) {
      if (length < 2){
         pDst[0] = MATHLIB_pow_scalar_ci<T>(pSrc0[0], pSrc1[0]);
      }
      else {
         MATHLIB_pow_vector<T>(length, pSrc0, pSrc1, pDst);
      }
   }

   return status;
}

/******************************************************************************/
/*                                                                            */
/* Explicit templatization for datatypes supported by MATHLIB_pow             */
/*                                                                            */
/******************************************************************************/

// single precision
template MATHLIB_STATUS
MATHLIB_pow<float>(size_t length, float *restrict pSrc0, float *restrict pSrc1, float *restrict pDst);

// double precision
template MATHLIB_STATUS
MATHLIB_pow<double>(size_t length, double *restrict pSrc0, double *restrict pSrc1, double *restrict pDst);

/******************************************************************************/
/*                                                                            */
/* C-interface wrapper functions                                              */
/*                                                                            */
/******************************************************************************/

extern "C" {

// single-precision wrapper
MATHLIB_STATUS MATHLIB_pow_sp(size_t length, float *restrict pSrc0, float *restrict pSrc1, float *restrict pDst)
{
   MATHLIB_STATUS status = MATHLIB_pow<float>(length, pSrc0, pSrc1, pDst);
   return status;
}

// double-precision wrapper
MATHLIB_STATUS MATHLIB_pow_dp(size_t length, double *restrict pSrc0, double *restrict pSrc1, double *restrict pDst)
{
   MATHLIB_STATUS status = MATHLIB_pow<double>(length, pSrc0, pSrc1, pDst);
   return status;
}


} // extern "C"
