/*
 *  Copyright (C) 2021-2025 Texas Instruments Incorporated
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
/*
 * Auto generated file
 */

#include "ti_drivers_config.h"
#include <drivers/device_manager/sciclient.h>




/*
 * BOOTLOADER
 */
#include "drivers/bootloader/bootloader_mmcsd_raw.h"

/* Bootloader boot media specific arguments */
Bootloader_MmcsdArgs gBootloader0Args =
{
    .MMCSDIndex      = CONFIG_MMCSD0,
    .curOffset       = 0,
    .appImageOffset  = 0x100000,
};
Bootloader_MmcsdArgs gBootloader1Args =
{
    .MMCSDIndex      = CONFIG_MMCSD0,
    .curOffset       = 0,
    .appImageOffset  = 0x80000,
};

/* Configuration option for lockstep or standalone */
void* operatingMode = NULL;

/* Bootloader DMA attributes */
#include <drivers/udma.h>
#include <drivers/bootloader/bootloader_dma.h>



/* Regions restricted for DMA. We should use CPU memcpy in these cases */
static Bootloader_AddrRegion gDmaRestrictRegions[] =
{
    {
        .regionStartAddr = CSL_WKUP_R5FSS0_ATCM_BASE,
        .regionSize      = CSL_WKUP_R5FSS0_ATCM_SIZE,
    },
    {
        .regionStartAddr = CSL_WKUP_R5FSS0_BTCM_BASE,
        .regionSize      = CSL_WKUP_R5FSS0_BTCM_SIZE,
    },
    {
        .regionStartAddr = CSL_MCU_M4FSS0_IRAM_BASE,
        .regionSize      = CSL_MCU_M4FSS0_IRAM_SIZE,
    },
    {
        .regionStartAddr = CSL_MCU_M4FSS0_DRAM_BASE,
        .regionSize      = CSL_MCU_M4FSS0_DRAM_SIZE,
    },
    {
        .regionStartAddr = 0xFFFFFFFFU,
        .regionSize      = 0U,
    }
};

#define BOOTLOADER_UDMA_BLK_COPY_CH_RING_ELEM_CNT   (1U)
#define BOOTLOADER_UDMA_BLK_COPY_CH_RING_MEM_SIZE   (((BOOTLOADER_UDMA_BLK_COPY_CH_RING_ELEM_CNT * 8U) + UDMA_CACHELINE_ALIGNMENT) & ~(UDMA_CACHELINE_ALIGNMENT - 1U))
#define BOOTLOADER_UDMA_BLK_COPY_CH_TRPD_MEM_SIZE   (UDMA_GET_TRPD_TR15_SIZE(1U))
#define BOOTLOADER_UDMA_NUM_BLKCOPY_CH              (1U)

/* BOOTLOADER UDMA Blockcopy Channel Objects */
static Udma_ChObject gBootloaderUdmaBlkCpyChObj[BOOTLOADER_UDMA_NUM_BLKCOPY_CH];

/* BOOTLOADER UDMA Blockcopy Channel Ring Mem */
static uint8_t gBootloaderUdmaBlkCpyCh0RingMem[BOOTLOADER_UDMA_BLK_COPY_CH_RING_MEM_SIZE] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));

/* BOOTLOADER UDMA Blockcopy Channel TRPD Mem */
static uint8_t gBootloaderUdmaBlkCpyCh0TrpdMem[BOOTLOADER_UDMA_BLK_COPY_CH_TRPD_MEM_SIZE] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));

BootloaderDma_UdmaArgs gBootloaderUdmaArgs =
{
    .drvHandle     = &gUdmaDrvObj[CONFIG_UDMA0],
    .chHandle      = &gBootloaderUdmaBlkCpyChObj[0],
    .trpdMem       = &gBootloaderUdmaBlkCpyCh0TrpdMem,
    .trpdMemSize   = BOOTLOADER_UDMA_BLK_COPY_CH_TRPD_MEM_SIZE,
    .ringMem       = &gBootloaderUdmaBlkCpyCh0RingMem,
    .ringMemSize   = BOOTLOADER_UDMA_BLK_COPY_CH_RING_MEM_SIZE,
    .ringElemCount = BOOTLOADER_UDMA_BLK_COPY_CH_RING_ELEM_CNT,
    .restrictedRegions = &gDmaRestrictRegions,};

