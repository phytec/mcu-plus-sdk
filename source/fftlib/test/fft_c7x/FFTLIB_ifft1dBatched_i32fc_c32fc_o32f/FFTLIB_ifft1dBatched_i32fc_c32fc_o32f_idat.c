/*******************************************************************************
 **+--------------------------------------------------------------------------+**
 **|                            **** |**
 **|                            **** |**
 **|                            ******o*** |**
 **|                      ********_///_**** |**
 **|                      ***** /_//_/ **** |**
 **|                       ** ** (__/ **** |**
 **|                           ********* |**
 **|                            **** |**
 **|                            *** |**
 **| |**
 **|         Copyright (c) 2017 Texas Instruments Incorporated |**
 **|                        ALL RIGHTS RESERVED |**
 **| |**
 **| Permission to use, copy, modify, or distribute this software, |**
 **| whether in part or in whole, for any purpose is forbidden without |**
 **| a signed licensing agreement and NDA from Texas Instruments |**
 **| Incorporated (TI). |**
 **| |**
 **| TI makes no representation or warranties with respect to the |**
 **| performance of this computer program, and specifically disclaims |**
 **| any responsibility for any damages, special or consequential, |**
 **| connected with the use of this program. |**
 **| |**
 **+--------------------------------------------------------------------------+**
 *******************************************************************************/

#include "FFTLIB_ifft1dBatched_i32fc_c32fc_o32f_idat.h"
/* #include "../../common/TI_memory.h" */

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 2))
#include "test_data/extended_test_cases/staticRefCase2.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 3))
#include "test_data/extended_test_cases/staticRefCase3.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 4))
#include "test_data/extended_test_cases/staticRefCase4.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 5))
#include "test_data/extended_test_cases/staticRefCase5.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 6))
#include "test_data/extended_test_cases/staticRefCase6.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 7))
#include "test_data/extended_test_cases/staticRefCase7.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 8))
#include "test_data/extended_test_cases/staticRefCase8.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 9))
#include "test_data/extended_test_cases/staticRefCase9.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 10))
#include "test_data/extended_test_cases/staticRefCase10.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 11))
#include "test_data/extended_test_cases/staticRefCase11.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 12))
#include "test_data/extended_test_cases/staticRefCase12.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 13))
#include "test_data/extended_test_cases/staticRefCase13.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 14))
#include "test_data/extended_test_cases/staticRefCase14.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 15))
#include "test_data/extended_test_cases/staticRefCase15.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 16))
#include "test_data/extended_test_cases/staticRefCase16.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 17))
#include "test_data/extended_test_cases/staticRefCase17.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 18))
#include "test_data/extended_test_cases/staticRefCase18.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 19))
#include "test_data/extended_test_cases/staticRefCase19.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 20))
#include "test_data/extended_test_cases/staticRefCase20.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 21))
#include "test_data/extended_test_cases/staticRefCase21.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 22))
#include "test_data/extended_test_cases/staticRefCase22.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 23))
#include "test_data/extended_test_cases/staticRefCase23.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 24))
#include "test_data/extended_test_cases/staticRefCase24.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 25))
#include "test_data/extended_test_cases/staticRefCase25.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 26))
#include "test_data/extended_test_cases/staticRefCase26.h"
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 27))
#include "test_data/extended_test_cases/staticRefCase27.h"
#endif

