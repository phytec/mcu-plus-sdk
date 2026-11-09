/*
 *  Copyright (C) 2021-2026 Texas Instruments Incorporated
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
 *
 */

/**
 *  \file     sdl_pok_funcTest.c
 *
 *  \brief    This file contains POK API functionality test code.
 *
 *  \details  POK functionality tests
 **/

/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/

#include "pok_main.h"
#include "dpl_interface.h"
#include <drivers/hw_include/tistdtypes.h>
#include <kernel/dpl/DebugP.h>
#include <sdl/esm/sdl_esm_priv.h>
#include <sdl/pok/v1/sdl_ip_pok.h>
#include <sdl/pok/v1/sdl_pok.h>
#include <sdl/pok/v1/soc/sdl_soc_pok.h>

/*===========================================================================*/
/*                         Macros                                            */
/*===========================================================================*/

#if defined (SOC_J722S)
/* UV trigger: max valid trim forces threshold above supply voltage */
#define SDL_POK_CORE_UV_TRIM_TRIGGER    (70u)   /* 0x46 -> 1.35V   (CORE_POK UV max) */
#define SDL_POK_1P8_UV_TRIM_TRIGGER     (68u)   /* 0x44 -> 2.168V  (1P8_POK  UV max) */
#define SDL_POK_3P3_UV_TRIM_TRIGGER     (68u)   /* 0x44 -> 3.9375V (3P3_POK  UV max) */

/* OV trigger: min valid trim forces threshold below supply voltage */
#define SDL_POK_CORE_OV_TRIMOV_TRIGGER  (0u)    /* 0x00 -> 0.725V  (CORE_POK OV min) */
#define SDL_POK_1P8_OV_TRIMOV_TRIGGER   (12u)   /* 0x0C -> 1.432V  (1P8_POK  OV min) */
#define SDL_POK_3P3_OV_TRIMOV_TRIGGER   (0u)    /* 0x00 -> 2.175V  (3P3_POK  OV min) */

/* UV restore: min valid trim sets threshold well below supply */
#define SDL_POK_CORE_UV_TRIM_RESTORE    (0u)    /* 0x00 -> 0.475V  (CORE_POK UV min) */
#define SDL_POK_1P8_UV_TRIM_RESTORE     (32u)   /* 0x20 -> 1.432V  (1P8_POK  UV min) */
#define SDL_POK_3P3_UV_TRIM_RESTORE     (0u)    /* 0x00 -> 1.425V  (3P3_POK  UV min) */

/* OV restore: high trim sets threshold above supply voltage */
#define SDL_POK_CORE_OV_TRIMOV_RESTORE  (74u)   /* 0x4A -> 1.65V  */
#define SDL_POK_1P8_OV_TRIMOV_RESTORE   (48u)   /* 0x30 -> 2.168V */
#define SDL_POK_3P3_OV_TRIMOV_RESTORE   (47u)   /* 0x2F -> 3.937V */

#endif
/* ========================================================================== */
/*                          Global Variables                                  */
/* ========================================================================== */

volatile Bool ESM_Error = false;
#if defined (SOC_J722S)
static volatile uint32_t g_expectedSigUV = 0xFFFFFFFFu;
static volatile uint32_t g_expectedSigOV = 0xFFFFFFFFu;
static volatile Bool     g_isPPMode        = false;
static volatile uint32_t g_curTrimRestore   = SDL_PWRSS_TRIM_NO_ACTION;
static volatile uint32_t g_curTrimOVRestore = SDL_PWRSS_TRIM_NO_ACTION;

static const char * const sdlPokInstNames[] =
{
    "VDDA_PMIC_IN",           /* 0 - SDL_POK_VDDA_PMIC_IN_ID                 */
    "VDDS_DDRIO",             /* 1 - SDL_POK_VDDS_DDRIO_ID (unused on J722S) */
    "VDDR_CORE",              /* 2 - SDL_POK_VDDR_CORE_ID                    */
    "VMON_CAP_MCU_GENERAL",   /* 3 - SDL_POK_VMON_CAP_MCU_GENERAL_ID         */
    "VDDSHV_MAIN_1P8",        /* 4 - SDL_POK_VDDSHV_MAIN_1P8_ID               */
    "VDDSHV_MAIN_3P3",        /* 5 - SDL_POK_VDDSHV_MAIN_3P3_ID               */
    "VDD_MCU_OV",             /* 6 - SDL_POK_VDD_MCU_OV_ID                   */
    "POR_VDDA_MCU_UV",        /* 7 - SDL_POR_VDDA_MCU_UV_ID                  */
    "POR_VDD_MCU_UV",         /* 8 - SDL_POR_VDD_MCU_UV_ID                   */
    "POR_VDDA_MCU_OV",        /* 9 - SDL_POR_VDDA_MCU_OV_ID                  */
};
#endif

