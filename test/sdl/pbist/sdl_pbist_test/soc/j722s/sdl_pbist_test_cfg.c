/*
 *  Copyright (C) 2024-2026 Texas Instruments Incorporated
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
 *  \file     pbist_test_cfg.c
 *
 *  \brief    This file contains PBIST test configuration
 *
 *  \details  PBIST Test Configuration
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <sdl/include/sdl_types.h>
#include <sdl/pbist/sdl_pbist_priv.h>
#include <sdl/sdl_pbist.h>
#include <drivers/sciclient.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <sdl/sdl_esm.h>
#include <sdl/esm/sdl_esm_priv.h>
#include <drivers/soc.h>
#include <drivers/hw_include/vpac/v4/cslr_vpac.h>
#include <drivers/hw_include/vpac/v4/cslr_viss.h>

#include "power_seq.h"
#include "pbist_test_cfg.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

#define GPU0_CFG_BASE                 (0x00FD80000ull)
#define SDL_MAIN_PD_RSVD0             (19U)
#define SDL_MAIN_LPSC_PDRSVD0_RSVD2   (87U)

/* Define the unlock and lock values */
#define KICK0_UNLOCK_VAL              (0x68EF3490U)
#define KICK1_UNLOCK_VAL              (0xD172BC5AU)
#define KICK_LOCK_VAL                 (0x00000000U)

#define SDL_WKUP_CTRL_MMR_CFG0_A53SS_DFT_CTL                              (0x00010600U)

/* JPGENC0 core clock control register offset */
#define SDL_JPGENC0_CORE_CLK_CTRL_OFFSET               (0x14U)

/* DMPAC0 test control register offset and PBIST enable bit */
#define SDL_DMPAC0_REGS_TEST_CTRL_OFFSET               (0x1CU)
#define SDL_DMPAC0_REGS_TEST_CTRL_EN_MASK        (0x00000001U)

/* ========================================================================== */
/*                            Local function prototypes                       */
/* ========================================================================== */

/*
    InitRestore functions : Initialize or Restore based on init flag
    init : TRUE  --> Initialize
    init : FALSE --> Restore
*/
int32_t PBIST_MPUAuxInitRestore(bool init);
int32_t PBIST_McuAuxInitRestore(bool init);
int32_t PBIST_EncodeAuxInitRestore(bool init);
int32_t PBIST_AuxInitRestore(bool init);
int32_t PBIST_GPUAuxInitRestore(bool init);
int32_t PBIST_DmpacAuxInitRestore(bool init);
int32_t PBIST_C7X1AuxInitRestore(bool init);
int32_t PBIST_C7X0AuxInitRestore(bool init);
int32_t PBIST_VPACAuxInitRestore(bool init);
int32_t PBIST_MainAuxInitRestore(bool init);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint32_t PBIST_MPUAuxDevList[MPU_NUM_AUX_DEVICES] =
{
    TISCI_DEV_COMPUTE_CLUSTER0,
    TISCI_DEV_A53SS0,
	TISCI_DEV_A53SS0_CORE_2,
	TISCI_DEV_A53SS0_CORE_3,
};

uint32_t PBIST_RTAuxDevList[RT_NUM_AUX_DEVICES] =
{
    TISCI_DEV_MMCSD0,
	TISCI_DEV_CSI_RX_IF0,
    TISCI_DEV_DPHY_RX0,
    TISCI_DEV_CSI_RX_IF1,
    TISCI_DEV_DPHY_RX1,
    TISCI_DEV_CSI_RX_IF2,
    TISCI_DEV_DPHY_RX2,
    TISCI_DEV_CSI_RX_IF3,
    TISCI_DEV_DPHY_RX3,
    TISCI_DEV_USB0, /* Now enabled with force bit power-off mechanism */
    TISCI_DEV_DSS0,
    TISCI_DEV_DSS_DSI0,
    TISCI_DEV_DSS1,
    TISCI_DEV_CSI_TX_IF0,
    TISCI_DEV_DPHY_TX0,
};

uint32_t PBIST_GPUAuxDevList[GPU_NUM_AUX_DEVICES] =
{
    TISCI_DEV_GPU0,
    TISCI_DEV_GPU0_CORE_VD,
};

