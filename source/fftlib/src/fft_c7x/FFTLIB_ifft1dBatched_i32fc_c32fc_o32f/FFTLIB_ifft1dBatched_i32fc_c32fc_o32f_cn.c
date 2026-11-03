/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|         Copyright (c) 2017 Texas Instruments Incorporated                |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission to use, copy, modify, or distribute this software,            |**
**| whether in part or in whole, for any purpose is forbidden without        |**
**| a signed licensing agreement and NDA from Texas Instruments              |**
**| Incorporated (TI).                                                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#include "FFTLIB_ifft1dBatched_i32fc_c32fc_o32f_cn.h"

FFTLIB_STATUS
FFTLIB_ifft1dBatched_i32fc_c32fc_o32f_cn(FFTLIB_F32           *pX,
                                         FFTLIB_bufParams1D_t *bufParamsX,
                                         FFTLIB_F32           *pW,
                                         FFTLIB_bufParams1D_t *bufParamsW,
                                         FFTLIB_F32           *pXFFT,
                                         FFTLIB_bufParams1D_t *bufParamsXFFT,
                                         FFTLIB_F32           *pSf,
                                         FFTLIB_bufParams1D_t *bufParamsSf,
                                         FFTLIB_F32           *pY,
                                         FFTLIB_bufParams1D_t *bufParamsY,
                                         uint32_t              numPoints,
                                         uint32_t              numChannels)
{
   FFTLIB_STATUS        status = FFTLIB_SUCCESS;
   FFTLIB_bufParams1D_t bufParamsX_FFT;

   /* #ifdef FFTLIB_CHECK_PARAMS */
   /*    status = FFTLIB_ifft1dBatched_i32fc_c32fc_o32f_checkParams_cn ( */
   /*        pX, bufParamsX, pW, bufParamsW, pY, bufParamsY); */
   /*    if (status == FFTLIB_SUCCESS) */
   /* #endif */

   uint32_t N_2 = numPoints >> 1;

   uint32_t ch;
   // TODO: loop through each channel and change indexing
   for (ch = 0; ch < numChannels; ch++) {
      uint32_t i = 0;
      uint32_t c = 0;

      FFTLIB_F32 temp0Real;
      FFTLIB_F32 temp0Imag;
      FFTLIB_F32 temp1Real;
      FFTLIB_F32 temp1Imag;

      FFTLIB_F32 var0Real;
      FFTLIB_F32 var0Imag;
      FFTLIB_F32 var1Real;
      FFTLIB_F32 var1Imag;

      c = (ch * (2 * numPoints));

      for (i = 0; i < N_2; i++) {
         var0Real  = pX[c + 2 * i];
         var0Imag  = pX[c + 2 * i + 1];
         temp0Real = var0Real * pSf[2 * i] - (var0Imag * pSf[2 * i + 1]);
         temp0Imag = var0Real * pSf[2 * i + 1] + (var0Imag * pSf[2 * i]);

         var1Real  = pX[c + 2 * i + numPoints];
         var1Imag  = pX[c + 2 * i + 1 + numPoints];
         temp1Real = var1Real * pSf[2 * i + numPoints] - (var1Imag * pSf[2 * i + 1 + (numPoints)]);
         temp1Imag = var1Real * pSf[2 * i + 1 + numPoints] + (var1Imag * pSf[2 * i + numPoints]);

         pXFFT[(c >> 1) + 2 * i]     = temp0Real + temp1Real;
         pXFFT[(c >> 1) + 2 * i + 1] = temp0Imag + temp1Imag;
      }
   }

   FFTLIB_ifft1dBatched_i32fc_c32fc_o32fc_cn(pXFFT, &bufParamsX_FFT, pW, &bufParamsX_FFT, pY, &bufParamsX_FFT,
                                             numPoints / 2, numChannels);

   return (status);
}

FFTLIB_STATUS
FFTLIB_ifft1dBatched_i32fc_c32fc_o32f_checkParams_cn(FFTLIB_F32           *pX,
                                                     FFTLIB_bufParams1D_t *bufParamsX,
                                                     FFTLIB_F32           *pW,
                                                     FFTLIB_bufParams1D_t *bufParamsW,
                                                     FFTLIB_F32           *pY,
                                                     FFTLIB_bufParams1D_t *bufParamsY)
{
   FFTLIB_STATUS status = FFTLIB_SUCCESS;

   /* if ((pX == NULL) || (pW == NULL) || (pY == NULL)) { */
   /*    status = FFTLIB_ERR_NULL_POINTER; */
   /* } */
   /* else if (bufParamsX->dim_x != bufParamsW->dim_x || */
   /*          bufParamsX->dim_x != bufParamsY->dim_x) { */
   /*    status = FFTLIB_ERR_INVALID_DIMENSION; */
   /* } */
   /* else if ((bufParamsX->data_type != FFTLIB_FLOAT32) || */
   /*          (bufParamsW->data_type != FFTLIB_FLOAT32) || */
   /*          (bufParamsY->data_type != FFTLIB_FLOAT32)) { */
   /*    status = FFTLIB_ERR_INVALID_TYPE; */
   /* } */
   /* else { */
   /*    /\* Check if number of pts is a power of 2 *\/ */
   /*    uint32_t k = 0; */
   /*    while (k < 32) { */
   /*       if (bufParamsX->dim_x & (1u << k)) { */
   /*          break; */
   /*       } */
   /*       k++; */
   /*    } */
   /*    if ((1u << k) != bufParamsX->dim_x) { */
   /*       status = FFTLIB_ERR_INVALID_DIMENSION; */
   /*    } */
   /* } */
   return (status);
}
