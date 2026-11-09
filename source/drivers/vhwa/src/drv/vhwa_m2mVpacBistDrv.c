/**
 *   Copyright (c) Texas Instruments Incorporated 2025
 *   All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
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
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file vhwa_m2mVpacBistDrv.c
 *
 *  \brief API Implementation for the VPAC M2M Bist VHWA driver, used mainly for
 *         running LBIST or PBIST on VPAC0/VPAC1. See vhwa_m2mDmpacBistDrv.c for
 *         the equivalent DMPAC driver.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <vhwa_dmpac_abstraction_layer.h>
#include <include/vhwa_common.h>
#include <include/vhwa_m2mBist.h>
#include "src/drv/vhwa_utils.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */


#define VHWA_M2M_BIST_VPAC0_UTC0_IDX               (0)
#define VHWA_M2M_BIST_VPAC0_UTC1_IDX               (1)
#define VHWA_M2M_BIST_VPAC1_UTC0_IDX               (2)
#define VHWA_M2M_BIST_VPAC1_UTC1_IDX               (3)

#if defined(VHWA_M2M_VPAC_INSTANCE)
    #if (VHWA_M2M_VPAC_INSTANCE == 0)
        #define VHWA_M2M_BIST_VPAC0_UTC_BASE_ADDR          (CSL_VPAC0_DRU_UTC_VPAC1_DRU_MMR_CFG_DRU_DRU_BASE)
    #endif

    #if (VHWA_M2M_VPAC_INSTANCE == 1)
        #define VHWA_M2M_BIST_VPAC1_UTC_BASE_ADDR          (CSL_VPAC1_DRU_UTC_VPAC1_DRU_MMR_CFG_DRU_DRU_BASE)
    #endif
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    uint32_t                        isRegistered;
    VhwaAl_SemaphoreP_Struct        lock;
} Vhwa_M2mVpacBistDrvInstObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Fdrv_Handle Vhwa_m2mVpacBistCreate(UInt32 drvId, UInt32 drvInstId,
    Ptr createArgs, Ptr createStatusArgs, const Fvid2_DrvCbParams *cbPrms);
Int32 Vhwa_m2mVpacBistDelete(Fdrv_Handle handle, Ptr deleteArgs);
Int32 Vhwa_m2mVpacBistControl(Fdrv_Handle handle, UInt32 cmd, Ptr cmdArgs,
    Ptr cmdStatusArgs);


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

Fvid2_DrvOps gVhwaM2mVpacBistDrvFvid2Ops = {
    FVID2_VHWA_M2M_VPAC_BIST_DRV_ID,
    /**< Unique driver Id. */
    Vhwa_m2mVpacBistCreate,
    /**< FVID2 create function pointer. */
    Vhwa_m2mVpacBistDelete,
    /**< FVID2 delete function pointer. */
    Vhwa_m2mVpacBistControl,
    /**< FVID2 control function pointer. */
    NULL, NULL,
    /**< FVID2 queue function pointer. */
    NULL,
    /**< FVID2 process request function pointer. */
    NULL,
    /**< FVID2 get processed request function pointer. */
};

Vhwa_M2mVpacBistDrvInstObj gVhwaM2mVpacBistDrvInstObj = {0};


/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Vhwa_m2mVpacBistInit(void)
{
    int32_t                     status = FVID2_SOK;
    Vhwa_M2mVpacBistDrvInstObj    *instObj = &gVhwaM2mVpacBistDrvInstObj;
    #if !defined(MCU_PLUS_SDK)
    SemaphoreP_Params           params;
    #endif

    status = Fvid2_registerDriver(&gVhwaM2mVpacBistDrvFvid2Ops);

    if (FVID2_SOK == status)
    {
        gVhwaM2mVpacBistDrvInstObj.isRegistered = 1u;

        /* Allocate lock semaphore */
        #if defined(MCU_PLUS_SDK)
        if(FVID2_SOK != SemaphoreP_constructBinary(&instObj->lock,1U))
        #else
        SemaphoreP_Params_init(&params);
        params.mode = SemaphoreP_Mode_BINARY;
        instObj->lock = SemaphoreP_create(1U, &params);
        if (NULL == instObj->lock)
        #endif
        {
            GT_0trace(VhwaM2mBistTrace, GT_ERR,
                "Failed to allocate instance semaphore!!\n");
            status = FVID2_EALLOC;
            (void)Fvid2_unRegisterDriver(&gVhwaM2mVpacBistDrvFvid2Ops);
            gVhwaM2mVpacBistDrvInstObj.isRegistered = 0u;
        }
    }
    return (status);
}