uint32_t PBIST_DM2AuxDevList[DM2_NUM_AUX_DEVICES] =
{
    TISCI_DEV_WKUP_PBIST0,
    TISCI_DEV_FSS0_OSPI_0,
    TISCI_DEV_FSS0_FSAS_0,
	TISCI_DEV_MCU_MCAN1,
	TISCI_DEV_MCU_MCAN0,
    TISCI_DEV_PCIE0,
    TISCI_DEV_SERDES_10G1,
    TISCI_DEV_USB1,
    TISCI_DEV_SERDES_10G0,
};

uint32_t PBIST_MainAuxDevList[MAIN_NUM_AUX_DEVICES] =
{
	TISCI_DEV_MCAN0,
    TISCI_DEV_CPSW0,
    TISCI_DEV_MCAN1,
	TISCI_DEV_MMCSD1,
	TISCI_DEV_MMCSD2,
    TISCI_DEV_GICSS0,
    TISCI_DEV_JPGENC0,
    TISCI_DEV_DBGSUSPENDROUTER0,
	TISCI_DEV_STM0,
	TISCI_DEV_DEBUGSS_WRAP0,
	TISCI_DEV_DEBUGSS0,
};

uint32_t PBIST_C7X0AuxDevList[C7X0_NUM_AUX_DEVICES] =
{
    TISCI_DEV_C7X256V0,
    TISCI_DEV_C7X256V0_CORE0,
};

uint32_t PBIST_C7X1AuxDevList[C7X1_NUM_AUX_DEVICES] =
{
    TISCI_DEV_C7X256V1,
    TISCI_DEV_C7X256V1_CORE0,
};

uint32_t PBIST_CodecAuxDevList[CODEC_NUM_AUX_DEVICES]=
{
    TISCI_DEV_CODEC0,
};

