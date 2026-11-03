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
**|        Copyright (c) 2025 Texas Instruments Incorporated                 |**
**|                                                                          |**
**|              All rights reserved not granted herein.                     |**
**|                                                                          |**
**|                         Limited License.                                 |**
**|                                                                          |**
**|  Texas Instruments Incorporated grants a world-wide, royalty-free,       |**
**|  non-exclusive license under copyrights and patents it now or            |**
**|  hereafter owns or controls to make, have made, use, import, offer to    |**
**|  sell and sell ("Utilize") this software subject to the terms herein.    |**
**|  With respect to the foregoing patent license, such license is granted   |**
**|  solely to the extent that any such patent is necessary to Utilize the   |**
**|  software alone.  The patent license shall not apply to any              |**
**|  combinations which include this software, other than combinations       |**
**|  with devices manufactured by or for TI ("TI Devices").  No hardware     |**
**|  patent is licensed hereunder.                                           |**
**|                                                                          |**
**|  Redistributions must preserve existing copyright notices and            |**
**|  reproduce this license (including the above copyright notice and the    |**
**|  disclaimer and (if applicable) source code license limitations below)   |**
**|  in the documentation and/or other materials provided with the           |**
**|  distribution                                                            |**
**|                                                                          |**
**|  Redistribution and use in binary form, without modification, are        |**
**|  permitted provided that the following conditions are met:               |**
**|                                                                          |**
**|    *  No reverse engineering, decompilation, or disassembly of this      |**
**|  software is permitted with respect to any software provided in binary   |**
**|  form.                                                                   |**
**|                                                                          |**
**|    *  any redistribution and use are licensed by TI for use only with    |**
**|  TI Devices.                                                             |**
**|                                                                          |**
**|    *  Nothing shall obligate TI to provide you with source code for      |**
**|  the software licensed and provided to you in object code.               |**
**|                                                                          |**
**|  If software source code is provided to you, modification and            |**
**|  redistribution of the source code are permitted provided that the       |**
**|  following conditions are met:                                           |**
**|                                                                          |**
**|    *  any redistribution and use of the source code, including any       |**
**|  resulting derivative works, are licensed by TI for use only with TI     |**
**|  Devices.                                                                |**
**|                                                                          |**
**|    *  any redistribution and use of any object code compiled from the    |**
**|  source code and any resulting derivative works, are licensed by TI      |**
**|  for use only with TI Devices.                                           |**
**|                                                                          |**
**|  Neither the name of Texas Instruments Incorporated nor the names of     |**
**|  its suppliers may be used to endorse or promote products derived from   |**
**|  this software without specific prior written permission.                |**
**|                                                                          |**
**|  DISCLAIMER.                                                             |**
**|                                                                          |**
**|  THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY      |**
**|  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE       |**
**|  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      |**
**|  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S LICENSORS BE      |**
**|  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR     |**
**|  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF    |**
**|  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR         |**
**|  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,   |**
**|  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE    |**
**|  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,       |**
**|  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#ifndef DSPLIB_CASCADEBIQUAD_H_
#define DSPLIB_CASCADEBIQUAD_H_

#include "../common/DSPLIB_types.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Number of coefficients per biquad
 *
 * @details
 *      This macro defines the number of coefficients per biquad.
 *
 * @note
 *      This macro is used in the cascade biquad kernel.
 *
 * @sa
 *      DSPLIB_cascadeBiquad
 */
#define DSPLIB_NUM_BIQUAD_COEFS     ( 5 )

/**
 * @brief Number of state variables per biquad in direct-form 1
 *
 * @details
 *      This macro defines the number of state variables per biquad.
 *      In direct-form 1, each biquad stage requires four state variables.
 *
 * @note
 *      This macro is used in the cascade biquad kernel.
 *
 * @sa
 *      DSPLIB_cascadeBiquad
 */
#define DSPLIB_NUM_STATE_VARS_DF1   ( 4 )

/**
 * @brief Number of state variables per biquad in direct-form 2
 *
 * @details
 *      This macro defines the number of state variables per biquad.
 *      In direct-form 2, each biquad stage requires two state variables.
 *
 * @note
 *      This macro is used in the cascade biquad kernel.
 *
 * @sa
 *      DSPLIB_cascadeBiquad
 */