int32_t Vhwa_m2mVpacBistDeInit(void)
{
    if (1u == gVhwaM2mVpacBistDrvInstObj.isRegistered)
    {
        (void)Fvid2_unRegisterDriver(&gVhwaM2mVpacBistDrvFvid2Ops);
        gVhwaM2mVpacBistDrvInstObj.isRegistered = 0u;
        #if defined(MCU_PLUS_SDK)
        SemaphoreP_destruct(&gVhwaM2mVpacBistDrvInstObj.lock);
        #endif
    }

    #if !defined(MCU_PLUS_SDK)
    if (NULL != gVhwaM2mVpacBistDrvInstObj.lock)
    {
        (void)SemaphoreP_delete(gVhwaM2mVpacBistDrvInstObj.lock);
        gVhwaM2mVpacBistDrvInstObj.lock = NULL;
    }
    #endif
    return (FVID2_SOK);
}

Fdrv_Handle Vhwa_m2mVpacBistCreate(UInt32 drvId, UInt32 drvInstId,
    Ptr createArgs, Ptr createStatusArgs, const Fvid2_DrvCbParams *cbPrms)
{
    Fdrv_Handle             handle = NULL;

    if ((FVID2_VHWA_M2M_VPAC_BIST_DRV_ID == drvId) && (0U == drvInstId))
    {
        handle = (Fdrv_Handle)&gVhwaM2mVpacBistDrvInstObj;
    }

    return (handle);
}

Int32 Vhwa_m2mVpacBistDelete(Fdrv_Handle handle, Ptr deleteArgs)
{
    int32_t status = FVID2_EFAIL;

    if ((Vhwa_M2mVpacBistDrvInstObj *)handle == &gVhwaM2mVpacBistDrvInstObj)
    {
        status = FVID2_SOK;
    }

    return (status);
}