PBIST_TestHandle_t PBIST_TestHandleArray[PBIST_MAX_INSTANCE+1] =
{
	/* COMPUTE_CLUSTER0_PBIST : MPU  */
    {
        .testName               = "A53 MPU CLUSTER0",
        .pbistInst              = SDL_PBIST_INST_MPU,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_COMPUTE_CLUSTER0_PBIST_0,     /* PBIST device id  */
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = true,                /* Secondary core needed */
        .coreName               = "MPU core 0",   /* Primary core   */
        .secCoreName            = "MPU core 1",   /* Secondary core */
        .tisciProcId            = SCICLIENT_PROC_ID_A53SS0_CORE_0,
        .tisciSecProcId         = SCICLIENT_PROC_ID_A53SS0_CORE_1,
        .tisciDeviceId          = TISCI_DEV_A53SS0_CORE_0,
        .tisciSecDeviceId       = TISCI_DEV_A53SS0_CORE_1,
        .coreCustPwrSeqNeeded   = true,
        .numAuxDevices          = MPU_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_MPUAuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_MPUAuxInitRestore, /* Auxilliary init function */
    },

    /* CODEC Instance PBIST3  */
    {
        .testName               = "CODEC PBIST3",
        .pbistInst              = SDL_PBIST_INST_ENCODE,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST3,    /* PBIST device id  */
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                 /* Secondary core needed */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = CODEC_NUM_AUX_DEVICES,     			/* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_CodecAuxDevList[0], 				/* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_EncodeAuxInitRestore, 				/* Auxilliary init function */
    },

    /* MAIN Instance PBIST1 */
	{
        .testName               = "PBIST1",
        .pbistInst              = SDL_PBIST_INST_PBIST1,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST1,
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "PBIST1",   /* Primary core   */
        .tisciProcId            = 0X0U,
        .tisciDeviceId          = 0X0U,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = RT_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_RTAuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_AuxInitRestore, /* Auxilliary init function */
    },

    /*Instance WKUP_PBIST1 */
	{
        .testName            = "WKUP_PBIST1",
        .pbistInst              = SDL_PBIST_INST_WKUP_PBIST1,
        .tisciPBISTDeviceId     = TISCI_DEV_WKUP_PBIST1,
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "WKUP_PBIST1",   /* Primary core   */
        .tisciProcId            = 0X0U,
        .tisciDeviceId          = 0X0U,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = DM2_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_DM2AuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_AuxInitRestore, /* Auxilliary init function */
    },

    /*Instance GPU0 */
	{

        .testName            = "PBIST_GPU",
        .pbistInst           = SDL_PBIST_INST_GPU,
        .tisciPBISTDeviceId     = TISCI_DEV_GPU0,
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "PBIST_GPU",   /* Primary core   */
        .tisciProcId            = 0X0U,
        .tisciDeviceId          = 0X0U,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = GPU_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_GPUAuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_GPUAuxInitRestore, /* Auxilliary init function */
    },

	/* MAIN Instance PBIST0*/
    {
        .testName               = "MAIN PBIST0",
        .pbistInst              = SDL_PBIST_INST_MAIN,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST0,    /* PBIST device id  */
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,               	/* Secondary core needed */
        .coreName               = "MAIN",             	/* No coreName   */
        .tisciProcId            = 0x0u,
        .tisciDeviceId          = 0x0u,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = MAIN_NUM_AUX_DEVICES,    				/* Number of Aux devices */
        .auxDeviceIdsP          = &PBIST_MainAuxDevList[0], 				/* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_MainAuxInitRestore, 				/* Auxilliary init function */
    },

    /* Instance VPAC0 */
	{
        .testName               = "VPAC0",
        .pbistInst              = SDL_PBIST_INST_VPAC0,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_VPAC0,
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "VPAC0",   /* Primary core   */
        .tisciProcId            = 0X0U,
        .tisciDeviceId          = 0X0U,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0x0u,     /* No Aux devices   */
        .auxDeviceIdsP          = 0x0u, /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_VPACAuxInitRestore, /* Auxilliary init function */
    },

    /* Instance C7X0 */
	{
        .testName               = "C7X0",
        .pbistInst              = SDL_PBIST_INST_C7X0,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_C7X256V0_PBIST,
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "C7X0",               /* Primary core   */
        .tisciProcId            = SCICLIENT_PROC_ID_C7X256V0_C7XV_CORE_0,
        .tisciDeviceId          = TISCI_DEV_C7X256V0_C7XV_CORE_0,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = C7X0_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_C7X0AuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_C7X0AuxInitRestore, /* Auxilliary init function */
    },

    /* Instance C7X1 */
	{
        .testName               = "C7X1",
        .pbistInst              = SDL_PBIST_INST_C7X1,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_C7X256V1_PBIST,
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "C7X1",   /* Primary core   */
        .tisciProcId            = SCICLIENT_PROC_ID_C7X256V1_C7XV_CORE_0,
        .tisciDeviceId          = TISCI_DEV_C7X256V1_C7XV_CORE_0,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = C7X1_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_C7X1AuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_C7X1AuxInitRestore, /* Auxilliary init function */
    },

    /* MAIN_PULSAR Instance PBIST2 */
	{
        .testName               = "PBIST2",
        .pbistInst              = SDL_PBIST_INST_PBIST2,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST2,
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "PBIST2",   /* Primary core   */
        .tisciProcId            = SCICLIENT_PROC_ID_R5FSS0_CORE0,
        .tisciDeviceId          = TISCI_DEV_R5FSS0_CORE0,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0x0u,     /* No Aux devices   */
        .auxDeviceIdsP          = 0x0u, /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_AuxInitRestore, /* Auxilliary init function */
    },

    /* Instance DMPAC0 */
	{
        .testName               = "DMPAC0",
        .pbistInst              = SDL_PBIST_INST_DMPAC0,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_DMPAC0,
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "DMPAC0",   /* Primary core   */
        .tisciProcId            = 0X0U,
        .tisciDeviceId          = 0X0U,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0x0u,     /* No Aux devices */
        .auxDeviceIdsP          = 0x0u, /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_DmpacAuxInitRestore, /* Auxilliary init function */
    },

    /* MCU_PULSER Instance MCU_PBIST0(WKUP_R5F) */
    {
        .testName               = "MCU PBIST0",
        .pbistInst              = SDL_PBIST_INST_MCU,
        .numPostPbistToCheck    = 1u,
        .tisciPBISTDeviceId     = TISCI_DEV_MCU_PBIST0,    /* PBIST device id  */
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,               	/* Secondary core needed */
        .coreName               = "MCU PULSER",             	/* No coreName   */
        .tisciProcId            = 0x0u,
        .tisciDeviceId          = 0x0u,
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0x0u,    				/* No Aux devices */
        .auxDeviceIdsP          = 0x0u, 				/* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_McuAuxInitRestore, 				/* Auxilliary init function */
    },
};

/* Captures common Initialization: currently nothing needed */
int32_t PBIST_commonInit(void)
{
    SDL_ErrType_t status = SDL_PASS;

    return status;
}