/* Arguments to be used for driver implementation callbacks when boot media is SOC memory */
Bootloader_MemArgs gMemBootloaderArgs =
{
    .curOffset = 0,
    .appImageBaseAddr = 0,
    .enableDmaTransfer = true,
    .bootloaderDmaUdmaArgs = &gBootloaderUdmaArgs,
    .isDmaOpen = FALSE,
};

/* Bootloader driver configuration */
Bootloader_Config gBootloaderConfig[CONFIG_BOOTLOADER_NUM_INSTANCES] =
{
    {
        &gBootloaderMmcsdFxns,
        &gBootloader0Args,
        BOOTLOADER_MEDIA_EMMC,
        0,
        0,
        NULL,
        .socCoreOpMode= (void *)&operatingMode,
    },
    {
        &gBootloaderMmcsdFxns,
        &gBootloader1Args,
        BOOTLOADER_MEDIA_EMMC,
        0,
        0,
        NULL,
        .socCoreOpMode= (void *)&operatingMode,
    },
};

/* Bootloader driver configuration specifically for SOC memory */
Bootloader_Config gMemBootloaderConfig =
{
        &gBootloaderMemFxns,
        &gMemBootloaderArgs,
        BOOTLOADER_MEDIA_MEM,
        0,
        0,
        NULL,
        .socCoreOpMode= (void *)&operatingMode,
        TRUE,
};

uint32_t gBootloaderConfigNum = CONFIG_BOOTLOADER_NUM_INSTANCES;

/*
 * UDMA
 */

/* UDMA driver instance object */
Udma_DrvObject          gUdmaDrvObj[CONFIG_UDMA_NUM_INSTANCES];
/* UDMA driver instance init params */
static Udma_InitPrms    gUdmaInitPrms[CONFIG_UDMA_NUM_INSTANCES] =
{
    {
        .instId             = UDMA_INST_ID_BCDMA_0,
        .skipGlobalEventReg = FALSE,
        .virtToPhyFxn       = Udma_defaultVirtToPhyFxn,
        .phyToVirtFxn       = Udma_defaultPhyToVirtFxn,
    },
};

/* DDR */

/* DDR register config .h file as generated from DDR SUBSYSTEM REGISTER CONFIGURATION tool
 * Make sure path to this file is specified in your application project/makefile include path
 */
#include "drivers/ddr/v0/soc/am62x/board_ddrReginit.h"


static DDR_Params gDdrParams =
{
    /* below values are set using the globals defined in drivers/ddr/v0/soc/am62x/board_ddrReginit.h */
    .clk1Freq              = DDRSS_PLL_FREQUENCY_1,
    .clk2Freq              = DDRSS_PLL_FREQUENCY_2,
    .ddrssCtlReg           = DDRSS_ctlReg,
    .ddrssPhyIndepReg      = DDRSS_phyIndepReg,
    .ddrssPhyReg           = DDRSS_phyReg,
    .ddrssCtlRegNum        = DDRSS_ctlRegNum,
    .ddrssPhyIndepRegNum   = DDRSS_phyIndepRegNum,
    .ddrssPhyRegNum        = DDRSS_phyRegNum,
    .ddrssCtlRegCount      = DDRSS_CTL_REG_INIT_COUNT,
    .ddrssPhyIndepRegCount = DDRSS_PHY_INDEP_REG_INIT_COUNT,
    .ddrssPhyRegCount      = DDRSS_PHY_REG_INIT_COUNT,
	.fshcount              = DDRSS_PLL_FHS_CNT,
    .sdramIdx              = 15U,
    .enableEccFlag = 0,
    .eccRegion = NULL,
};

/*
 * SDL Interface functions for BIST modules
 */
static HwiP_Object gSDLHwiPObject[SDL_NUM_HWIP_OBJECTS];
uint32_t gSDLHwiPAvailable[SDL_NUM_HWIP_OBJECTS];