/*===========================================================================*/
/*                         Internal function declarations                    */
/*===========================================================================*/

static int32_t sdlPOK_Test(SDL_POK_Inst instance, SDL_POK_config *pPokCfg,
                            uint32_t esmSigUV, uint32_t esmSigOV);
static void    sdlEsmSetupForPOK(uint32_t esm_err_sig);
static void sdlGetInstance(SDL_POK_Inst *instance, uint32_t *esm_err_sig);
uint32_t deactivate_trigger(uint32_t *esm_err_sig );
int32_t        sdlPOKInPor_funcTest(void);
int32_t        sdlPOK_funcTest(void);

#if defined (SOC_J722S)

#define SDL_POK_INST_NAME(id) \
    (((uint32_t)(id) < (sizeof(sdlPokInstNames) / sizeof(sdlPokInstNames[0]))) ? \
        sdlPokInstNames[(uint32_t)(id)] : "UNKNOWN_POK_ID")

#endif

/*===========================================================================*/
/*                         Function definitions                              */
/*===========================================================================*/

int32_t SDL_ESM_applicationCallbackFunction(SDL_ESM_Inst esmInst,
                                            SDL_ESM_IntType esmIntrType,
                                            uint32_t grpChannel,
                                            uint32_t index,
                                            uint32_t intSrc,
                                            void *arg)
{
    int32_t retVal = SDL_PASS;
    DebugP_log("\r\n  ESM Call back function called : instType 0x%x, intType 0x%x, " \
                "grpChannel 0x%x, index 0x%x, intSrc 0x%x \r\n",
                esmInst, esmIntrType, grpChannel, index, intSrc);
    DebugP_log("  Take action \r\n");
    /* Disable the ESM Interrupt */
    deactivate_trigger(&intSrc);
    SDL_ESM_clrNError(SDL_ESM_INST_WKUP_ESM0);
    SDL_ESM_disableIntr(SDL_WKUP_ESM0_CFG_BASE,intSrc);
    ESM_Error = true;
    /* Any additional customer specific actions can be added here */

    return retVal;
}

uint32_t deactivate_trigger(uint32_t *esm_err_sig )
{
    SDL_POK_Inst               instance;
    SDL_POK_config             pPokCfg;
    SDL_pokVal_t               pPokVal;
    uint32_t pbaseAddress;
    SDL_POK_getBaseaddr(SDL_POK_MCU_CTRL_MMR0, &pbaseAddress);
    SDL_mcuCtrlRegsBase_t    *pBaseAddr = (SDL_mcuCtrlRegsBase_t *) pbaseAddress;
    int32_t                    sdlRet = SDL_EFAIL;

    sdlGetInstance(&instance, esm_err_sig);

    pPokCfg.hystCtrl = SDL_PWRSS_HYSTERESIS_NO_ACTION;
    pPokCfg.voltDetMode = SDL_PWRSS_GET_VOLTAGE_DET_MODE;
    pPokCfg.trim = SDL_PWRSS_TRIM_NO_ACTION;
    pPokCfg.detectionCtrl = SDL_POK_DETECTION_NO_ACTION;
    pPokCfg.pokEnSelSrcCtrl = SDL_POK_ENSEL_NO_ACTION;
    pPokCfg.hystCtrlOV = SDL_PWRSS_HYSTERESIS_NO_ACTION;
    pPokCfg.trimOV = SDL_PWRSS_TRIM_NO_ACTION;
    pPokCfg.deglitch = SDL_PWRSS_DEGLITCH_NO_ACTION;

    SDL_pokGetControl (pBaseAddr,&pPokCfg,&pPokVal,instance);

#if defined (SOC_J722S)
    if (g_isPPMode)
    {
        if (*esm_err_sig == g_expectedSigUV)
        {
            pPokCfg.trim   = g_curTrimRestore;
            pPokCfg.trimOV = SDL_PWRSS_TRIM_NO_ACTION;
        }
        else
        {
            pPokCfg.trimOV = g_curTrimOVRestore;
            pPokCfg.trim   = SDL_PWRSS_TRIM_NO_ACTION;
        }
    }
    else if (pPokVal.voltDetMode == SDL_PWRSS_SET_UNDER_VOLTAGE_DET_ENABLE)
    {
        pPokCfg.trim = g_curTrimRestore;
        pPokCfg.trimOV = SDL_PWRSS_TRIM_NO_ACTION;
    }
    else if (pPokVal.voltDetMode == SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE)
    {
        pPokCfg.trimOV = g_curTrimOVRestore;
        pPokCfg.trim = SDL_PWRSS_TRIM_NO_ACTION;
    }
    else
    {
        pPokCfg.trim = g_curTrimRestore;
    }
#else
    if (pPokVal.voltDetMode == SDL_PWRSS_SET_UNDER_VOLTAGE_DET_ENABLE)
    {
        pPokCfg.trim = 0;
        pPokCfg.trimOV = SDL_PWRSS_TRIM_NO_ACTION;
    }
    else if (pPokVal.voltDetMode == SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE)
    {
        pPokCfg.trimOV = 45;
        pPokCfg.trim = SDL_PWRSS_TRIM_NO_ACTION;
    }
    else
    {
        pPokCfg.trim = 0;
    }
#endif

    pPokCfg.hystCtrl = SDL_PWRSS_HYSTERESIS_NO_ACTION;
    pPokCfg.voltDetMode = pPokVal.voltDetMode;
    pPokCfg.detectionCtrl = SDL_POK_DETECTION_NO_ACTION;
    pPokCfg.pokEnSelSrcCtrl = SDL_POK_ENSEL_NO_ACTION;
    pPokCfg.hystCtrlOV = SDL_PWRSS_HYSTERESIS_NO_ACTION;
    pPokCfg.deglitch = SDL_PWRSS_DEGLITCH_NO_ACTION;
    sdlRet = SDL_POK_init(instance,&pPokCfg);

    return sdlRet;
}