/*
    InitRestore functions : Initialize or Restore based on init flag
    init : TRUE  --> Initialize
    init : FALSE --> Restore
*/
int32_t PBIST_MPUAuxInitRestore(bool init)
{
    static uint32_t savedRegVal = 0U;
    int32_t testResult          = 0;
    uint32_t baseAddr;

    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(SDL_WKUP_CTRL_MMR0_CFG0_BASE);

    *((uint32_t *)(((uint32_t)baseAddr) + SDL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(((uint32_t)baseAddr) + SDL_WKUP_CTRL_MMR_CFG0_LOCK4_KICK1)) = KICK1_UNLOCK_VAL;
    /* BISOR override is needed to verify DC memories in cfg */
    if (init)
    {
        /* A53SS_DFT_CTL is write-only; reset value is 0x0000 (captured by static init).
         * Set BISOR override to verify DC memories during PBIST. */
        *((uint32_t *)(((uint32_t)baseAddr) + SDL_WKUP_CTRL_MMR_CFG0_A53SS_DFT_CTL)) = 0x0001U;
    }
    else
    {
        /* Restore to the known reset/pre-PBIST value */
        *((uint32_t *)(((uint32_t)baseAddr) + SDL_WKUP_CTRL_MMR_CFG0_A53SS_DFT_CTL)) = savedRegVal;
    }

    return testResult;
}

int32_t PBIST_MainAuxInitRestore(bool init)
  {
    static uint32_t savedRegVal = 0U;
    int32_t testResult          = 0;
    volatile uint32_t *reg      = (volatile uint32_t *)(SDL_JPGENC0_CORE_BASE + SDL_JPGENC0_CORE_CLK_CTRL_OFFSET);

    if (init)
    {
        PBIST_AuxInitRestore(init);
        savedRegVal = *reg;
        *reg        = 0x00U;
    }
    else
    {
        PBIST_AuxInitRestore(init);
        *reg = savedRegVal;
    }

    return (testResult);
}

int32_t PBIST_C7X0AuxInitRestore(bool init)
{
    static uint32_t savedRegVal = 0U;
    int32_t testResult          = 0;

    if (init)
    {
        /* Enable MAIN_PLL7_HSDIV0_CLKOUT for C7X0 */
        savedRegVal = SDL_REG32_RD(CSL_PLL0_CFG_BASE + CSL_MAIN_PLL_MMR_CFG_PLL7_HSDIV_CTRL0);
        SDL_REG32_WR(CSL_PLL0_CFG_BASE + CSL_MAIN_PLL_MMR_CFG_PLL7_HSDIV_CTRL0, (0x8000U | savedRegVal));
    }
    else
    {
        SDL_REG32_WR(CSL_PLL0_CFG_BASE + CSL_MAIN_PLL_MMR_CFG_PLL7_HSDIV_CTRL0, savedRegVal);
    }

    return (testResult);
}

int32_t PBIST_C7X1AuxInitRestore(bool init)
{
    static uint32_t savedRegVal = 0U;
    int32_t testResult          = 0;

    if (init)
    {
        /* Enable MAIN_PLL7_HSDIV1_CLKOUT for C7X1 */
        savedRegVal = SDL_REG32_RD(CSL_PLL0_CFG_BASE + CSL_MAIN_PLL_MMR_CFG_PLL7_HSDIV_CTRL1);
        SDL_REG32_WR(CSL_PLL0_CFG_BASE + CSL_MAIN_PLL_MMR_CFG_PLL7_HSDIV_CTRL1, (0x8000U | savedRegVal));
    }
    else
    {
        SDL_REG32_WR(CSL_PLL0_CFG_BASE + CSL_MAIN_PLL_MMR_CFG_PLL7_HSDIV_CTRL1, savedRegVal);
    }

    return (testResult);
}

int32_t PBIST_VPACAuxInitRestore(bool init)
{
    static uint32_t savedReg0 = 0U;
    static uint32_t savedReg1 = 0U;
    static uint32_t savedReg2 = 0U;
    int32_t testResult        = 0;
    volatile uint32_t *reg0   = (volatile uint32_t *)(SDL_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_BASE + CSL_VISS_TOP_TEST_CNTL);
    volatile uint32_t *reg1   = (volatile uint32_t *)(SDL_VPAC0_IVPAC_TOP_0_CFG_SLV_VPAC_REGS_VPAC_REGS_CFG_IP_MMRS_BASE + CSL_VPAC_CNTL_VPAC_TEST_CTRL);
    volatile uint32_t *reg2   = (volatile uint32_t *)(SDL_VPAC0_IVPAC_TOP_0_CFG_SLV_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_BASE + CSL_VISS_TOP_VISS_CNTL);

    if (init)
    {
        savedReg0 = *reg0;
        savedReg1 = *reg1;
        savedReg2 = *reg2;

        *reg0 = CSL_VISS_TOP_TEST_CNTL_GATED_MEM_CLKF_MASK;
        *reg1 = (CSL_VPAC_CNTL_VPAC_TEST_CTRL_UTC0_CFG_PBIST_OVERRIDE_MASK |
                 CSL_VPAC_CNTL_VPAC_TEST_CTRL_UTC1_CFG_PBIST_OVERRIDE_MASK);
        *reg2 = (CSL_VISS_TOP_VISS_CNTL_GLBCE_EN_MASK |
                 CSL_VISS_TOP_VISS_CNTL_NSF4V_EN_MASK);
    }
    else
    {
        *reg0 = savedReg0;
        *reg1 = savedReg1;
        *reg2 = savedReg2;
    }

    return (testResult);
}

int32_t PBIST_McuAuxInitRestore(bool init)
{
    int32_t testResult = 0;

    return testResult;
}

int32_t PBIST_EncodeAuxInitRestore(bool init)
{
    static uint32_t savedRegVal = 0U;
    int32_t testResult          = 0;
    uint32_t baseAddr;

    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(SDL_WKUP_CTRL_MMR0_CFG0_BASE);

    *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_LOCK2_KICK1)) = KICK1_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK0)) = KICK0_UNLOCK_VAL;
    *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK1)) = KICK1_UNLOCK_VAL;

    if (init)
    {
        /* Save and disable clock gating for the video codec */
        savedRegVal = *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1));
        *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1)) = 0x00000008U;
    }
    else
    {
        /* Restore clock gating for the video codec */
        *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1)) = savedRegVal;
    }

    return testResult;
}