int32_t SDL_findAvailableObject()
{
    int i = 0;

    for (i = 0; i < SDL_NUM_HWIP_OBJECTS; i++)
    {
        if (gSDLHwiPAvailable[i] == true)
        {
            gSDLHwiPAvailable[i] = false;
            break;
        }
    }
    if (i == SDL_NUM_HWIP_OBJECTS)
    {
        i = -1;
    }
    return i;
}

int32_t SDL_findObject(HwiP_Object *obj)
{
    int i = 0;
    for (i = 0; i < SDL_NUM_HWIP_OBJECTS; i++)
    {
        if (&gSDLHwiPObject[i] == obj)
        {
            break;
        }
    }
    if (i == SDL_NUM_HWIP_OBJECTS)
    {
        i = -1;
    }
    return i;
}

static pSDL_DPL_HwipHandle SDL_registerInterrupt(SDL_DPL_HwipParams *pParams)
{
    HwiP_Params hwipParams;
    HwiP_Params_init(&hwipParams);
    int32_t objNum;
    pSDL_DPL_HwipHandle handle;

    hwipParams.args = (void *)pParams->callbackArg;
    hwipParams.intNum = pParams->intNum;
    hwipParams.callback = pParams->callback;
    objNum = SDL_findAvailableObject();

    if (objNum != -1)
    {
        HwiP_construct(&gSDLHwiPObject[objNum], &hwipParams);
        handle = &gSDLHwiPObject[objNum];
    }
    else
    {
        handle = NULL;
    }

    return handle;
}

static int32_t SDL_deregisterInterrupt(pSDL_DPL_HwipHandle handle)
{
    int32_t objNum;
    objNum = SDL_findObject(handle);
    if (objNum != -1)
    {
        gSDLHwiPAvailable[objNum] = true;
    }
    HwiP_destruct(handle);
    return SDL_PASS;
}

static int32_t SDL_enableInterrupt(uint32_t intNum)
{
    HwiP_enableInt(intNum);
    return SDL_PASS;
}

static int32_t SDL_disableInterrupt(uint32_t intNum)
{
    HwiP_disableInt(intNum);
    return SDL_PASS;
}

static void* SDL_addrTranslate(uint64_t addr, uint32_t size)
{
    uint32_t transAddr = (uint32_t)(-1);

    transAddr = (uint32_t)AddrTranslateP_getLocalAddr(addr);

    return (void *)transAddr;
}

static SDL_DPL_Interface dpl_interface =
{
    .enableInterrupt = (pSDL_DPL_InterruptFunction) SDL_enableInterrupt,
    .disableInterrupt = (pSDL_DPL_InterruptFunction) SDL_disableInterrupt,
    .registerInterrupt = (pSDL_DPL_RegisterFunction) SDL_registerInterrupt,
    .deregisterInterrupt = (pSDL_DPL_DeregisterFunction) SDL_deregisterInterrupt,
    .delay = (pSDL_DPL_DelayFunction) ClockP_sleep,
    .addrTranslate = (pSDL_DPL_AddrTranslateFunction) SDL_addrTranslate
};

int32_t SDL_dplInit(void)
{
    SDL_ErrType_t ret = SDL_PASS;
    int32_t i;

    for (i = 0; i < SDL_NUM_HWIP_OBJECTS; i++)
    {
        gSDLHwiPAvailable[i] = true;
    }

    ret = SDL_DPL_init(&dpl_interface);

    return ret;
}

/*
 * SDL handle functions to Initialize/Restore Auxiliary modules based on init flag
 */

int32_t SDL_PBIST_handleMAINAuxDevices(bool init)
{
    int32_t testResult = 0;
    uint32_t baseAddr;

    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_WKUP_CTRL_MMR0_CFG0_BASE);

    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_WKUP,6u);
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_WKUP,3u);

    *((uint32_t *)(baseAddr + CSL_WKUP_CTRL_MMR_CFG0_CLKGATE_CTRL)) = 0x1;

    return testResult;
}

int32_t SDL_PBIST_handleMPUAuxDevices(bool init)
{
    int32_t testResult = 0;
    uint32_t baseAddr;

    baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(CSL_WKUP_CTRL_MMR0_CFG0_BASE);

    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_WKUP,4u);

    /* BISOR override is needed to verify DC memories in cfg */
    *((uint32_t *)(((uint32_t)baseAddr) + SDL_WKUP_CTRL_MMR_CFG0_A53SS_DFT_CTL)) = 0x0001;

    return testResult;
}