static void sdlPOKGetUVOV(uint32_t id, uint32_t *isOV)
{
    switch (id)
    {
        case SDL_POR_VDDA_MCU_UV_ID:
        case SDL_POR_VDD_MCU_UV_ID:
            *isOV = 0x0;
            break;
        case SDL_POK_VDD_MCU_OV_ID:
        case SDL_POR_VDDA_MCU_OV_ID:
            *isOV = 0x1;
            break;
        default:
            *isOV = 0x2;
            break;
    }
    return;
}

#if defined (SOC_J722S)
static const char * sdlPOKGetUVOVName(uint32_t isOV)
{
    const char *name;
    switch (isOV)
    {
        case 0x0:
            name = "UV";
            break;
        case 0x1:
            name = "OV";
            break;
        default:
            name = "PP";
            break;
    }
    return (name);
}

typedef enum {
    SDL_POK_TYPE_CORE = 0U,    /* POK_CORE */
    SDL_POK_TYPE_1P8,          /* POK_1P8 */
    SDL_POK_TYPE_3P3,          /* POK_3P3 */
    SDL_POK_TYPE_SA            /* POK_SA, no trim */
} SDL_POK_MonType;

static SDL_POK_MonType sdlPOKGetType(uint32_t id)
{
    SDL_POK_MonType type;
    switch (id)
    {
        case SDL_POK_VDDA_PMIC_IN_ID:        /* VMON_ER_VSYS */
            type = SDL_POK_TYPE_SA;
            break;
        case SDL_POK_VDDSHV_MAIN_1P8_ID:     /* VMON_1P8_SOC */
        case SDL_POK_VMON_CAP_MCU_GENERAL_ID:
        case SDL_POR_VDDA_MCU_UV_ID:
        case SDL_POR_VDDA_MCU_OV_ID:
            type = SDL_POK_TYPE_1P8;
            break;
        case SDL_POK_VDDSHV_MAIN_3P3_ID:     /* VMON_3P3_SOC */
            type = SDL_POK_TYPE_3P3;
            break;
        default:  /* POK_VDD_MCU_UV, VDDR_CORE, VDDS_DDRIO, POR_VDD_MCU_UV */
            type = SDL_POK_TYPE_CORE;
            break;
    }
    return type;
}