int32_t PBIST_AuxInitRestore(bool init)
{
    int32_t testResult = 0;
	uint32_t baseAddr;
    uint32_t baseAddr1;

     static uint32_t savedRegVal1 = 0U;
     static uint32_t savedRegVal2 = 0U;
     static uint32_t savedRegVal3 = 0U;
     static uint32_t savedRegVal4 = 0U;

    if(init)
    {
        baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(SDL_WKUP_CTRL_MMR0_CFG0_BASE);

        *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK0)) = KICK0_UNLOCK_VAL;
        *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_LOCK6_KICK1)) = KICK1_UNLOCK_VAL;
        savedRegVal1 = *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0));
        savedRegVal2 = *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1));
        *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0)) = 0xffffffff;
        *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1)) = 0xffffffff;

        baseAddr1 = (uint32_t) AddrTranslateP_getLocalAddr(SDL_MCU_CTRL_MMR0_CFG0_BASE);

        *((uint32_t *)(baseAddr1 + SDL_MCU_CTRL_MMR_CFG0_LOCK6_KICK0)) = KICK0_UNLOCK_VAL;
        *((uint32_t *)(baseAddr1 + SDL_MCU_CTRL_MMR_CFG0_LOCK6_KICK1)) = KICK1_UNLOCK_VAL;
        savedRegVal3 = *((uint32_t *)(baseAddr1 + SDL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL));
        *((uint32_t *)(baseAddr1 + SDL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL)) = 0xffffffff;

        *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK0)) = KICK0_UNLOCK_VAL;
        *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_LOCK3_KICK1)) = KICK1_UNLOCK_VAL;
        savedRegVal4 = *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_PBIST_EN));
        *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_PBIST_EN)) = 0xffff;
    }
    else
    {
        baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(SDL_WKUP_CTRL_MMR0_CFG0_BASE);
        *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL0)) = savedRegVal1;
        *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL1)) = savedRegVal2;

        baseAddr1 = (uint32_t) AddrTranslateP_getLocalAddr(SDL_MCU_CTRL_MMR0_CFG0_BASE);
        *((uint32_t *)(baseAddr1 + SDL_MCU_CTRL_MMR_CFG0_CLKGATE_CTRL)) = savedRegVal3;

        *((uint32_t *)(baseAddr + SDL_WKUP_CTRL_MMR_CFG0_PBIST_EN)) = savedRegVal4;
    }
	return testResult;
}

 int32_t PBIST_DmpacAuxInitRestore(bool init)
{
    int32_t testResult = 0;
    static uint32_t savedRegVal = 0U;
    volatile uint32_t *reg = (volatile uint32_t *)(SDL_DMPAC0_DMPAC_TOP_CFG_SLV_DMPAC_REGS_DMPAC_REGS_CFG_IP_MMRS_BASE + SDL_DMPAC0_REGS_TEST_CTRL_OFFSET);

     /*Enable RAM clocks*/
    if (init)
    {
        savedRegVal = *reg;
        *reg = SDL_DMPAC0_REGS_TEST_CTRL_EN_MASK;
    }
    else
    {
        *reg = savedRegVal;
    }

    return testResult;
}