/*
 * Lists of SDL Auxiliary Devices for each selected PBIST instance
 * (the lists include PBIST devices)
 */
uint32_t PBIST_MCUAuxDevList[MCU_NUM_AUX_DEVICES]  =
{
};
uint32_t PBIST_MPUAuxDevList[MPU_NUM_AUX_DEVICES]  =
{
    TISCI_DEV_COMPUTE_CLUSTER0,
    TISCI_DEV_A53SS0_CORE_0,
    TISCI_DEV_A53SS0_CORE_1,
    TISCI_DEV_A53SS0_CORE_2,
    TISCI_DEV_A53SS0_CORE_3,
    TISCI_DEV_COMPUTE_CLUSTER0_PBIST_0,
};
uint32_t PBIST_MAINAuxDevList[MAIN_NUM_AUX_DEVICES]  =
{
    TISCI_DEV_DMASS0,
    TISCI_DEV_ICSSM0,
    TISCI_DEV_CPSW0,
    TISCI_DEV_CSI_RX_IF0,
    TISCI_DEV_USB0,
    TISCI_DEV_USB1,
    TISCI_DEV_MCAN0,
    TISCI_DEV_DSS0,
};

/* Array of SDL PBIST instance configurations */
PBIST_TestHandle_t PBIST_TestHandleArray[PBIST_NUM_INSTANCE] =
{
    {
        .pbistInst              = SDL_PBIST_INST_MCU,
        .numAuxDevices          = MCU_NUM_AUX_DEVICES,
        .auxDeviceIds          = &PBIST_MCUAuxDevList[0],
        .auxHandleFunction      = 0,
    },
    {
        .pbistInst              = SDL_PBIST_INST_MPU,
        .numAuxDevices          = MPU_NUM_AUX_DEVICES,
        .auxDeviceIds          = &PBIST_MPUAuxDevList[0],
        .auxHandleFunction      = SDL_PBIST_handleMPUAuxDevices,
    },
    {
        .pbistInst              = SDL_PBIST_INST_MAIN,
        .numAuxDevices          = MAIN_NUM_AUX_DEVICES,
        .auxDeviceIds          = &PBIST_MAINAuxDevList[0],
        .auxHandleFunction      = SDL_PBIST_handleMAINAuxDevices,
    },
};

/* SDL PBIST PSC Addresses of auxiliary devices required for SDL PSC functions */
uint32_t SDL_PBIST_pscAddress[PBIST_PSC_NUM_ADDR] =
{
    PBIST_A53_0_CLUSTER_ADDR,
    PBIST_A53_0_ADDR,
    PBIST_A53_1_ADDR,
    PBIST_A53_2_ADDR,
    PBIST_A53_3_ADDR,
    PBIST_USB0_ADDR,
    PBIST_USB1_ADDR,
};

/* Power Domain IDs of corresponding auxiliary devices that require SDL PSC functions */
uint32_t SDL_PBIST_pscPds[PBIST_PSC_NUM_ADDR] =
{
    CSL_MAIN_PD_A53_CLUSTER_0,
    CSL_MAIN_PD_A53_0,
    CSL_MAIN_PD_A53_1,
    CSL_MAIN_PD_A53_2,
    CSL_MAIN_PD_A53_3,
    CSL_MAIN_GP_CORE_CTL,
    CSL_MAIN_GP_CORE_CTL,
};

/* SDL PBIST function for bit shifts values of Power Domain IDs */
uint32_t SDL_PBIST_getPscShift(uint32_t pdId)
{
    return (1U << pdId);
}