Int32 Vhwa_m2mVpacBistControl(Fdrv_Handle handle, UInt32 cmd, Ptr cmdArgs,
    Ptr cmdStatusArgs)
{
    int32_t                     status = FVID2_SOK;
    uint32_t                    cnt;
    Vhwa_M2mVpacBistDrvInstObj    *instObj = NULL;

    if ((Vhwa_M2mVpacBistDrvInstObj *)handle == &gVhwaM2mVpacBistDrvInstObj)
    {
        instObj =  &gVhwaM2mVpacBistDrvInstObj;
        status = FVID2_SOK;
    }
    else
    {
        status = FVID2_EFAIL;
    }
    if (FVID2_SOK == status)
    {
        (void)VhwaAl_SemaphoreP_pend(instObj->lock, SYSTEMP_WAIT_FOREVER);
        switch (cmd)
        {
#ifdef VHWA_M2M_VPAC_INSTANCE
#if (VHWA_M2M_VPAC_INSTANCE == 0)
            case VHWA_M2M_IOCTL_BIST_VPAC0_ACQUIRE_LOCK:

                for (cnt = VHWA_VPAC0_VISS_LOCK_IDX; cnt <= VHWA_VPAC0_LOCK_IDX_MAX; cnt ++)
                {
                    status = Vhwa_commonHwaLockAquire(cnt, SYSTEMP_WAIT_FOREVER);
                    if (FVID2_SOK != status)
                    {
                        GT_1trace(VhwaM2mBistTrace, GT_ERR,
                            "Failed to acquire semaphore for %d!!\n", cnt);
                        break;
                    }
                }
#if defined(VHWA_MCU_PLUS_SDK)
                /* Need to unregister ISRs, so they can be re-registered on release */
                Vhwa_m2mVissUnregisterIsrGlobal();
                Vhwa_m2mLdcUnregisterIsrGlobal();
                Vhwa_m2mMscUnregisterIsrGlobal();
#endif
                break;
            case VHWA_M2M_IOCTL_BIST_VPAC0_RELEASE_LOCK:
                /* Before releasing lock, restore the registers of UTC */

                /* Since driver does not support multiple instances of the modules,
                   calling these APIs without any arguments.. */
                status = Vhwa_m2mVissReInit();

                if (FVID2_SOK == status)
                {
                    Vhwa_commonHwaLockRelease(VHWA_VPAC0_VISS_LOCK_IDX);
                }
                
                if (FVID2_SOK == status)
                {
                    status = Vhwa_m2mLdcReInit();
                }
                if (FVID2_SOK == status)
                {
                    Vhwa_commonHwaLockRelease(VHWA_VPAC0_LDC_LOCK_IDX);
                }
                
                if (FVID2_SOK == status)
                {
                    status = Vhwa_m2mMscReInit();
                }
                if (FVID2_SOK == status)
                {
                    Vhwa_commonHwaLockRelease(VHWA_VPAC0_MSC0_LOCK_IDX);
                }
                if (FVID2_SOK == status)
                {
                    Vhwa_commonHwaLockRelease(VHWA_VPAC0_MSC1_LOCK_IDX);
                }

                #if !defined(SOC_AM62A) && !defined(SOC_J722S)
                if (FVID2_SOK == status)
                {
                    status = Vhwa_m2mNfReInit();
                }
                
                if (FVID2_SOK == status)
                {
                    Vhwa_commonHwaLockRelease(VHWA_VPAC0_NF_LOCK_IDX);
                }                
                #endif
                break;
#endif

#if (VHWA_M2M_VPAC_INSTANCE == 1)
            case VHWA_M2M_IOCTL_BIST_VPAC1_ACQUIRE_LOCK:
                for (cnt = VHWA_VPAC1_VISS_LOCK_IDX; cnt <= VHWA_VPAC1_NF_LOCK_IDX; cnt ++)
                {
                    status = Vhwa_commonHwaLockAquire(cnt, SYSTEMP_WAIT_FOREVER);
                    if (FVID2_SOK != status)
                    {
                        GT_1trace(VhwaM2mBistTrace, GT_ERR,
                            "Failed to acquire semaphore for %d!!\n", cnt);
                        break;
                    }
                }

                break;
            case VHWA_M2M_IOCTL_BIST_VPAC1_RELEASE_LOCK:
                /* Before Releasing the locks restore UTC registers */

                /* Since driver does not support multiple instances of the modules,
                   calling these APIs without any arguments.. */
                status = Vhwa_m2mVissReInit();

                if (FVID2_SOK == status)
                {
                    Vhwa_commonHwaLockRelease(VHWA_VPAC1_VISS_LOCK_IDX);
                }
                
                if (FVID2_SOK == status)
                {
                    status = Vhwa_m2mLdcReInit();
                }
                if (FVID2_SOK == status)
                {
                    Vhwa_commonHwaLockRelease(VHWA_VPAC1_LDC_LOCK_IDX);
                }
                
                if (FVID2_SOK == status)
                {
                    status = Vhwa_m2mMscReInit();
                }
                if (FVID2_SOK == status)
                {
                    Vhwa_commonHwaLockRelease(VHWA_VPAC1_MSC0_LOCK_IDX);
                }
                if (FVID2_SOK == status)
                {
                    Vhwa_commonHwaLockRelease(VHWA_VPAC1_MSC1_LOCK_IDX);
                }

                #if !defined(SOC_AM62A) && !defined(SOC_J722S)
                if (FVID2_SOK == status)
                {
                    status = Vhwa_m2mNfReInit();
                }
                
                if (FVID2_SOK == status)
                {
                    Vhwa_commonHwaLockRelease(VHWA_VPAC1_NF_LOCK_IDX);
                }                
                #endif
                break;
#endif
#endif

            default:
                status = FVID2_EINVALID_PARAMS;
                break;
        }
        (void)VhwaAl_SemaphoreP_post(instObj->lock);
    }

    return (status);
}
