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

#include <cstdint>
#define ELEMENT_COUNT(x) c7x::element_count_of<x>::value

/******************************************************************************/
/*                                                                            */
/* Includes                                                                   */
/*                                                                            */
/******************************************************************************/

#include "MATHLIB_atan2_scalar.h"
#include "MATHLIB_ilut.h"
#include "MATHLIB_lut.h"
#include "MATHLIB_permute.h"
#include "MATHLIB_types.h"
#include "MATHLIB_utility.h"
#include <cstddef>
#include <limits>

/******************************************************************************/
/*                                                                            */
/* MATHLIB_atan2                                                               */
/*                                                                            */
/******************************************************************************/

// this method performs a/b division for atan2 computation
template <typename vecType> static inline vecType divspMod_atan2_i(vecType a, vecType b);

template <> inline c7x::float_vec divspMod_atan2_i<c7x::float_vec>(c7x::float_vec a, c7x::float_vec b)
{
   typedef typename c7x::make_full_vector<float>::type vecType;

   vecType res_fVec, r0, d0, d1, p0_Vec, p1_Vec, Two;

   Two = (vecType) 2.0;

   p0_Vec = __recip(b);
   d0     = p0_Vec * b;
   r0     = p0_Vec;

   p1_Vec = Two - d0;
   d1     = r0 * p1_Vec;

   res_fVec = a * d1;

   return res_fVec;
}

// this method constructs the polynomial estimation for atan2 computation
template <typename vecType, typename vecBool>
static inline vecType atan22f_sr1i_atan2_i(vecType g1, vecType pih, vecBool s, vecBool bn, vecBool an);

template <>
inline c7x::float_vec atan22f_sr1i_atan2_i<c7x::float_vec, c7x::char_vec>(c7x::float_vec g1,
                                                                          c7x::float_vec pih,
                                                                          c7x::char_vec  s,
                                                                          c7x::char_vec  bn,
                                                                          c7x::char_vec  an)
{

   /*************************************************************************************/
   /* Create and assign values for constants and variables for polynomial approximation */
   /*************************************************************************************/
   c7x::float_vec coef_vec, negativeCoef, pi_vec, polVec, Zero_vec, G2, G4, G6, G8, G10, G12, tmp1_vec, tmp2_vec, C1,
       C2, C3, C4, C5, C6, C7, C8, Res, res_minus, res_plus;
   c7x::char_vec false_vec;

   false_vec = (c7x::char_vec) 0;
   Zero_vec  = (c7x::float_vec) 0.0;
   pi_vec    = (c7x::float_vec) 3.1415927;
   // pih = (c7x::float_vec) 1.57079632679;

   C1 = (c7x::float_vec) 0.00230158202;
   C2 = (c7x::float_vec) -0.01394551000;
   C3 = (c7x::float_vec) 0.03937087815;
   C4 = (c7x::float_vec) -0.07235669163;
   C5 = (c7x::float_vec) 0.10521499322;
   C6 = (c7x::float_vec) -0.14175076797;
   C7 = (c7x::float_vec) 0.19989300877;
   C8 = (c7x::float_vec) -0.33332930041;

   coef_vec = pih;

   // get coef_vec based on the flags
   // check 'swap' flag
   //    if (s == false_vec) {
   //     coef_vec = pi_vec;
   //   }
   __vpred cmp_swap = __cmp_eq_pred(s, false_vec);
   coef_vec         = __select(cmp_swap, pi_vec, coef_vec);
   // if ((s == false_vec) && (bn == false_vec)) {
   //  coef_vec = 0.0f;

   __vpred cmp_negb      = __cmp_eq_pred(bn, false_vec);
   __vpred and_negB_swap = __and(cmp_negb, cmp_swap);

   coef_vec = __select(and_negB_swap, Zero_vec, coef_vec);

   // check if input to atan2_i is negative
   // if (an != false_vec) {
   //    coef_vec = -coef_vec;
   // }
   negativeCoef     = -coef_vec;
   __vpred cmp_sign = __cmp_eq_pred(an, false_vec);
   coef_vec         = __select(cmp_sign, coef_vec, negativeCoef);

   // calculate polynomial
   G2  = g1 * g1;
   G4  = G2 * G2;
   G6  = G2 * G4;
   G8  = G4 * G4;
   G10 = G6 * G4;
   G12 = G8 * G4;

   tmp1_vec = ((C5 * G8) + (C6 * G6)) + ((C7 * G4) + (C8 * G2));
   tmp2_vec = ((((C1 * G4) + (C2 * G2)) + C3) * G12) + (C4 * G10);

   polVec = tmp1_vec + tmp2_vec;
   polVec = (polVec * g1) + g1;

   // return ((s != false_vec) ? (coef_vec - polVec) : (coef_vec + polVec));
   res_minus       = coef_vec - polVec;
   res_plus        = coef_vec + polVec;
   __vpred cmp_res = __cmp_eq_pred(s, false_vec);
   Res             = __select(cmp_res, res_plus, res_minus);

   return Res;
}