/* SDL PSC function for Powering on/off of Auxiliary devices using Force bit */
int32_t SDL_PBIST_PSCForceBit(uint32_t pscAddr, uint32_t pdShift, bool powerOn)
{
    int32_t pscTimeout = PBIST_PSC_PTCMD_TIMEOUT;
    uint32_t pscRdValue;
    int32_t result = SDL_PASS;

    /* Read current value of the register */
    pscRdValue = HW_RD_REG32(pscAddr);
    /* Delete bits corresponding to state */
    pscRdValue &= ~PBIST_PSC_NEXT_MASK;

    /* Bits to be set for SyncRst state and Force bit */
    if (powerOn == true)
    {
        pscRdValue |= PBIST_PSC_FORCE_ON;
    }
    else
    {
        pscRdValue |= PBIST_PSC_FORCE_OFF;
    }

    /* Write back to the PSC register */
    HW_WR_REG32(pscAddr, pscRdValue);
    /* Write 1 to PSC_PTCMD to cause state change */
    HW_WR_REG32(PBIST_PSC_PTCMD_ADDR, pdShift);
    asm("dsb");
    asm("isb");

    /* Wait until state transition is completed */
    while (((HW_RD_REG32(PBIST_PSC_PTSTAT_ADDR) & pdShift) != 0) && (pscTimeout > 0))
    {
        pscTimeout--;
    }

    /* If the transition wait timed out */
    if ((HW_RD_REG32(PBIST_PSC_PTSTAT_ADDR) & pdShift) != 0)
    {
        result = SDL_EFAIL;
    }
    return result;
}

/* SDL function for handling all the PSC devices */
int32_t SDL_PBIST_handlePSCdevices(bool powerOn)
{
    SDL_ErrType_t status;
    uint32_t pdShift;

    for (int i = 0; i < PBIST_PSC_NUM_ADDR; i++)
    {
        pdShift = SDL_PBIST_getPscShift(SDL_PBIST_pscPds[i]);
        status = SDL_PBIST_PSCForceBit(SDL_PBIST_pscAddress[i],pdShift,powerOn);
        DebugP_assert(status == SDL_PASS);
    }

    return status;
}

/* SDL function to start PBIST selfTest of a given instance */
int32_t SDL_PBIST_startInstance(uint32_t instanceId, bool runPosTest)
{
    SDL_ErrType_t status;

    /* Power on all Auxiliary modules required for PBIST test */
    for (int i = 0; i < PBIST_TestHandleArray[instanceId].numAuxDevices; i++)
    {
        status = Sciclient_pmSetModuleState(PBIST_TestHandleArray[instanceId].auxDeviceIds[i],
                                            TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                            TISCI_MSG_FLAG_AOP,
                                            SystemP_WAIT_FOREVER);
        DebugP_assert(status == SDL_PASS);
    }

    /* Initialize Auxiliary devices with init set as TRUE */
    if (PBIST_TestHandleArray[instanceId].auxHandleFunction != 0)
    {
        status = PBIST_TestHandleArray[instanceId].auxHandleFunction(TRUE);
        DebugP_assert(status == SDL_PASS);
    }

    /* Start the PBIST test */
    if (runPosTest == true)
    {
        status = SDL_SBL_PBIST_selfTest((SDL_PBIST_inst)PBIST_TestHandleArray[instanceId].pbistInst, SDL_PBIST_TEST);
        DebugP_assert(status == SDL_PASS);
    }
    else
    {
        status = SDL_SBL_PBIST_selfTest((SDL_PBIST_inst)PBIST_TestHandleArray[instanceId].pbistInst, SDL_PBIST_NEG_TEST);
        DebugP_assert(status == SDL_PASS);
    }

    return (status);
}

