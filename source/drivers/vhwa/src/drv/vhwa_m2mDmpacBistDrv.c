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
 *  \file vhwa_m2mDmpacBistDrv.c
 *
 *  \brief API Implementation for the DMPAC M2M Bist VHWA driver, used mainly
 *         for running LBIST or PBIST on DMPAC. See vhwa_m2mVpacBistDrv.c for
 *         the equivalent VPAC driver.
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
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    uint32_t                        isRegistered;
    VhwaAl_SemaphoreP_Struct        lock;
} Vhwa_M2mDmpacBistDrvInstObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Fdrv_Handle Vhwa_m2mDmpacBistCreate(UInt32 drvId, UInt32 drvInstId,
    Ptr createArgs, Ptr createStatusArgs, const Fvid2_DrvCbParams *cbPrms);
Int32 Vhwa_m2mDmpacBistDelete(Fdrv_Handle handle, Ptr deleteArgs);
Int32 Vhwa_m2mDmpacBistControl(Fdrv_Handle handle, UInt32 cmd, Ptr cmdArgs,
    Ptr cmdStatusArgs);


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

Fvid2_DrvOps gVhwaM2mDmpacBistDrvFvid2Ops = {
    FVID2_VHWA_M2M_DMPAC_BIST_DRV_ID,
    /**< Unique driver Id. */
    Vhwa_m2mDmpacBistCreate,
    /**< FVID2 create function pointer. */
    Vhwa_m2mDmpacBistDelete,
    /**< FVID2 delete function pointer. */
    Vhwa_m2mDmpacBistControl,
    /**< FVID2 control function pointer. */
    NULL, NULL,
    /**< FVID2 queue function pointer. */
    NULL,
    /**< FVID2 process request function pointer. */
    NULL,
    /**< FVID2 get processed request function pointer. */
};

Vhwa_M2mDmpacBistDrvInstObj gVhwaM2mDmpacBistDrvInstObj = {0};


/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Vhwa_m2mDmpacBistInit(void)
{
    int32_t                          status = FVID2_SOK;
    Vhwa_M2mDmpacBistDrvInstObj    *instObj = &gVhwaM2mDmpacBistDrvInstObj;
    #if !defined(MCU_PLUS_SDK)
    SemaphoreP_Params           params;
    #endif

    status = Fvid2_registerDriver(&gVhwaM2mDmpacBistDrvFvid2Ops);

    if (FVID2_SOK == status)
    {
        gVhwaM2mDmpacBistDrvInstObj.isRegistered = 1u;

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
            (void)Fvid2_unRegisterDriver(&gVhwaM2mDmpacBistDrvFvid2Ops);
            gVhwaM2mDmpacBistDrvInstObj.isRegistered = 0u;
        }
    }
    return (status);
}

int32_t Vhwa_m2mDmpacBistDeInit(void)
{
    if (1u == gVhwaM2mDmpacBistDrvInstObj.isRegistered)
    {
        (void)Fvid2_unRegisterDriver(&gVhwaM2mDmpacBistDrvFvid2Ops);
        gVhwaM2mDmpacBistDrvInstObj.isRegistered = 0u;
        #if defined(MCU_PLUS_SDK)
        SemaphoreP_destruct(&gVhwaM2mDmpacBistDrvInstObj.lock);
        #endif
    }

    #if !defined(MCU_PLUS_SDK)
    if (NULL != gVhwaM2mDmpacBistDrvInstObj.lock)
    {
        (void)SemaphoreP_delete(gVhwaM2mDmpacBistDrvInstObj.lock);
        gVhwaM2mDmpacBistDrvInstObj.lock = NULL;
    }
    #endif
    return (FVID2_SOK);
}

Fdrv_Handle Vhwa_m2mDmpacBistCreate(UInt32 drvId, UInt32 drvInstId,
    Ptr createArgs, Ptr createStatusArgs, const Fvid2_DrvCbParams *cbPrms)
{
    Fdrv_Handle             handle = NULL;

    if ((FVID2_VHWA_M2M_DMPAC_BIST_DRV_ID == drvId) && (0U == drvInstId))
    {
        handle = (Fdrv_Handle)&gVhwaM2mDmpacBistDrvInstObj;
    }

    return (handle);
}

Int32 Vhwa_m2mDmpacBistDelete(Fdrv_Handle handle, Ptr deleteArgs)
{
    int32_t status = FVID2_EFAIL;

    if ((Vhwa_M2mDmpacBistDrvInstObj *)handle == &gVhwaM2mDmpacBistDrvInstObj)
    {
        status = FVID2_SOK;
    }

    return (status);
}

Int32 Vhwa_m2mDmpacBistControl(Fdrv_Handle handle, UInt32 cmd, Ptr cmdArgs,
    Ptr cmdStatusArgs)
{
    int32_t                          status = FVID2_SOK;
    uint32_t                         cnt;
    Vhwa_M2mDmpacBistDrvInstObj    *instObj = NULL;

    if ((Vhwa_M2mDmpacBistDrvInstObj *)handle == &gVhwaM2mDmpacBistDrvInstObj)
    {
        instObj =  &gVhwaM2mDmpacBistDrvInstObj;
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
#ifdef VHWA_M2M_DMPAC_INSTANCE
            case VHWA_M2M_IOCTL_BIST_DMPAC_ACQUIRE_LOCK:
                for (cnt = VHWA_DMPAC_DOF_LOCK_IDX; cnt <= VHWA_DMPAC_SDE_LOCK_IDX; cnt ++)
                {
                    status = Vhwa_commonHwaLockAquire(cnt, SYSTEMP_WAIT_FOREVER);
                    if (FVID2_SOK != status)
                    {
                        GT_1trace(VhwaM2mBistTrace, GT_ERR,
                            "Failed to acquire semaphore for %d!!\n", cnt);
                        break;
                    }
                }
#if defined (VHWA_MCU_PLUS_SDK)
                Vhwa_m2mDofUnregisterIsrGlobal();
                Vhwa_m2mSdeUnregisterIsrGlobal();
#endif
                break;
            case VHWA_M2M_IOCTL_BIST_DMPAC_RELEASE_LOCK:
                /* Before Releasing the locks restore UTC registers */
                status = Vhwa_m2mDofReInit();

                if (FVID2_SOK == status)
                {
                    Vhwa_commonHwaLockRelease(VHWA_DMPAC_DOF_LOCK_IDX);
                }

                if (FVID2_SOK == status)
                {
                    status = Vhwa_m2mSdeReInit();
                }
                if (FVID2_SOK == status)
                {
                    Vhwa_commonHwaLockRelease(VHWA_DMPAC_SDE_LOCK_IDX);
                }
                break;
#endif
            default:
                status = FVID2_EINVALID_PARAMS;
                break;
        }
        (void)VhwaAl_SemaphoreP_post(instObj->lock);
    }

    return (status);
}