// this method performs arc-tangent2 computation of input vector
template <typename T> static inline void MATHLIB_atan2_vector(size_t length, T *pSrc0, T *pSrc1, T *pDst);

template <> inline void MATHLIB_atan2_vector<float>(size_t length, float *pSrc0, float *pSrc1, float *pDst)
{

   // variables
   size_t numBlocks    = 0; // compute loop's iteration count
   size_t remNumBlocks = 0; // when numBlocks is not a multiple of SIMD width

   // derive c7x vector type from template typename
   typedef typename c7x::make_full_vector<float>::type vec;
   __SE_TEMPLATE_v1                                    se0Params = __gen_SE_TEMPLATE_v1();
   __SA_TEMPLATE_v1                                    sa0Params = __gen_SA_TEMPLATE_v1();

   MATHLIB_SE0SA01DSequentialInit(&se0Params, &sa0Params, length, pSrc0, pDst);

   // calculate compute loop's iteration counter
   numBlocks    = length / c7x::element_count_of<vec>::value;
   remNumBlocks = length % c7x::element_count_of<vec>::value;
   if (remNumBlocks) {
      numBlocks++;
   }

   // open SE0, SE1, and SA0 for reading and writing operands
   MATHLIB_SE0SE1SA0Open(&se0Params, &sa0Params, pSrc0, pSrc1);

   /***********************************************************************/
   /* Create and assign values for constants employed on atan2 computation */
   /***********************************************************************/
   vec           g, res_fvec, Zero, temp, abs_a, abs_b;
   c7x::char_vec an, bn, s, TRUE_vec, FALSE_vec;
   vec           pih    = (vec) 1.570796327;
   vec           pi_Vec = (vec) 3.141592741;
   vec           MAX    = std::numeric_limits<float>::max();

   TRUE_vec  = (c7x::char_vec) 1;
   FALSE_vec = (c7x::char_vec) 0;
   Zero      = (vec) 0.0;

   // compute loop to perform vector atan2
   for (size_t i = 0; i < numBlocks; i++) {
      vec a = c7x::strm_eng<0, vec>::get_adv();
      vec b = c7x::strm_eng<1, vec>::get_adv();

      vec x = a;
      vec y = b;

      /* if (i == 0) { */
      /*    x.print(); */
      /*    y.print(); */
      /* } */

      s                = FALSE_vec;
      __vpred cmp_negA = __cmp_lt_pred(a, Zero);
      an               = __select(cmp_negA, TRUE_vec, FALSE_vec);
      __vpred cmp_negB = __cmp_lt_pred(b, Zero);
      bn               = __select(cmp_negB, TRUE_vec, FALSE_vec);

      // swap a and b before calling division sub routine if a > b
      // if (_fabsf(a) > _fabsf(b) {
      //    temp = b;
      //    b = a;
      //    a    = temp;
      //    s    = TRUE_vec;
      // }

      abs_a = __abs(a);
      abs_b = __abs(b);

      __vpred cmp_AgtB = __cmp_lt_pred(abs_b, abs_a);
      temp             = __select(cmp_AgtB, b, Zero);
      b                = __select(cmp_AgtB, a, b);
      a                = __select(cmp_AgtB, temp, a);
      s                = __select(cmp_AgtB, TRUE_vec, s);
      /***********************************************************************/
      /* Division computation for atan2                                       */
      /***********************************************************************/
      g = divspMod_atan2_i<vec>(a, b);

      /***********************************************************************/
      /* Polynomial computation for atan2                                     */
      /***********************************************************************/
      res_fvec = atan22f_sr1i_atan2_i<vec, c7x::char_vec>(g, pih, s, bn, an);

      /***********************************************************************/
      /* Bounds Checking                                                     */
      /***********************************************************************/

      // if (x == 0.0f) {
      //    res_fvec = y >= 0.0f ? 0.0f : pi_Vec;
      // }

      __vpred cmp_zeroX = __cmp_eq_pred(x, Zero);

      __vpred cmp_zeroY = __cmp_le_pred(Zero, y);
      vec     resY      = __select(cmp_zeroY, Zero, pi_Vec);

      res_fvec = __select(cmp_zeroX, resY, res_fvec);

      // if (g > MAX) {

      // res_fvec = pih;
      // }

      __vpred gMax = __cmp_lt_pred(MAX, g);
      res_fvec     = __select(gMax, pih, res_fvec);

      // if (g < -MAX) {
      // res_fvec = -pih;
      // }

      vec MIN         = -MAX;
      vec negativepih = -pih;

      __vpred gMin = __cmp_lt_pred(g, MIN);
      res_fvec     = __select(gMin, negativepih, res_fvec);

      vec outVec = res_fvec;

      __vpred tmp  = c7x::strm_agen<0, vec>::get_vpred();
      vec    *addr = c7x::strm_agen<0, vec>::get_adv(pDst);
      __vstore_pred(tmp, addr, outVec);
   }

   MATHLIB_SE0SE1SA0Close();

   return;
}

