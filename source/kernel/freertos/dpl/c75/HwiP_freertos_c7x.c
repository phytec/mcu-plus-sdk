/*
 * Copyright (c) 2015-2025, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  ======== HwiP_freeRtos_c7x.c ========
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>

#include <kernel/dpl/HwiP.h>
#include <drivers/hw_include/cslr_soc.h>
#include <kernel/nortos/dpl/c75/csl_clec.h>
#include <c75_clec_base_address.h>
#include <kernel/nortos/dpl/c75/HwiP_c75.h>

#include <FreeRTOS.h>
#include "portmacro.h"
#include <task.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define DPL_FREERTOS_C7X_CONFIGNUM_HWI                 (64U)

#ifndef NULL_PTR
#define NULL_PTR ((void *)0x0)
#endif

#define  HWIP_USE_DEFAULT_PRIORITY   (~((uint8_t)0))

#pragma FUNC_EXT_CALLED(Hwi_dispatchC);

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

typedef struct HwiP_freeRtos_s {
    bool              used;
    HwiC7x_Struct        hwi;
} HwiP_freeRtos;

typedef struct HwiP_Struct_s {

    uint32_t intNum;

} HwiP_Struct;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* global pool of statically allocated semaphore pools */
static HwiP_freeRtos gOsalHwiPFreeRtosPool[DPL_FREERTOS_C7X_CONFIGNUM_HWI];
static CSL_CLEC_EVTRegs* Hwip_getClecBaseAddr(void);

uint32_t  gOsalHwiAllocCnt   = 0U, gOsalHwiPeak = 0U;
extern uint32_t ulPortInterruptNesting;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void HwiP_enable(void)
{
    return;
}

uintptr_t HwiP_disable(void)
{
    uintptr_t key = (uintptr_t)NULL;

    if(( xPortInIsrContext() == true ) ||
       ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED ))
    {
        key = Hwi_disable();
    }
    else
    {
        portENTER_CRITICAL();
    }

    return (key);
}

void HwiP_restore(uintptr_t key)
{
    if(( xPortInIsrContext() == true ) ||
       ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED ))
    {
        (void)Hwi_restore((uint32_t)key);
    }
    else
    {
        portEXIT_CRITICAL();
    }

    return;
}

/*
 *  ======== Hwi_dispatchC ========
 *  Configurable dispatcher.
 */
void Hwi_dispatchC(int intNum)
{
    extern uint32_t ulPortYieldRequired;

    ulPortInterruptNesting++;

    Hwi_switchAndDispatch(intNum);

    ulPortInterruptNesting--;
    if (ulPortInterruptNesting == 0U)
    {
        if (ulPortYieldRequired != (uint32_t)pdFALSE)
        {
            ulPortYieldRequired = pdFALSE;
            vPortYieldAsyncFromISR();
        }

    }

}

uint32_t HwiP_inISR(void)
{
    uint32_t stat = 0U;

    if (ulPortInterruptNesting != 0U)
    {
        stat =  1U;
    }
    return stat;
}