static void sdlPOKGetTrimValues(uint32_t id,
                                uint32_t *pTrimTrigger, uint32_t *pTrimOVTrigger,
                                uint32_t *pTrimRestore, uint32_t *pTrimOVRestore)
{
    SDL_POK_MonType type = sdlPOKGetType(id);
    switch (type)
    {
        case SDL_POK_TYPE_1P8:
            *pTrimTrigger   = SDL_POK_1P8_UV_TRIM_TRIGGER;
            *pTrimOVTrigger = SDL_POK_1P8_OV_TRIMOV_TRIGGER;
            *pTrimRestore   = SDL_POK_1P8_UV_TRIM_RESTORE;
            *pTrimOVRestore = SDL_POK_1P8_OV_TRIMOV_RESTORE;
            break;
        case SDL_POK_TYPE_3P3:
            *pTrimTrigger   = SDL_POK_3P3_UV_TRIM_TRIGGER;
            *pTrimOVTrigger = SDL_POK_3P3_OV_TRIMOV_TRIGGER;
            *pTrimRestore   = SDL_POK_3P3_UV_TRIM_RESTORE;
            *pTrimOVRestore = SDL_POK_3P3_OV_TRIMOV_RESTORE;
            break;
        default: /* SDL_POK_TYPE_CORE and SDL_POK_TYPE_SA */
            *pTrimTrigger   = SDL_POK_CORE_UV_TRIM_TRIGGER;
            *pTrimOVTrigger = SDL_POK_CORE_OV_TRIMOV_TRIGGER;
            *pTrimRestore   = SDL_POK_CORE_UV_TRIM_RESTORE;
            *pTrimOVRestore = SDL_POK_CORE_OV_TRIMOV_RESTORE;
            break;
    }
}
#endif /* SOC_J722S */

void sdlEsmSetupForPOK(uint32_t esm_err_sig)
{
    /* ESM Variables */
    esmInfo_t appEsmInfo;
    uint32_t  esmBaseAddr;
#if defined (M4F_CORE)
    SDL_ESM_getBaseAddr(SDL_ESM_INST_WKUP_ESM0,&esmBaseAddr);
#endif
#if defined (R5F_CORE)
    SDL_ESM_getBaseAddr(SDL_ESM_INST_MAIN_ESM0,&esmBaseAddr);
#endif
    /* Check INFO register for ESM last reset cause */
    SDL_ESM_getInfo(esmBaseAddr, &appEsmInfo);

    /* The below function can be changed to force an error for diagnostic
     * reasons. */
    /* make sure we're not in force error mode */
    SDL_ESM_setMode(esmBaseAddr, ESM_OPERATION_MODE_NORMAL);

    /* Enable this ESM Error Signal */
    SDL_ESM_enableIntr(esmBaseAddr, esm_err_sig);

    /* Set the output interrupt priority level */
    SDL_ESM_setIntrPriorityLvl(esmBaseAddr, esm_err_sig, ESM_INTR_PRIORITY_LEVEL_HIGH);

    /* Enable Error Pin on this ESM Error Signal */
    SDL_ESM_setInfluenceOnErrPin(esmBaseAddr, esm_err_sig, TRUE);

    /* Enable for all ESM Error Signals */
    SDL_ESM_enableGlobalIntr(esmBaseAddr);
}

static int32_t sdlPOK_Test(SDL_POK_Inst instance, SDL_POK_config *pPokCfg,
                            uint32_t esmSigUV, uint32_t esmSigOV)
{
    int32_t sdlRet;
    volatile int32_t i = 0;
    SDL_POK_staticRegs pStaticRegs;

    ESM_Error = false;
#if defined (SOC_J722S)
    g_expectedSigUV = esmSigUV;
    g_expectedSigOV = esmSigOV;
#else
    (void)esmSigUV;
    (void)esmSigOV;
#endif

    pPokCfg->hystCtrl        = SDL_PWRSS_HYSTERESIS_NO_ACTION;
    pPokCfg->hystCtrlOV      = SDL_PWRSS_HYSTERESIS_NO_ACTION;
    pPokCfg->deglitch        = SDL_PWRSS_DEGLITCH_NO_ACTION;
    pPokCfg->pokEnSelSrcCtrl = SDL_POK_ENSEL_PRG_CTRL;
    pPokCfg->detectionCtrl   = SDL_POK_DETECTION_ENABLE;

    sdlRet = SDL_POK_getStaticRegisters(instance, &pStaticRegs);
    if (sdlRet == SDL_PASS)
    {
        DebugP_log("Trim value before init trim= %d  trimOV= %d\r\n", pStaticRegs.trim, pStaticRegs.trimOV);
    }
    else
    {
        DebugP_log("SDL_POK_getStaticRegisters Failed \r\n");
    }

    sdlRet = SDL_POK_init(instance, pPokCfg);

    if (sdlRet != SDL_PASS)
    {
        DebugP_log("SDL_POK_init failed! \r\n");
    }
    sdlRet = SDL_POK_verifyConfig(instance, pPokCfg);
    if (sdlRet != SDL_PASS)
    {
        DebugP_log("SDL_POK_verifyConfig failed! \r\n");
    }
    else
    {
        sdlRet = SDL_POK_getStaticRegisters(instance, &pStaticRegs);
        if (sdlRet == SDL_PASS)
        {
            DebugP_log("Trim value after init trim= %d  trimOV= %d\r\n", pStaticRegs.trim, pStaticRegs.trimOV);
        }
        else
        {
            DebugP_log("SDL_POK_getStaticRegisters Failed \r\n");
        }
        DebugP_log("Waiting for ESM to report the error \r\n");
        /* Wait for the ESM interrupt to report the error */
        do {
            i++;
            if (i > 0x0FFFFFFF)
            {
                /* Timeout for the wait */
                break;
            }
        } while (ESM_Error == false);
        if (ESM_Error == true)
        {
            DebugP_log(" Got the ESM Error Interrupt \r\n");
            sdlRet  = SDL_PASS;
            ESM_Error = false;
        }
        else
        {
            sdlRet = SDL_EFAIL;
        }
    }
    return (sdlRet);
}