static inline double atan2dpi(double a)
{
   double P0    = -1.3688768894191926929e+1;
   double P1    = -2.0505855195861651981e+1;
   double P2    = -8.4946240351320683534e+0;
   double P3    = -8.3758299368150059274e-1;
   double Q0    = 4.1066306682575781263e+1;
   double Q1    = 8.6157349597130242515e+1;
   double Q2    = 5.9578436142597344465e+1;
   double Q3    = 1.5024001160028576121e+1;
   double sqrt3 = 1.7320508075688772935e+0;
   double iims3 = 2.6794919243112270647e-1;
   double F, G, H, R, RN, RD;
   int    N, Sign;

   Sign = 0;
   F    = a;
   N    = 0;

   __vpred cmp_cond1 = __cmp_lt_pred(F, 0.0);
   F                 = __select(cmp_cond1, -F, F);
   Sign              = __select(cmp_cond1, 1, Sign);

   double  temp1     = divdpMod_atan2dpi(1.0, F);
   __vpred cmp_cond2 = __cmp_lt_pred(1.0, F);
   F                 = __select((cmp_cond2), temp1, F);
   N                 = __select((cmp_cond2), 2, N);

   double temp3_0 = (F * sqrt3) - 1.0;
   double temp3_1 = (F + sqrt3);
   double temp3   = divdpMod_atan2dpi(temp3_0, temp3_1);

   __vpred cmp_cond3 = __cmp_lt_pred(iims3, F);
   N                 = __select((cmp_cond3), N + 1, N);
   F                 = __select((cmp_cond3), temp3, F);

   H = F;
   H = _fabs(H);

   G  = H * H;
   RN = ((((((P3 * G) + P2) * G) + P1) * G) + P0) * G;
   RD = ((((((G + Q3) * G) + Q2) * G) + Q1) * G) + Q0;
   R  = divdpMod_atan2dpi(RN, RD);

   F = F + (F * R);

   __vpred cmp_cond4 = __cmp_gt_pred(N, 1);
   F                 = __select(__pdupl2b_pp(cmp_cond4), -F, F);

   H = F + ti_math_vTable[N];

   if (Sign == 1) {
      H = -H;
   }

   return (H);
}

template <typename T> static inline double atan2dp_i1(double a, double b, double c)
{
   double HalfPI     = 1.57079632679489661923;
   double MATHLIB_PI = 3.14159265358979323846;
   double X, Y, W, res_dvec;

   Y = a;
   X = b;
   W = c;

   res_dvec = W;

   double  res_pi = MATHLIB_PI + W;
   __vpred cond1  = __cmp_lt_pred(X, 0.0);
   __vpred cond2  = __cmp_lt_pred(0.0, W);
   res_pi         = __select(cond2, (W - MATHLIB_PI), res_pi);
   res_dvec       = __select(cond1, res_pi, res_dvec);

   __vpred cond3 = __cmp_eq_pred(X, 0.0);
   __vpred cond4 = __cmp_lt_pred(0.0, Y);

   double res1 = __select(cond4, HalfPI, -HalfPI);
   res_dvec    = __select(cond3, res1, res_dvec);

   __vpred cond5 = __cmp_eq_pred(Y, 0.0);
   __vpred cond6 = __cmp_le_pred(0.0, X);

   double res2 = __select(cond6, 0.0, MATHLIB_PI);
   res_dvec    = __select(cond5, res2, res_dvec);

   return (res_dvec);
}