static ifft1dBatched_i32fc_c32fc_o32f_testParams_t testParams[] = {
#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 2))
    {
        STATIC,        // test pattern
        staticRefIn2,  // staticIn0
        staticRefOut2, // staticOut
        128,           // numPoints
        1,             // numChannels
        2,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 3))
    {
        STATIC,        // test pattern
        staticRefIn3,  // staticIn0
        staticRefOut3, // staticOut
        256,           // numPoints
        1,             // numChannels
        3,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 4))
    {
        STATIC,        // test pattern
        staticRefIn4,  // staticIn0
        staticRefOut4, // staticOut
        512,           // numPoints
        1,             // numChannels
        4,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 5))
    {
        STATIC,        // test pattern
        staticRefIn5,  // staticIn0
        staticRefOut5, // staticOut
        1024,          // numPoints
        1,             // numChannels
        5,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 6))
    {
        STATIC,        // test pattern
        staticRefIn6,  // staticIn0
        staticRefOut6, // staticOut
        2048,          // numPoints
        1,             // numChannels
        6,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 7))
    {
        STATIC,        // test pattern
        staticRefIn7,  // staticIn0
        staticRefOut7, // staticOut
        4096,          // numPoints
        1,             // numChannels
        7,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 8))
    {
        STATIC,        // test pattern
        staticRefIn8,  // staticIn0
        staticRefOut8, // staticOut
        8192,          // numPoints
        1,             // numChannels
        8,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 9))
    {
        STATIC,        // test pattern
        staticRefIn9,  // staticIn0
        staticRefOut9, // staticOut
        128,           // numPoints
        2,             // numChannels
        9,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 10))
    {
        STATIC,         // test pattern
        staticRefIn10,  // staticIn0
        staticRefOut10, // staticOut
        256,            // numPoints
        2,              // numChannels
        10,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 11))
    {
        STATIC,         // test pattern
        staticRefIn11,  // staticIn0
        staticRefOut11, // staticOut
        512,            // numPoints
        2,              // numChannels
        11,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 12))
    {
        STATIC,         // test pattern
        staticRefIn12,  // staticIn0
        staticRefOut12, // staticOut
        1024,           // numPoints
        2,              // numChannels
        12,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 13))
    {
        STATIC,         // test pattern
        staticRefIn13,  // staticIn0
        staticRefOut13, // staticOut
        2048,           // numPoints
        2,              // numChannels
        13,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 14))
    {
        STATIC,         // test pattern
        staticRefIn14,  // staticIn0
        staticRefOut14, // staticOut
        4096,           // numPoints
        2,              // numChannels
        14,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 15))
    {
        STATIC,         // test pattern
        staticRefIn15,  // staticIn0
        staticRefOut15, // staticOut
        8192,           // numPoints
        2,              // numChannels
        15,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 16))
    {
        STATIC,         // test pattern
        staticRefIn16,  // staticIn0
        staticRefOut16, // staticOut
        128,            // numPoints
        4,              // numChannels
        16,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 17))
    {
        STATIC,         // test pattern
        staticRefIn17,  // staticIn0
        staticRefOut17, // staticOut
        256,            // numPoints
        4,              // numChannels
        17,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 18))
    {
        STATIC,         // test pattern
        staticRefIn18,  // staticIn0
        staticRefOut18, // staticOut
        512,            // numPoints
        4,              // numChannels
        18,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 19))
    {
        STATIC,         // test pattern
        staticRefIn19,  // staticIn0
        staticRefOut19, // staticOut
        1024,           // numPoints
        4,              // numChannels
        19,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 20))
    {
        STATIC,         // test pattern
        staticRefIn20,  // staticIn0
        staticRefOut20, // staticOut
        2048,           // numPoints
        4,              // numChannels
        20,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 21))
    {
        STATIC,         // test pattern
        staticRefIn21,  // staticIn0
        staticRefOut21, // staticOut
        4096,           // numPoints
        4,              // numChannels
        21,             // test ID
    },
#endif

// Known failure; fix TBD
/* #if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 22)) */
/*    { */
/*     STATIC,                                           // test pattern */
/*     staticRefIn22,                                    // staticIn0 */
/*     staticRefOut22,                                   // staticOut */
/*     8192,                                             // numPoints */
/*     4,                                                // numChannels */
/*     22,                                               // test ID */
/*     }, */
/* #endif */

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 23))
    {
        STATIC,         // test pattern
        staticRefIn23,  // staticIn0
        staticRefOut23, // staticOut
        128,            // numPoints
        16,             // numChannels
        23,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 24))
    {
        STATIC,         // test pattern
        staticRefIn24,  // staticIn0
        staticRefOut24, // staticOut
        256,            // numPoints
        16,             // numChannels
        24,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 25))
    {
        STATIC,         // test pattern
        staticRefIn25,  // staticIn0
        staticRefOut25, // staticOut
        512,            // numPoints
        16,             // numChannels
        25,             // test ID
    },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 26))
    {
        STATIC,         // test pattern
        staticRefIn26,  // staticIn0
        staticRefOut26, // staticOut
        1024,           // numPoints
        16,             // numChannels
        26,             // test ID
    },
#endif

    // Known failure; fix TBD
    /* #if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 200) || (TEST_CATEGORY == 100) || (TEST_CASE == 27)) */
    /*     { */
    /*         STATIC,         // test pattern */
    /*         staticRefIn27,  // staticIn0 */
    /*         staticRefOut27, // staticOut */
    /*         2048,           // numPoints */
    /*         16,             // numChannels */
    /*         27,             // test ID */
    /*     }, */
    /* #endif */

};

/*
 *  Sends the test parameter structure and number of tests
 */
void ifft1dBatched_i32fc_c32fc_o32f_getTestParams(ifft1dBatched_i32fc_c32fc_o32f_testParams_t** params,
                                                  int32_t*                                      numTests)
{
   *params   = testParams;
   *numTests = sizeof(testParams) / sizeof(ifft1dBatched_i32fc_c32fc_o32f_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2017 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