int32_t sdlPOKInPor_funcTest(void)
{
    int32_t                      testStatus, sdlRet = SDL_PASS, overallStatus = SDL_APP_TEST_PASS;
    SDL_POK_config               pPokCfg;
    uint32_t                     esm_err_sig_uv, esm_err_sig_ov;
    SDL_POK_Inst                 instance;
    bool                         usePorCfgFlag;
    uint32_t                     i;
    uint32_t                     isOV;
    SDL_POK_staticRegs           pStaticRegs;
#if defined (SOC_J722S)
    uint32_t                     trimTrigger, trimOVTrigger, trimRestore, trimOVRestore;
#endif
    DebugP_log(" Below are the POK In POR ID values for the test\r\n");
    DebugP_log("  SDL_POR_VDDA_MCU_UV_ID is:            7 \r\n");
    DebugP_log("  SDL_POR_VDD_MCU_UV_ID is:             8 \r\n");
    DebugP_log("  SDL_POR_VDDA_MCU_OV_ID is:            9 \r\n");

    DebugP_log(" Enter the Voltage Detection (0: UV, 1: OV, 2: PP) for the POK ID to monitor for the test  \r\n");

    instance = SDL_POR_VDDA_MCU_UV_ID;

    DebugP_log("\r\r\n\r\r\nDefault test loops through POK IDs \r\n", instance);
    pPokCfg.voltDetMode = SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE;
    pPokCfg.trim = 0;

    sdlRet = SDL_POK_getStaticRegisters(instance,&pStaticRegs);
    if (sdlRet == SDL_PASS)
    {
        DebugP_log("\r\n bandGap status %d\r\n", pStaticRegs.porBGapOK);
        DebugP_log("\r\r\n\r\r\nmodule status %d\r\n", pStaticRegs.porModuleStatus);
    }
    else
    {
        DebugP_log("SDL_POK_getStaticRegisters failed! \r\n");
    }

    for (i = SDL_POR_VDDA_MCU_UV_ID; i <= SDL_POR_VDDA_MCU_OV_ID; i++)
    {
        sdlRet = SDL_PASS;
        sdlGetErrSig(i, &instance, &esm_err_sig_uv, &esm_err_sig_ov, &usePorCfgFlag);
        sdlPOKGetUVOV(i, &isOV);

#if defined (SOC_J722S)
        sdlPOKGetTrimValues(i, &trimTrigger, &trimOVTrigger, &trimRestore, &trimOVRestore);
        g_isPPMode = (isOV == 0x2U);
        g_curTrimRestore   = trimRestore;
        g_curTrimOVRestore = trimOVRestore;

        if (isOV == 0x1)
        {
            pPokCfg.voltDetMode = SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE;
            pPokCfg.trim = SDL_PWRSS_TRIM_NO_ACTION;
            pPokCfg.trimOV = trimOVTrigger;
        }
        else
        {
            pPokCfg.voltDetMode = SDL_PWRSS_SET_UNDER_VOLTAGE_DET_ENABLE;
            pPokCfg.trimOV = SDL_PWRSS_TRIM_NO_ACTION;
            pPokCfg.trim = trimTrigger;
        }

        DebugP_log("\r\n");
        DebugP_log("Started error injection tests on POK instance %s(%d)\r\n",
                   SDL_POK_INST_NAME(instance), instance);
        DebugP_log("  Detection mode under test : %s\r\n", sdlPOKGetUVOVName(isOV));
#else
        if (isOV == 0x1)
        {
            pPokCfg.voltDetMode = SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE;
            pPokCfg.trim = SDL_PWRSS_TRIM_NO_ACTION;
            pPokCfg.trimOV = 0;
        }
        else
        {
            pPokCfg.voltDetMode = SDL_PWRSS_SET_UNDER_VOLTAGE_DET_ENABLE;
            pPokCfg.trimOV = SDL_PWRSS_TRIM_NO_ACTION;
            pPokCfg.trim = 127;
        }

        DebugP_log("Started error injection tests on POK instance (%d)\r\n", instance);
#endif

        /* ESM Setup for POK tests */

        sdlEsmSetupForPOK(esm_err_sig_uv);

        if (sdlRet == SDL_PASS)
        {
            DebugP_log("  ---- Phase: TRIGGER ----\r\n");
            sdlRet = sdlPOK_Test(instance, &pPokCfg,
                                  esm_err_sig_uv, esm_err_sig_ov);
            /* Re-configure to "good" setting */
#if defined (SOC_J722S)
            if (isOV == 0x1)
            {
                pPokCfg.trimOV = trimOVRestore;
                pPokCfg.trim = SDL_PWRSS_TRIM_NO_ACTION;
            }
            else
            {
                pPokCfg.trim = trimRestore;
                pPokCfg.trimOV = SDL_PWRSS_TRIM_NO_ACTION;
            }
#else
            if (isOV == 0x1)
            {
                pPokCfg.trimOV = 45;
                pPokCfg.trim = SDL_PWRSS_TRIM_NO_ACTION;
            }
            else
            {
                pPokCfg.trim = 0;
                pPokCfg.trimOV = SDL_PWRSS_TRIM_NO_ACTION;
            }
#endif

            DebugP_log("  ---- Phase: RESTORE ----\r\n");
            (void) sdlPOK_Test(instance, &pPokCfg,
                                esm_err_sig_uv, esm_err_sig_ov);
            /* Un register the Interrupt */

        }

        if (sdlRet == SDL_PASS)
        {
            testStatus = SDL_APP_TEST_PASS;
        }
        else
        {
            testStatus = SDL_APP_TEST_FAILED;
            overallStatus = SDL_APP_TEST_FAILED;
        }
#if defined (SOC_J722S)
        DebugP_log("  Verdict for instance %s(%d): %s\r\n",
                   SDL_POK_INST_NAME(instance), instance,
                   (testStatus == SDL_APP_TEST_PASS) ? "PASSED" : "FAILED");
#else
        DebugP_log("  Verdict for instance (%d): %s\r\n",
                   instance,
                   (testStatus == SDL_APP_TEST_PASS) ? "PASSED" : "FAILED");
#endif
    }
    return (overallStatus);
}