template <typename T> static inline double atan2dp_i2(double a, double b, double c)
{
   double HalfPI = 1.57079632679489661923;
   double Maxv   = 1.7976931348623157e+308;
   double X, Y, Z, res_dVec;

   Y        = a;
   X        = b;
   res_dVec = c;

   Z = cmn_DIVDP(Y, X);

   __vpred cond7 = __cmp_lt_pred(Maxv, Z);
   res_dVec      = __select((cond7), HalfPI, res_dVec);

   __vpred cond8 = __cmp_lt_pred(Z, -Maxv);
   res_dVec      = __select(cond8, -HalfPI, res_dVec);

   return (res_dVec);
}

template <typename T>
static inline void MATHLIB_atan2_scalar(size_t length, T *restrict pSrc0, T *restrict pSrc1, T *restrict pDst)
{
   // Call scalar code
   for (size_t i = 0; i < length; i++) {
      pDst[i] = cmn_DIVDP(pSrc0[i], pSrc1[i]);
   }
   for (size_t i = 0; i < length; i++) {
      pDst[i] = atan2dpi(pDst[i]);
   }
   for (size_t i = 0; i < length; i++) {
      pDst[i] = atan2dp_i1<double>(pSrc0[i], pSrc1[i], pDst[i]);
   }
   for (size_t i = 0; i < length; i++) {
      pDst[i] = atan2dp_i2<double>(pSrc0[i], pSrc1[i], pDst[i]);
   }
}

// this method performs exponential computation of input vector
template <typename T> MATHLIB_STATUS MATHLIB_atan2(size_t length, T *pSrc0, T *pSrc1, T *pDst);

template <> MATHLIB_STATUS MATHLIB_atan2<float>(size_t length, float *pSrc0, float *pSrc1, float *pDst)
{
   MATHLIB_STATUS status = MATHLIB_SUCCESS; // return function status

   // check for null pointers and non-zero length
   status = MATHLIB_checkParams(length, pSrc0, pSrc1, pDst);

   // Calling Scalar operations for C7504 and vector operations for others
   if (status == MATHLIB_SUCCESS) {
      if (length < 2) {
         pDst[0] = MATHLIB_atan2_scalar_ci<float>(pSrc0[0], pSrc1[0]);
      }
      else {
         MATHLIB_atan2_vector<float>(length, pSrc0, pSrc1, pDst);
      }
   }
   return status;
}

template <> MATHLIB_STATUS MATHLIB_atan2<double>(size_t length, double *pSrc0, double *pSrc1, double *pDst)
{
   MATHLIB_STATUS status = MATHLIB_SUCCESS; // return function status

   // check for null pointers and non-zero length
   status = MATHLIB_checkParams(length, pSrc0, pSrc1, pDst);

   // Calling Scalar operations for C7504 and vector operations for others
   if (status == MATHLIB_SUCCESS) {
      MATHLIB_atan2_scalar<double>(length, pSrc0, pSrc1, pDst);
   }
   return status;
}

/******************************************************************************/
/*                                                                            */
/* C-interface wrapper functions                                              */
/*                                                                            */
/******************************************************************************/

extern "C" {

// single-precision wrapper
MATHLIB_STATUS MATHLIB_atan2_sp(size_t length, float *pSrc0, float *pSrc1, float *pDst)
{
   MATHLIB_STATUS status = MATHLIB_atan2<float>(length, pSrc0, pSrc1, pDst);
   return status;
}

// double-precision wrapper
MATHLIB_STATUS MATHLIB_atan2_dp(size_t length, double *pSrc0, double *pSrc1, double *pDst)
{
   MATHLIB_STATUS status = MATHLIB_atan2<double>(length, pSrc0, pSrc1, pDst);
   return status;
}

} // extern "C"