#define DSPLIB_NUM_STATE_VARS_DF2   ( 2 )

/**
 * @defgroup DSPLIB_cascadeBiquad DSPLIB_cascadeBiquad
 *
 * @brief Kernel for multichannel multistage cascade on input data
 *
 * @details
 *          The kernel supports computation of biquads of a vector of several
 *          inputs in one kernel call.
 *
 * @ingroup DSPLIB
 */
/**@{**/

/**
 * @brief Enumeration for biquad realization form
 *
 * @details This enumeration defines the type of biquad realization.
 *          - DSPLIB_BIQUAD_TIF  : TI Form
 *          - DSPLIB_BIQUAD_DF1  : Direct Form I
 *          - DSPLIB_BIQUAD_DF2  : Direct Form II
 *          - DSPLIB_BIQUAD_TDF2 : Transposed Direct Form II
 */
typedef enum {
   /** @brief TI Form */
   DSPLIB_BIQUAD_TIF = 0,
   /** @brief Direct Form I */
   DSPLIB_BIQUAD_DF1 = 1,
   /** @brief Direct Form II */
   DSPLIB_BIQUAD_DF2 = 2,
   /** @brief Transposed Direct Form II */
   DSPLIB_BIQUAD_TDF2 = 3,

} DSPLIB_biquadForm;

/**
 * @brief Structure containing the parameters to initialize the kernel
 */
typedef struct {
   /** @brief Variant of the function refer to @ref DSPLIB_FUNCTION_STYLE     */
   int8_t funcStyle;
   /** @brief Size of input data                                              */
   uint32_t dataSize;
   /** @brief number of stages                                                */
   uint32_t numStages;
   /** @brief number of channels                                              */
   uint32_t numChannels;
   /** @brief Flag to enable per channel filter coefficients:
    *         0 => same coefficients for all channels
    *         1 => different coefficients for each channel                    */
   uint32_t enableNChCoeffs;
   /** @brief biquad realization form                                         */
   uint32_t biquadForm;

} DSPLIB_cascadeBiquad_InitArgs;

/**
 *  @brief        This is a query function to calculate the size of internal
 *                handle
 *  @param [in]   pKerInitArgs  : Pointer to structure holding init parameters
 *  @return       Size of the buffer in bytes
 *  @remarks      Application is expected to allocate buffer of the requested
 *                size and provide it as input to other functions requiring it.
 */
int32_t DSPLIB_cascadeBiquad_getHandleSize(DSPLIB_cascadeBiquad_InitArgs *pKerInitArgs);

/**
 * @brief Get coefficient buffer descriptor for optimized cascade biquad.
 *
 * @param [in] dataType     : Type of the data in the buffer.
 *                           Supported data types are:
 *                           - @ref DSPLIB_FLOAT32
 * @param [in] numStages    : Number of cascade stages
 * @param [in] numChannels   : Number of channels
 * @param [in] biquadForm   : Type of the biquad realization.
 *                           Supported forms are:
 *                           - @ref DSPLIB_BIQUAD_TIF
 *                           - @ref DSPLIB_BIQUAD_DF1
 *                           - @ref DSPLIB_BIQUAD_DF2
 *                           - @ref DSPLIB_BIQUAD_TDF2
 * @param [in] enableNChCoeffs: Flag to enable per channel filter coefficients.
 *                           - 0 => same coefficients for all channels
 *                           - 1 => different coefficients for each channel
 * @param [in,out] pBufParamsFilterCoeffOpt : Pointer to the buffer descriptor.
 *
 * @return      Status value indicating success or failure. Refer to @ref DSPLIB_STATUS.
 *
 * @remarks The application is expected to allocate the buffer
 * using the dimension information in the returned buffer descriptor.
 */
DSPLIB_STATUS DSPLIB_cascadeBiquad_get_coefficientsBufferDesc(uint32_t dataType,
                                                              uint32_t numStages,
                                                              uint32_t numChannels,
                                                              uint32_t biquadForm,
                                                              uint32_t enableNChCoeffs,
                                                              DSPLIB_bufParams2D_t *pBufParamsFilterCoeffOpt);