int32_t sdlPOK_funcTest(void)
{
    int32_t                      testStatus, sdlRet = SDL_PASS, overallStatus = SDL_APP_TEST_PASS;
    SDL_POK_config               pPokCfg;
    bool                         usePorCfgFlag;

    uint32_t                     esm_err_sig_uv, esm_err_sig_ov;
    SDL_POK_Inst                 instance;
    uint32_t                     i;
    uint32_t                     isOV;
#if defined (SOC_J722S)
    uint32_t                     trimTrigger, trimOVTrigger, trimRestore, trimOVRestore;
#endif

#if !defined(IP_VERSION_POK_V1_NO_DDRIO)

    DebugP_log(" Below are the POK ID values \r\n");
    DebugP_log("  SDL_POK_VDDA_PMIC_IN_ID is:            0 \r\n");
    DebugP_log("  SDL_POK_VDDS_DDRIO_ID is:              1 \r\n");
    DebugP_log("  SDL_POK_VDDR_CORE_ID is:               2 \r\n");
    DebugP_log("  SDL_POK_VMON_CAP_MCU_GENERAL_ID is:    3 \r\n");
    DebugP_log("  SDL_POK_VDDSHV_MAIN_1P8_ID is:         4 \r\n");
    DebugP_log("  SDL_POK_VDDSHV_MAIN_3P3_ID is:         5 \r\n");
    DebugP_log("  SDL_POK_VDD_MCU_OV_ID is:              6 \r\n");

#else

    DebugP_log(" Below are the POK ID values \r\n");
    DebugP_log("  SDL_POK_VDDA_PMIC_IN_ID is:            0 \r\n");
    DebugP_log("  SDL_POK_VDDR_CORE_ID is:               1 \r\n");
    DebugP_log("  SDL_POK_VMON_CAP_MCU_GENERAL_ID is:    2 \r\n");
    DebugP_log("  SDL_POK_VDDSHV_MAIN_1P8_ID is:         3 \r\n");
    DebugP_log("  SDL_POK_VDDSHV_MAIN_3P3_ID is:         4 \r\n");
    DebugP_log("  SDL_POK_VDD_MCU_OV_ID is:              5 \r\n");

#endif
    DebugP_log(" Enter the Voltage Detection (0: UV, 1: OV, 2: PP) for the POK ID to monitor for the test  \r\n");

    DebugP_log("\r\r\n\r\r\nDefault test cycles through POKs, monitoring set to OV \r\n");
    pPokCfg.voltDetMode = SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE;
    pPokCfg.trim = 0;

    for (i = SDL_FIRST_POK_ID + 1; i <= SDL_POK_VDD_MCU_OV_ID; i++)
    {
        sdlRet = SDL_PASS;
        sdlGetErrSig(i, &instance, &esm_err_sig_uv, &esm_err_sig_ov, &usePorCfgFlag);
        sdlPOKGetUVOV(i, &isOV);
#if defined (SOC_J722S)
        sdlPOKGetTrimValues(i, &trimTrigger, &trimOVTrigger, &trimRestore, &trimOVRestore);
        g_isPPMode = (isOV == 0x2U);
        g_curTrimRestore   = trimRestore;
        g_curTrimOVRestore = trimOVRestore;

        if (isOV == 0x1)
        {
            pPokCfg.voltDetMode = SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE;
            pPokCfg.trim = SDL_PWRSS_TRIM_NO_ACTION;
            pPokCfg.trimOV = trimOVTrigger;
        }
        else if (isOV == 0x0)
        {
            pPokCfg.voltDetMode = SDL_PWRSS_SET_UNDER_VOLTAGE_DET_ENABLE;
            pPokCfg.trim = trimTrigger;
            pPokCfg.trimOV = SDL_PWRSS_TRIM_NO_ACTION;
        }
        else
        {
            SDL_POK_enablePP(SDL_POK_PRG_PP_1_ID, true);
            /* This is Ping/Pong */
            pPokCfg.voltDetMode = SDL_PWRSS_SET_PP_VOLTAGE_DET_ENABLE;
            pPokCfg.trim   = trimTrigger;
            pPokCfg.trimOV = trimOVTrigger;
        }

        DebugP_log("\r\n");
        DebugP_log("Started error injection tests on POK instance %s(%d)\r\n",
                   SDL_POK_INST_NAME(instance), instance);
        DebugP_log("  Detection mode under test : %s\r\n", sdlPOKGetUVOVName(isOV));
#else
        if (isOV == 0x1)
        {
            pPokCfg.voltDetMode = SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE;
            pPokCfg.trim = SDL_PWRSS_TRIM_NO_ACTION;
            pPokCfg.trimOV = 0;
        }
        else if (isOV == 0x0)
        {
            pPokCfg.voltDetMode = SDL_PWRSS_SET_UNDER_VOLTAGE_DET_ENABLE;
            pPokCfg.trim = 127;
            pPokCfg.trimOV = SDL_PWRSS_TRIM_NO_ACTION;
        }
        else
        {
            SDL_POK_enablePP(SDL_POK_PRG_PP_1_ID, true);
            /* This is Ping/Pong */
            pPokCfg.voltDetMode = SDL_PWRSS_SET_PP_VOLTAGE_DET_ENABLE;
            pPokCfg.trim = 127;
            pPokCfg.trimOV = 0;
        }

        DebugP_log("Started error injection tests on POK instance (%d)\r\n", instance);
#endif

        /* ESM Setup for POK tests */

        sdlEsmSetupForPOK(esm_err_sig_uv);
        sdlEsmSetupForPOK(esm_err_sig_ov);

        if (sdlRet == SDL_PASS)
        {
            DebugP_log("  ---- Phase: TRIGGER ----\r\n");
            sdlRet = sdlPOK_Test(instance, &pPokCfg,
                                  esm_err_sig_uv, esm_err_sig_ov);

            if (sdlRet == SDL_PASS)
            {
                testStatus = SDL_APP_TEST_PASS;
            }
            else
            {
                testStatus = SDL_APP_TEST_FAILED;
                overallStatus = SDL_APP_TEST_FAILED;
            }
            /* Re-set the trim value to a good value */
#if defined(SOC_J722S)
            if (isOV == 0x1)
            {
                pPokCfg.trim = SDL_PWRSS_TRIM_NO_ACTION;
                pPokCfg.trimOV = trimOVRestore;
            }
            else if (isOV == 0x0)
            {
                pPokCfg.trim = trimRestore;
                pPokCfg.trimOV = SDL_PWRSS_TRIM_NO_ACTION;
            }
            else
            {
                pPokCfg.trim   = trimRestore;
                pPokCfg.trimOV = trimOVRestore;
            }
#else
            if (isOV == 0x1)
            {
                pPokCfg.trim = SDL_PWRSS_TRIM_NO_ACTION;
                pPokCfg.trimOV = 45;
            }
            else if (isOV == 0x0)
            {
                pPokCfg.trim = 0;
                pPokCfg.trimOV = SDL_PWRSS_TRIM_NO_ACTION;
            }
            else
            {
                pPokCfg.trim = 0;
                pPokCfg.trimOV = 45;
            }
#endif

            DebugP_log("  ---- Phase: RESTORE ----\r\n");
            (void) sdlPOK_Test(instance, &pPokCfg,
                                esm_err_sig_uv, esm_err_sig_ov);
        }
#if defined (SOC_J722S)
        DebugP_log("  Verdict for instance %s(%d): %s\r\n",
                   SDL_POK_INST_NAME(instance), instance,
                   (testStatus == SDL_APP_TEST_PASS) ? "PASSED" : "FAILED");
#else
        DebugP_log("  Verdict for instance (%d): %s\r\n",
                   instance,
                   (testStatus == SDL_APP_TEST_PASS) ? "PASSED" : "FAILED");
#endif
    }
    return (overallStatus);
}