int32_t HwiP_construct(HwiP_Object *object, HwiP_Params *params)
{
    HwiP_Struct *obj = (HwiP_Struct *)object;
    HwiP_freeRtos *handle = (HwiP_freeRtos *) NULL_PTR;
    Hwi_Params  hwiParams;
    uint32_t          i;
    uintptr_t         key;
    HwiP_freeRtos      *hwiPool;
    uint32_t          maxHwi;
    int32_t status;
    int iStat;

    DebugP_assertNoLog( sizeof(HwiP_Struct) <= sizeof(HwiP_Object) );
    DebugP_assertNoLog( params->callback != NULL );
    DebugP_assertNoLog( params->intNum < DPL_FREERTOS_C7X_CONFIGNUM_HWI );

    hwiPool        = (HwiP_freeRtos *) &gOsalHwiPFreeRtosPool[0];
    maxHwi         = DPL_FREERTOS_C7X_CONFIGNUM_HWI;

    if(gOsalHwiAllocCnt==0U)
    {
        (void)memset((void *)gOsalHwiPFreeRtosPool,0,sizeof(gOsalHwiPFreeRtosPool));
    }


    /* Grab the memory */
    key = HwiP_disable();

    for (i = 0U; i < maxHwi; i++)
    {
        if (hwiPool[i].used == (bool)false)
        {
            hwiPool[i].used = true;
            /* Update statistics */
            gOsalHwiAllocCnt++;
            if (gOsalHwiAllocCnt > gOsalHwiPeak)
            {
                gOsalHwiPeak = gOsalHwiAllocCnt;
            }
            break;
        }
    }
    HwiP_restore(key);

    if (i < maxHwi)
    {
        /* Grab the memory */
        handle = (HwiP_freeRtos *) &hwiPool[i];
    }

    if (handle != NULL_PTR)
    {
        status =  HwiP_configClec(params->eventId, params->intNum, params->isPulse);

        if(status == SystemP_SUCCESS)
        {
            Hwi_Params_init(&hwiParams);
            hwiParams.arg = (uint32_t)(params->args);

            if (params->priority==0U)
            {
               /* A priority of 0 is invalid for many targets. -1 forces
                  sysbios to assign a default priority */
               hwiParams.priority       = -1;
            }
            else
            {
               hwiParams.priority       = (int32_t)params->priority;
            }

            hwiParams.eventId        = (int32_t)params->eventId;
            hwiParams.enableInt      = true;
            hwiParams.maskSetting    = Hwi_MaskingOption_SELF;
            iStat = Hwi_construct(&handle->hwi, params->intNum, (Hwi_FuncPtr)(params->callback), &hwiParams);

            if (iStat != 0)
            {
                /* Free the allocated memory and return null */
                handle->used = false;
                handle = (HwiP_freeRtos *) NULL_PTR;
            }
        }
    }

    obj->intNum = params->intNum;

    return SystemP_SUCCESS;
}


void HwiP_destruct(HwiP_Object *handle)
{
    HwiP_Struct *obj = (HwiP_Struct *)handle;
    HwiP_freeRtos      *hwiPool;
    DebugP_assertNoLog( obj->intNum < DPL_FREERTOS_C7X_CONFIGNUM_HWI );

    uintptr_t   key;
    uint32_t    i;
    uint32_t    maxHwi;
    hwiPool        = (HwiP_freeRtos *) &gOsalHwiPFreeRtosPool[0];
    maxHwi         = DPL_FREERTOS_C7X_CONFIGNUM_HWI;

    if( Hwi_Module_state.dispatchTable[obj->intNum] != NULL)
    {
        Hwi_destruct(obj->intNum);
        key = HwiP_disable();
        /* Found the osal hwi object to delete */
        if (gOsalHwiAllocCnt > 0U)
        {
            gOsalHwiAllocCnt--;
            for (i=0; i<maxHwi; i++)
            {
                if ((uint32_t)hwiPool[i].hwi.intNum == obj->intNum)
                {
                    hwiPool[i].used = false;
                    break;
                }
            }
        }

        HwiP_restore(key);
    }
    return;
}

int32_t HwiP_setArgs(HwiP_Object *handle, void *args)
{
    HwiP_Struct *obj = (HwiP_Struct *)handle;

    DebugP_assertNoLog( obj->intNum < DPL_FREERTOS_C7X_CONFIGNUM_HWI );

    Hwi_Module_state.dispatchTable[obj->intNum]->arg = (uint32_t)args;

    return SystemP_SUCCESS;
}

void HwiP_Params_init(HwiP_Params *params)
{
    params->intNum = 0;
    params->callback = NULL;
    params->args = NULL;
    params->eventId = 0;
    params->priority = HWIP_USE_DEFAULT_PRIORITY;
    params->isFIQ = 0;
    params->isPulse = 1;
}