int32_t PBIST_GPUAuxInitRestore(bool init)
{
    int32_t testResult = 0;
    int32_t i = 0;
    uint32_t timeoutCnt;

    uint32_t localP = (uint32_t) GPU0_CFG_BASE;

    if (testResult == 0)
    {
        if (init)
        {
            *((uint32_t *)(localP + 0xA100)) = 0x0;
            timeoutCnt = 100000U;
            while (timeoutCnt-- > 0)
            {
                if (*((uint32_t *)(localP + 0xA100)) ==  (uint32_t)0x0)
                {
                    break;
                }
            }
            if (timeoutCnt == 0)
            {
                DebugP_log("timeout in GPUAuxInitRestore [1]\n");
            }

            /* Force all GPU clocks on */
            *((uint64_t *)(localP)) = 0x0015550015115555;

            /* Force the FW Processor clocks to ON to enable testing of mars memories */
            *((uint32_t *)(localP + 0x3090)) = 0x00000001;
            i = 1000;
            while(i--);
            *((uint32_t *)(localP + 0x3480)) = 0x00000001;
            timeoutCnt = 100000U;
            while (timeoutCnt-- > 0)
            {
                if((*(uint32_t *)(localP + 0x3488) & 0x400) == (uint32_t)0x400)
                {
                    break;
                }
            }
            if (timeoutCnt == 0)
            {
                DebugP_log("timeout in GPUAuxInitRestore [2]\n");
            }
            *((uint32_t *)(localP + 0x3480)) = 0x80000001;
            i = 1000;
            while(i--);
            timeoutCnt = 100000U;
            while (timeoutCnt-- > 0)
            {
                if((*((uint32_t *)(((uint32_t)localP) + 0x3488)) & 0x200) == (uint32_t)0x200)
                {
                    break;
                }
            }
            if (timeoutCnt == 0)
            {
                DebugP_log("timeout in GPUAuxInitResotre [3]\n");
            }
            *((uint32_t *)(localP + 0x3420)) = 0x000001FF;
            *((uint32_t *)(localP + 0x34B8)) = 0x002307F8;
            timeoutCnt = 100000U;
            while (timeoutCnt-- > 0)
            {
                if((*((uint32_t *)(localP + 0x34B0)) & 0x1700) == (uint32_t)0x0000)
                {
                    break;
                }
            }
            if (timeoutCnt == 0)
            {
                DebugP_log("timeout in GPUAuxInitRestore [4]\n");
            }
            i = 1000;
            while(i--);
            *((uint32_t *)(((uint32_t)localP) + 0x3480)) = 0x00;
            i = 1000;
            while(i--);
        }
        else
        {
          /* TODO: Need to see how to revert */
        }
    }
    return testResult;
}

char * PBIST_getPostStatusString(SDL_PBIST_postStatus postStatus)
{
    if (postStatus == SDL_PBIST_POST_NOT_RUN)
    {
        return PBIST_POST_NOT_RUN_STR;
    }
    else if (postStatus == SDL_PBIST_POST_TIMEOUT)
    {
        return PBIST_POST_ATTEMPTED_TIMEOUT_STR;
    }
    else if (postStatus == SDL_PBIST_POST_COMPLETED_FAILURE)
    {
        return PBIST_POST_COMPLETED_FAILURE_STR;
    }
    else if (postStatus == SDL_PBIST_POST_COMPLETED_SUCCESS)
    {
        return PBIST_POST_COMPLETED_SUCCESS_STR;
    }
    return NULL;
}

void PBIST_printPostStatus(SDL_PBIST_postResult *result)
{
    DebugP_log("    HW POST MCU Status : %s\n", (PBIST_getPostStatusString(result->mcuPostStatus)) ? : "Invalid");

    return;
}

/* Nothing past this point */