/**
 * @brief Helper function to get the coefficients for the optimized cascade biquad.
 *
 * @param [in] numStages    : Number of cascade stages
 * @param [in,out] pBufParamsFilterCoeffCn   : Pointer to the coefficient buffer descriptor for the
 * @param [in,out] pBufParamsFilterCoeff     : Pointer to the coefficient buffer descriptor for the optimized code
 * @param [in] pFilterCoeff      : Pointer to the coefficients buffer
 * @param [in] pFilterCoeffOpt   : Pointer to the coefficients buffer for optimized code.
 *
 * @return      Status value indicating success or failure. Refer to @ref DSPLIB_STATUS.
 *
 * @remarks Calculates the optimized coefficients for the cascade biquad.
 *
 */
DSPLIB_STATUS DSPLIB_cascadeBiquad_get_coefficients(uint32_t biquadForm, 
                                                    uint32_t enableNChCoeffs,
                                                    DSPLIB_bufParams2D_t *pBufParamsFilterCoeff,
                                                    DSPLIB_bufParams2D_t *pBufParamsFilterCoeffOpt,
                                                    const void *restrict pFilterCoeff,
                                                    const void *restrict pFilterCoeffOpt);

/**
 *  @brief       This function should be called before the
 *               @ref DSPLIB_cascadeBiquad_exec function is called. This
 *               function takes care of any one-time operations such as setting up
 *               the configuration of required hardware resources such as the streaming engines. 
 *               The results of these operations are stored in the handle.
 *
 *  @param [in]  handle       :  Active handle to the kernel
 *  @param [in]  bufParamsIn  :  Pointer to the structure containing dimensional
 *                               information of input buffer
 *  @param [in]  bufParamsFilter :  Pointer to the structure containing dimensional
 *                               information of filter buffer
 *  @param [out] bufParamsOut :  Pointer to the structure containing dimensional
 *                               information of ouput buffer
 *  @param [in]  pKerInitArgs :  Pointer to the structure holding init parameters
 *
 *  @return      Status value indicating success or failure. Refer to @ref DSPLIB_STATUS.
 *
 *  @remarks     Application is expected to provide a valid handle.
 */
DSPLIB_STATUS DSPLIB_cascadeBiquad_init(DSPLIB_kernelHandle            handle,
                                        DSPLIB_bufParams2D_t          *bufParamsIn,
                                        DSPLIB_bufParams2D_t          *bufParamsFilterCoeff,
                                        DSPLIB_bufParams2D_t          *bufParamsFilterVar,
                                        DSPLIB_bufParams2D_t          *bufParamsOut,
                                        DSPLIB_cascadeBiquad_InitArgs *pKerInitArgs);

/**
 *  @brief       This function checks the validity of the parameters passed to
 *               @ref DSPLIB_cascadeBiquad_init function. This function
 *               is called with the same parameters as the
 *               @ref DSPLIB_cascadeBiquad_init, and this function
 *               must be called before the
 *               @ref DSPLIB_cascadeBiquad_init is called.
 *
 *  @param [in]  handle       :  Active handle to the kernel
 *  @param [in]  bufParamsIn  :  Pointer to the structure containing dimensional
 *                               information of input buffer
 *  @param [in]  bufParamsFilter :  Pointer to the structure containing dimensional
 *                               information of filter buffer
 *  @param [out] bufParamsOut :  Pointer to the structure containing dimensional
 *                               information of output buffer
 *  @param [in]  pKerInitArgs :  Pointer to the structure holding init parameters
 *
 *  @return      Status value indicating success or failure. Refer to @ref DSPLIB_STATUS.
 *
 *  @remarks     None
 */
DSPLIB_STATUS DSPLIB_cascadeBiquad_init_checkParams(DSPLIB_kernelHandle                  handle,
                                                    const DSPLIB_bufParams2D_t          *bufParamsIn,
                                                    const DSPLIB_bufParams2D_t          *bufParamsFilterCoeff,
                                                    const DSPLIB_bufParams2D_t          *bufParamsFilterVar,
                                                    const DSPLIB_bufParams2D_t          *bufParamsOut,
                                                    const DSPLIB_cascadeBiquad_InitArgs *pKerInitArgs);

