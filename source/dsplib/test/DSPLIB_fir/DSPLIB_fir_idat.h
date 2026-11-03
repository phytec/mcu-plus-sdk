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
**|         Copyright (c) 2016 Texas Instruments Incorporated                |**
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

#ifndef DSPLIB_FIR_IXX_IXX_OXX_IDAT_H

#define DSPLIB_FIR_IXX_IXX_OXX_IDAT_H

#include <dsplib.h>

// include test infrastructure provided by MMALIB
#include "../common/DSPLIB_test.h"

typedef struct {
   uint8_t testPattern; /* 0: constant, 1: sequential, 2: random, 3: static
                           array, 4: file, etc */
   void    *staticIn;
   void    *filter;
   void    *staticOut;
   uint32_t dataType;
   uint32_t dataSize;
   uint32_t dataPitchIn;  // in bytes
   uint32_t dataPitchOut; // in bytes
   uint32_t batchSize;
   uint32_t filterSize;
   uint32_t filterPitch; // in bytes
   uint32_t enableNchCoefs;
   uint32_t enableMMA;
   uint32_t enableQ;
   uint32_t Q;
   uint32_t outputDataLocation; // 0 -> HEAP (probably L2SRAM), 1 -> MSMC
   uint32_t numReps;
   uint32_t testID;
} DSPLIB_fir_testParams_t;

void DSPLIB_fir_getTestParams(DSPLIB_fir_testParams_t **params, int32_t *numTests);

#endif /* define DSPLIB_FIR_IXX_IXX_OXX_IDAT_H */

/* ======================================================================== */
/*  End of file:  DSPLIB_firtestParams.h                                     */
/* ======================================================================== */