/* SDL function for waiting on PBIST of a given instance */
int32_t SDL_PBIST_completeInstance(uint32_t instanceId)
{
    SDL_ErrType_t status = SystemP_FAILURE;
    int32_t timeoutCount = 0;

    while(timeoutCount < SDL_BIST_MAX_TIMEOUT_VALUE)
    {
        if(PBIST_DONE == SDL_SBL_PBIST_checkDone((SDL_PBIST_inst)PBIST_TestHandleArray[instanceId].pbistInst))
        {
            status = SystemP_SUCCESS;
            break;
        }
        timeoutCount++;
    }
    DebugP_assert(status == SystemP_SUCCESS);

    /* Restore Auxiliary devices with init set as FALSE */
    if (PBIST_TestHandleArray[instanceId].auxHandleFunction != 0)
    {
        status = PBIST_TestHandleArray[instanceId].auxHandleFunction(FALSE);
        DebugP_assert(status == SDL_PASS);
    }

    /* Power off all Auxiliary modules after a PBIST test */
    for (int i = 0; i < PBIST_TestHandleArray[instanceId].numAuxDevices; i++)
    {

        /* Powering off of PSC Auxiliary devices will be done by SDL PSC Function */

        if (PBIST_TestHandleArray[instanceId].auxDeviceIds[i] == TISCI_DEV_COMPUTE_CLUSTER0)
        {
            continue;
        }

        if (PBIST_TestHandleArray[instanceId].auxDeviceIds[i] == TISCI_DEV_A53SS0_CORE_0)
        {
            continue;
        }

        if (PBIST_TestHandleArray[instanceId].auxDeviceIds[i] == TISCI_DEV_A53SS0_CORE_1)
        {
            continue;
        }

        if (PBIST_TestHandleArray[instanceId].auxDeviceIds[i] == TISCI_DEV_A53SS0_CORE_2)
        {
            continue;
        }

        if (PBIST_TestHandleArray[instanceId].auxDeviceIds[i] == TISCI_DEV_A53SS0_CORE_3)
        {
            continue;
        }

        if (PBIST_TestHandleArray[instanceId].auxDeviceIds[i] == TISCI_DEV_USB0)
        {
            continue;
        }

        if (PBIST_TestHandleArray[instanceId].auxDeviceIds[i] == TISCI_DEV_USB1)
        {
            continue;
        }

        status = Sciclient_pmSetModuleState(PBIST_TestHandleArray[instanceId].auxDeviceIds[i],
                                            TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF,
                                            TISCI_MSG_FLAG_AOP,
                                            SystemP_WAIT_FOREVER);
        DebugP_assert(status == SDL_PASS);
    }

    return (status);
}

/* SDL function for starting PBIST tests of all selected instances */
int32_t SDL_PBIST_startAllTests(bool runPosTest)
{
    SDL_ErrType_t status;

    status = SDL_dplInit();
    DebugP_assert(status == SDL_PASS);

    /* Run PBIST tests for all selected instances */
    for (int i = 0; i < PBIST_NUM_INSTANCE; i++)
    {
        if (((SDL_PBIST_inst)PBIST_TestHandleArray[i].pbistInst == SDL_PBIST_INST_MCU) &&
            (Bootloader_socIsMCUResetIsoEnabled()))
        {
            continue;
        }

        status = SDL_PBIST_startInstance(i, runPosTest);
        DebugP_assert(status == SDL_PASS);

    }

    return (status);
}

/* SDL function for completing PBIST tests of all selected instances */
int32_t SDL_PBIST_completeAllTests(void)
{
    SDL_ErrType_t status;

    /* Wait for completion of PBIST tests for all selected instances */
    for (int i = 0; i < PBIST_NUM_INSTANCE; i++)
    {
        if (((SDL_PBIST_inst)PBIST_TestHandleArray[i].pbistInst == SDL_PBIST_INST_MCU) &&
            (Bootloader_socIsMCUResetIsoEnabled()))
        {
            continue;
        }

        status = SDL_PBIST_completeInstance(i);
        DebugP_assert(status == SDL_PASS);

    }

    return (status);
}

/*
 * MMCSD
 */

/* MMCSD attributes */
MMCSD_Attrs gMmcsdAttrs[CONFIG_MMCSD_NUM_INSTANCES] =
{
    {
        .ctrlBaseAddr         = CSL_MMCSD0_CTL_CFG_BASE,
        .ssBaseAddr           = CSL_MMCSD0_SS_CFG_BASE,
        .inputClkFreq         = 200000000U,
        .enableDma            = TRUE,
        .phyType              = MMCSD_PHY_TYPE_SW_PHY,
        .phyDriverType        = MMCSD_PHY_DRIVER_TYPE_0,
        .cardType             = MMCSD_CARD_TYPE_EMMC,
        .busWidth             = MMCSD_BUS_WIDTH_8BIT,
        .supportedModes       = MMCSD_SUPPORT_MMC_DS | MMCSD_SUPPORT_MMC_HS200,
        .tuningType           = MMCSD_PHY_TUNING_TYPE_MANUAL,
        .vddCoreVoltage       = MMCSD_VDD_CORE_0_85V,
    },
};
/* MMCSD objects - initialized by the driver */
static MMCSD_Object gMmcsdObjects[CONFIG_MMCSD_NUM_INSTANCES];
/* MMCSD driver configuration */
MMCSD_Config gMmcsdConfig[CONFIG_MMCSD_NUM_INSTANCES] =
{
    {
        &gMmcsdAttrs[CONFIG_MMCSD0],
        &gMmcsdObjects[CONFIG_MMCSD0],
    },
};