/**
 *  @brief       This function is the main kernel compute function.
 *
 *  @details     Please refer to details under
 *               @ref DSPLIB_cascadeBiquad
 *
 *  @param [in]  handle      : Active handle to the kernel
 *  @param [in]  pIn         : Pointer to buffer holding the input data
 *  @param [in]  pFilter     : Pointer to buffer holding the filter data
 *  @param [out] pOut        : Pointer to buffer holding the output data
 *
 *  @return      Status value indicating success or failure. Refer to @ref DSPLIB_STATUS.
 *
 *  @par Assumptions:
 *    - None
 *
 *  @par Performance Considerations:
 *    For best performance,
 *    - the input and output data buffers are expected to be in L2 memory
 *    - the buffer pointers are assumed to be 64-byte aligned
 *
 *  @remarks     Before calling this function, application is expected to call
 *               @ref DSPLIB_cascadeBiquad_init and
 *               @ref DSPLIB_cascadeBiquad_exec_checkParams functions.
 *               This ensures resource configuration and error checks are done only
 *               once for several invocations of this function.
 */
DSPLIB_STATUS DSPLIB_cascadeBiquad_exec(DSPLIB_kernelHandle handle,
                                        void *restrict pIn,
                                        void *restrict pFilterCoeff,
                                        void *restrict pFilterVar,
                                        void *restrict pOut);

/**
 *  @brief       This function checks the validity of the parameters passed to
 *               @ref DSPLIB_cascadeBiquad_exec function. This function
 *               is called with the same parameters as the
 *               @ref DSPLIB_cascadeBiquad_exec, and this function
 *               must be called before the
 *               @ref DSPLIB_cascadeBiquad_exec is called.
 *
 *  @param [in]  handle      : Active handle to the kernel
 *  @param [in]  pIn         : Pointer to buffer holding the input data
 *  @param [in]  pFilter     : Pointer to buffer holding the input data
 *  @param [out] pOut        : Pointer to buffer holding the output matrix
 *
 *  @return      Status value indicating success or failure. Refer to @ref DSPLIB_STATUS.
 *
 *  @remarks     None
 */
DSPLIB_STATUS DSPLIB_cascadeBiquad_exec_checkParams(DSPLIB_kernelHandle handle,
                                                    const void *restrict pIn,
                                                    const void *restrict pFilterCoeff,
                                                    const void *restrict pFilterVar,
                                                    const void *restrict pOut);

/**
 *  @brief       This is a utility function that gives an estimate of the cycles
 *               consumed for the kernel execution.
 *
 *  @param [in]  handle       :  Active handle to the kernel
 *  @param [in]  bufParamsIn  :  Pointer to the structure containing dimensional
 *                               information of the input buffer
 *  @param [in]  bufParamsFilter  :  Pointer to the structure containing dimensional
 *                               information of the filter buffer
 *  @param [in]  bufParamsOut :  Pointer to the structure containing dimensional
 *                               information of the output buffer
 *  @param [out] archCycles   :  Cycles estimated for the compute, startup and
 *                               teardown
 *  @param [out] estCycles    :  Cycles estimated for the compute, startup,
 *                               teardown and any associated overhead
 *  @remarks     None
 */
void DSPLIB_cascadeBiquad_perfEst(DSPLIB_kernelHandle         handle,
                                  const DSPLIB_bufParams2D_t *bufParamsIn,
                                  const DSPLIB_bufParams2D_t *bufParamsFilterCoeff,
                                  const DSPLIB_bufParams2D_t *bufParamsFilterVar,
                                  const DSPLIB_bufParams2D_t *bufParamsOut,
                                  uint64_t                   *archCycles,
                                  uint64_t                   *estCycles);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* DSPLIB_CASCADEBIQUAD_H_ */

/* ======================================================================== */
/*  End of file:  DSPLIB_cascadeBiquad.h                                    */
/* ======================================================================== */
