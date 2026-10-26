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
 * OSPI
 */


/* Regions restricted for DMA. We should use CPU memcpy in these cases */
static OSPI_AddrRegion gOspiDmaRestrictRegions[] =
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

/* OSPI attributes */
static OSPI_Attrs gOspiAttrs[CONFIG_OSPI_NUM_INSTANCES] =
{
    {
        .baseAddr             = CSL_FSS0_OSPI0_CTRL_BASE,
        .dataBaseAddr         = CSL_FSS0_DAT_REG1_BASE,
        .moduleId             = TISCI_DEV_FSS0_OSPI_0,
        .clkId                = TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK,
        .inputClkFreq         = 166666666U,
        .intrNum              = 171U,
        .intrEnable           = FALSE,
        .intrPriority         = 4U,
        .dmaEnable            = TRUE,
        .phyEnable            = TRUE,
        .phySkipTuning        = FALSE,
        .dacEnable            = FALSE,
        .chipSelect           = OSPI_CS0,
        .frmFmt               = OSPI_FF_POL0_PHA0,
        .decChipSelect        = OSPI_DECODER_SELECT4,
        .readMode             = OSPI_READ_MODE_DAC,
        .baudRateDiv          = 8,
        .phaseDelayElement    = 3,
        .validateOtp          = FALSE,
        .dmaRestrictedRegions = gOspiDmaRestrictRegions,
        .phyConfiguration     = {
            .phyControlMode = OSPI_FLASH_CFG_PHY_MASTER_CONTROL_REG_PHY_MASTER_MODE,
            .dllLockMode    = OSPI_PHY_DLL_HALF_CYCLE_LOCK,
            .phyParams = {
                .radius = 5,
                .rxTxDllMin = 0,
                .rxTxDllMax = 127,
                .minReadDelay = 0,
                .maxReadDelay = 4,
                .minPassSize = 100,
                .diagonalShift = 10,
                .maxDiagonalShift = 70,
                .numConsecutiveFail = 5,
                .numConsecutivePass = 10,
                .rdDelaySearchStep = 16,
            }
        }
    },
};
/* OSPI objects - initialized by the driver */
static OSPI_Object gOspiObjects[CONFIG_OSPI_NUM_INSTANCES];
/* OSPI driver configuration */
OSPI_Config gOspiConfig[CONFIG_OSPI_NUM_INSTANCES] =
{
    {
        &gOspiAttrs[CONFIG_OSPI0],
        &gOspiObjects[CONFIG_OSPI0],
    },
};

uint32_t gOspiConfigNum = CONFIG_OSPI_NUM_INSTANCES;

#include <drivers/ospi/v0/dma/ospi_dma.h>
#include <drivers/ospi/v0/dma/udma/ospi_dma_udma.h>
#include <drivers/udma.h>

/*
 * OSPI UDMA Blockcopy Parameters
 */
#define OSPI_UDMA_BLK_COPY_CH_RING_ELEM_CNT (1U)
#define OSPI_UDMA_BLK_COPY_CH_RING_MEM_SIZE (((OSPI_UDMA_BLK_COPY_CH_RING_ELEM_CNT * 8U) + UDMA_CACHELINE_ALIGNMENT) & ~(UDMA_CACHELINE_ALIGNMENT - 1U))
#define OSPI_UDMA_BLK_COPY_CH_TRPD_MEM_SIZE (UDMA_GET_TRPD_TR15_SIZE(1U))
#define OSPI_UDMA_NUM_BLKCOPY_CH (1U)

/* OSPI UDMA Blockcopy Channel Objects */
static Udma_ChObject gOspiUdmaBlkCopyChObj[OSPI_UDMA_NUM_BLKCOPY_CH];

/* OSPI UDMA Blockcopy Channel Ring Mem */
static uint8_t gOspiUdmaBlkCopyCh0RingMem[OSPI_UDMA_BLK_COPY_CH_RING_MEM_SIZE] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));

/* OSPI UDMA Blockcopy Channel TRPD Mem */
static uint8_t gOspiUdmaBlkCopyCh0TrpdMem[OSPI_UDMA_BLK_COPY_CH_TRPD_MEM_SIZE] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));

OspiDma_UdmaArgs gOspiUdma0Args =
{
    .drvHandle     = &gUdmaDrvObj[CONFIG_UDMA0],
    .chHandle      = &gOspiUdmaBlkCopyChObj[0],
    .trpdMem       = &gOspiUdmaBlkCopyCh0TrpdMem,
    .trpdMemSize   = OSPI_UDMA_BLK_COPY_CH_TRPD_MEM_SIZE,
    .ringMem       = &gOspiUdmaBlkCopyCh0RingMem,
    .ringMemSize   = OSPI_UDMA_BLK_COPY_CH_RING_MEM_SIZE,
    .ringElemCount = OSPI_UDMA_BLK_COPY_CH_RING_ELEM_CNT,
};
OSPI_DmaConfig gOspiDmaConfig[CONFIG_OSPI_NUM_DMA_INSTANCES] =
{
    {
        .fxns        = &gOspiDmaUdmaFxns,
        .ospiDmaArgs = (void *)&gOspiUdma0Args,
    }
};

uint32_t gOspiDmaConfigNum = CONFIG_OSPI_NUM_DMA_INSTANCES;


/*
 * BOOTLOADER
 */
/* Include ti_board_config.h for flash config macros */
#include "ti_board_config.h"

/* Bootloader boot media specific arguments */
Bootloader_FlashArgs gBootloader0Args =
{
    .flashIndex     = CONFIG_FLASH0,
    .curOffset      = 0,
    .appImageOffset = 0x100000,
    .flashType      = CONFIG_FLASH_TYPE_SERIAL_NOR,
};
Bootloader_FlashArgs gBootloader1Args =
{
    .flashIndex     = CONFIG_FLASH0,
    .curOffset      = 0,
    .appImageOffset = 0x80000,
    .flashType      = CONFIG_FLASH_TYPE_SERIAL_NOR,
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
        &gBootloaderFlashFxns,
        &gBootloader0Args,
        BOOTLOADER_MEDIA_FLASH,
        0,
        0,
        NULL,
        .socCoreOpMode= (void *)&operatingMode,
    },
    {
        &gBootloaderFlashFxns,
        &gBootloader1Args,
        BOOTLOADER_MEDIA_FLASH,
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
 * Lists of SDL Auxiliary Devices for each selected PBIST instance
 * (the lists include PBIST devices)
 */
uint32_t PBIST_MCUAuxDevList[MCU_NUM_AUX_DEVICES]  =
{
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
};

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
    OSPI_init();
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

}

void System_deinit(void)
{
    OSPI_deinit();

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