uint32_t gMmcsdConfigNum = CONFIG_MMCSD_NUM_INSTANCES;

/*
 * QoS
 */

/* QoS configuration data file */
#include "drivers/qos/v0/soc/am62x/qos_data.h"

/*
 * UART
 */

/* UART atrributes */
static UART_Attrs gUartAttrs[CONFIG_UART_NUM_INSTANCES] =
{
    {
        .baseAddr           = CSL_UART0_BASE,
        .inputClkFreq       = 48000000U,
    },
};
/* UART objects - initialized by the driver */
static UART_Object gUartObjects[CONFIG_UART_NUM_INSTANCES];
/* UART driver configuration */
UART_Config gUartConfig[CONFIG_UART_NUM_INSTANCES] =
{
    {
        .attrs = &gUartAttrs[CONFIG_UART0],
        .object = &gUartObjects[CONFIG_UART0],
        .traceInstance = FALSE,
    },
};

uint32_t gUartConfigNum = CONFIG_UART_NUM_INSTANCES;

#include <drivers/uart/v0/dma/uart_dma.h>


UART_DmaConfig gUartDmaConfig[CONFIG_UART_NUM_DMA_INSTANCES] =
{
};

uint32_t gUartDmaConfigNum = CONFIG_UART_NUM_DMA_INSTANCES;


void Drivers_uartInit(void)
{
    UART_init();
}


void Pinmux_init();
void PowerClock_init(void);
void PowerClock_deinit(void);

/*
 * Common Functions
 */
void System_init(void)
{
    /* DPL init sets up address transalation unit, on some CPUs this is needed
     * to access SCICLIENT services, hence this needs to happen first
     */
    Dpl_init();
    /* We should do sciclient init before we enable power and clock to the peripherals */
    /* SCICLIENT init */
    {

        int32_t retVal = SystemP_SUCCESS;

        retVal = Sciclient_direct_init();
        DebugP_assertNoLog(SystemP_SUCCESS == retVal);

    }


   


    PowerClock_init();
    /* Now we can do pinmux */
    Pinmux_init();
    /* finally we initialize all peripheral drivers */
    Drivers_uartInit();

    /* BIST */
    {
        int32_t status;

        /* Unlock MMRs */
        SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, 4u);
        SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MCU, 3u);


        /* Start Positive PBIST tests of all selected instances*/
        status = SDL_PBIST_startAllTests(true);
        DebugP_assert(status == SDL_PASS);
    }

	DDR_init(&gDdrParams);

    QOS_init(gQosData, gQosCount);
    /* UDMA */
    {
        uint32_t        instId;
        int32_t         retVal = UDMA_SOK;

        for(instId = 0U; instId < CONFIG_UDMA_NUM_INSTANCES; instId++)
        {
            retVal += Udma_init(&gUdmaDrvObj[instId], &gUdmaInitPrms[instId]);
            DebugP_assert(UDMA_SOK == retVal);
        }
    }
	GTC_init();

    MMCSD_init();
}

void System_deinit(void)
{
    /* UDMA */
    {
        uint32_t        instId;
        int32_t         retVal = UDMA_SOK;

        for(instId = 0U; instId < CONFIG_UDMA_NUM_INSTANCES; instId++)
        {
            retVal += Udma_deinit(&gUdmaDrvObj[instId]);
            DebugP_assert(UDMA_SOK == retVal);
        }
    }
    MMCSD_deinit();
    UART_deinit();
    PowerClock_deinit();
    /* SCICLIENT deinit */
    {
        int32_t         retVal = SystemP_SUCCESS;

        retVal = Sciclient_deinit();
        DebugP_assertNoLog(SystemP_SUCCESS == retVal);
    }
    Dpl_deinit();
}