int32_t HwiP_configClec(uint16_t eventId, uint32_t intNum, uint8_t isPulse)
{
    int32_t status = SystemP_SUCCESS;

    if(eventId != HWIP_INVALID_EVENT_ID)
    {
        CSL_ClecEventConfig   cfgClec;
#if (CSL_C7X256V_CLEC_MAIN_CNT == 1U)
        CSL_CLEC_EVTRegs     *clecBaseAddr = (CSL_CLEC_EVTRegs*)CSL_C7X256V0_CLEC_BASE;
#elif (CSL_C7X256V_CLEC_MAIN_CNT > 1U)
        CSL_CLEC_EVTRegs     *clecBaseAddr = Hwip_getClecBaseAddr();
        if (clecBaseAddr == (CSL_CLEC_EVTRegs*) NULL)
        {
            status = SystemP_FAILURE;
        }
        if (SystemP_SUCCESS == status)
        {
#endif
            /* Configure CLEC */
            cfgClec.secureClaimEnable = FALSE;
            cfgClec.evtSendEnable     = TRUE;
            cfgClec.rtMap             = CSL_CLEC_RTMAP_CPU_ALL;
            cfgClec.extEvtNum         = 0;
            cfgClec.c7xEvtNum         = intNum;
            CSL_clecClearEvent(clecBaseAddr, eventId);
            CSL_clecConfigEventLevel(clecBaseAddr, eventId, !(isPulse)); /* configure interrupt as pulse/level */
            status = CSL_clecConfigEvent(clecBaseAddr, eventId, &cfgClec);
#if (CSL_C7X256V_CLEC_MAIN_CNT > 1U)
        }
#endif
    }

    return status;
}

/* The C7x CLEC should be initialized to allow config/re config.
 * This function configures all inputs to given level.
 */
void HwiP_configClecAccessCtrl(void)
{
    CSL_ClecEventConfig cfgClec;
    CSL_CLEC_EVTRegs   *clecBaseAddr = Hwip_getClecBaseAddr();
    uint32_t            i, maxInputs = 511U;

    cfgClec.secureClaimEnable = FALSE;
    cfgClec.evtSendEnable     = FALSE;
    cfgClec.rtMap             = CSL_CLEC_RTMAP_DISABLE;
    cfgClec.extEvtNum         = 0U;
    cfgClec.c7xEvtNum         = 0U;
    for(i = 1U; i < maxInputs; i++)
    {
        CSL_clecConfigEvent(clecBaseAddr, i, &cfgClec);
    }
}

/*
 * Returns the C7x clec base address for the current C7x cluster
*/
static CSL_CLEC_EVTRegs* Hwip_getClecBaseAddr(void)
{
    CSL_CLEC_EVTRegs     *clecBaseAddr = (CSL_CLEC_EVTRegs*) NULL;

#if (CSL_C7X256V_CLEC_MAIN_CNT == 1U)
    clecBaseAddr = (CSL_CLEC_EVTRegs*)CSL_C75_CPU_CLUSTER_C75_1_BASE_ADDR;
#elif (CSL_C7X256V_CLEC_MAIN_CNT == 2U)
    uint32_t clusterId;

    clusterId=CSL_clecGetC7xClusterId();

    if (clusterId == CSL_C75_CPU_CLUSTER_NUM_C75_1)
    {
        clecBaseAddr = (CSL_CLEC_EVTRegs*)CSL_C75_CPU_CLUSTER_C75_1_BASE_ADDR;
    }
    else if (clusterId == CSL_C75_CPU_CLUSTER_NUM_C75_2)
    {
        clecBaseAddr = (CSL_CLEC_EVTRegs*)CSL_C75_CPU_CLUSTER_C75_2_BASE_ADDR;
    }
    else
    {
        clecBaseAddr = (CSL_CLEC_EVTRegs*) NULL;
    }
#else
#error "Invalid CLEC Count"
#endif
    return clecBaseAddr;
}