static void sdlGetInstance(SDL_POK_Inst *instance, uint32_t *esm_err_sig)
{
    switch (*esm_err_sig)
    {
        case MCU_ESM_ERR_SIG_VDDA_PMIC_IN_UV:
            *instance = SDL_POK_VDDA_PMIC_IN_ID;
            break;
#if !defined(IP_VERSION_POK_V1_NO_DDRIO)
        case MCU_ESM_ERR_SIG_VDDS_DDRIO_UV:
        case MCU_ESM_ERR_SIG_VDDS_DDRIO_OV:
            *instance = SDL_POK_VDDS_DDRIO_ID;
            break;
#endif
        case MCU_ESM_ERR_SIG_VDDR_CORE_UV:
        case MCU_ESM_ERR_SIG_VDDR_CORE_OV:
            *instance = SDL_POK_VDDR_CORE_ID;
            break;
        case MCU_ESM_ERR_SIG_VMON_CAP_MCU_GENERAL_UV:
        case MCU_ESM_ERR_SIG_VMON_CAP_MCU_GENERAL_OV:
            *instance = SDL_POK_VMON_CAP_MCU_GENERAL_ID;
            break;
        case MCU_ESM_ERR_SIG_VDDSHV_MAIN_1P8_UV:
        case MCU_ESM_ERR_SIG_VDDSHV_MAIN_1P8_OV:
            *instance = SDL_POK_VDDSHV_MAIN_1P8_ID;
            break;
        case MCU_ESM_ERR_SIG_VDDSHV_MAIN_3P3_UV:
        case MCU_ESM_ERR_SIG_VDDSHV_MAIN_3P3_OV:
            *instance = SDL_POK_VDDSHV_MAIN_3P3_ID;
            break;
        case MCU_ESM_ERR_SIG_VDD_MCU_OV:
            *instance = SDL_POK_VDD_MCU_OV_ID;
            break;
        case MCU_ESM_ERR_SIG_VDDA_MCU_UV:
            *instance = SDL_POR_VDDA_MCU_UV_ID;
            break;
        case MCU_ESM_ERR_SIG_VDDA_MCU_OV:
            *instance = SDL_POR_VDDA_MCU_OV_ID;
            break;
        case MCU_ESM_ERR_SIG_VDD_MCU_UV:
            *instance = SDL_POR_VDD_MCU_UV_ID;
            break;
        default:
            *instance = (SDL_POK_Inst)(-1);
            break;
    }
    return;
}

/* Nothing past this point */
