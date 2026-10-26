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
/* Include ti_board_config.h for flash config macros */
#include "ti_board_config.h"

/* Bootloader boot media specific arguments */
Bootloader_FlashArgs gBootloader0Args =
{
    .flashIndex     = CONFIG_FLASH0,
    .curOffset      = 0,
    .appImageOffset = 0x100000,
    .flashType      = CONFIG_FLASH_TYPE_PARALLEL_NAND,
};
Bootloader_FlashArgs gBootloader1Args =
{
    .flashIndex     = CONFIG_FLASH0,
    .curOffset      = 0,
    .appImageOffset = 0x80000,
    .flashType      = CONFIG_FLASH_TYPE_PARALLEL_NAND,
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
#include "drivers/ddr/v0/soc/am62x/board_lpddrReginit.h"


static DDR_Params gDdrParams =
{
    /* below values are set using the globals defined in drivers/ddr/v0/soc/am62x/board_lpddrReginit.h */
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
 * QoS
 */

/* QoS configuration data file */
#include "drivers/qos/v0/soc/am62x/qos_data.h"


/*
 * GPMC
 */

/* Regions restricted for DMA. We should use CPU memcpy in these cases */
static GPMC_AddrRegion gGpmcDmaRestrictRegions[] =
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


/* GPMC attributes */
static GPMC_HwAttrs gGpmcAttrs[CONFIG_GPMC_NUM_INSTANCES] =
{
    {
        .gpmcBaseAddr         = CSL_GPMC0_CFG_BASE,
        .dataBaseAddr         = CSL_GPMC0_DATA_BASE,
        .elmBaseAddr          = CSL_ELM0_BASE,
        .inputClkFreq         = 133333333U,
        .intrNum              = 103U,
        .intrPriority         = 4U,
        .chipSelBaseAddr      = 0x50000000U,
        .chipSelAddrSize      = GPMC_CS_MASK_ADDR_SIZE_16MB,
        .clkDivider           = CSL_GPMC_CONFIG1_GPMCFCLKDIVIDER_DIVBY1,
        .waitPinNum           = CSL_GPMC_CONFIG1_WAITPINSELECT_W0,
        .addrDataMux          = CSL_GPMC_CONFIG1_MUXADDDATA_NONMUX,
        .timeLatency          = CSL_GPMC_CONFIG1_TIMEPARAGRANULARITY_X1,
        .waitPinPol           = CSL_GPMC_CONFIG_WAIT0PINPOLARITY_W0ACTIVEL,
        .timingParams         =
        {
            .csOnTime               =   0U,
            .csRdOffTime            =   4U,
            .csWrOffTime            =   6U,
            .advOnTime              =   0U,
            .advRdOffTime           =   4U,
            .advWrOffTime           =   4U,
            .advAadMuxOnTime        =   0U,
            .advAadMuxRdOffTime     =   0U,
            .advAadMuxWrOffTime     =   0U,
            .weOnTtime              =   0U,
            .weOffTime              =   3U,
            .oeOnTime               =   1U,
            .oeOffTime              =   3U,
            .oeAadMuxOnTime         =   0U,
            .oeAadMuxOffTime        =   0U,
            .pageBurstAccess        =   0U,
            .rdAccessTime           =   4U,
            .wrAcessTime            =   6U,
            .rdCycleTime            =   4U,
            .wrCycleTime            =   5U,
            .wrDataOnMuxBusTime     =   0U,
            .cycle2CycleDelay       =   0U,
            .busTurnAroundTime      =   0U,
            .cycleDelaySameChipSel  =   CSL_GPMC_CONFIG6_CYCLE2CYCLESAMECSEN_NOC2CDELAY,
            .cycleDelayDiffChipSel  =   CSL_GPMC_CONFIG6_CYCLE2CYCLEDIFFCSEN_NOC2CDELAY,
        },
        .eccAlgo                =   GPMC_NAND_ECC_ALGO_BCH_8BIT,
        .readType               =   CSL_GPMC_CONFIG1_READTYPE_RDASYNC,
        .csExDelay              =   CSL_GPMC_CONFIG2_CSEXTRADELAY_NOTDELAYED,
        .accessType             =   CSL_GPMC_CONFIG1_READMULTIPLE_RDSINGLE,
        .optimisedAccess        =   CSL_GPMC_PREFETCH_CONFIG1_ENABLEOPTIMIZEDACCESS_OPTDISABLED,
        .dmaRestrictedRegions   =   gGpmcDmaRestrictRegions,
    },
};
/* GPMC objects - initialized by the driver */
static GPMC_Object gGpmcObjects[CONFIG_GPMC_NUM_INSTANCES];
/* GPMC driver configuration */
GPMC_Config gGpmcConfig[CONFIG_GPMC_NUM_INSTANCES] =
{
    {
        &gGpmcAttrs[CONFIG_GPMC0],
        &gGpmcObjects[CONFIG_GPMC0],
    },
};

uint32_t gGpmcConfigNum = CONFIG_GPMC_NUM_INSTANCES;




#include <drivers/gpmc/v0/dma/gpmc_dma.h>
#include <drivers/gpmc/v0/dma/udma/gpmc_dma_udma.h>
#include <drivers/udma.h>


/*
 * GPMC UDMA Blockcopy Parameters
 */
#define GPMC_UDMA_BLK_COPY_CH_RING_ELEM_CNT (1U)
#define GPMC_UDMA_BLK_COPY_CH_RING_MEM_SIZE (((GPMC_UDMA_BLK_COPY_CH_RING_ELEM_CNT * 8U) + UDMA_CACHELINE_ALIGNMENT) & ~(UDMA_CACHELINE_ALIGNMENT - 1U))
#define GPMC_UDMA_BLK_COPY_CH_TRPD_MEM_SIZE (UDMA_GET_TRPD_TR15_SIZE(1U))
#define GPMC_UDMA_NUM_BLKCOPY_CH (1U)

/* GPMC UDMA Blockcopy Channel Objects */
static Udma_ChObject gGpmcUdmaBlkCopyChObj[GPMC_UDMA_NUM_BLKCOPY_CH];

/* GPMC UDMA Blockcopy Channel Ring Mem */
static uint8_t gGpmcUdmaBlkCopyCh0RingMem[GPMC_UDMA_BLK_COPY_CH_RING_MEM_SIZE] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));

/* GPMC UDMA Blockcopy Channel TRPD Mem */
static uint8_t gGpmcUdmaBlkCopyCh0TrpdMem[GPMC_UDMA_BLK_COPY_CH_TRPD_MEM_SIZE] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));

GpmcDma_UdmaArgs gGpmcUdma0Args =
{
    .drvHandle     = &gUdmaDrvObj[CONFIG_UDMA0],
    .chHandle      = &gGpmcUdmaBlkCopyChObj[0],
    .trpdMem       = &gGpmcUdmaBlkCopyCh0TrpdMem,
    .trpdMemSize   = GPMC_UDMA_BLK_COPY_CH_TRPD_MEM_SIZE,
    .ringMem       = &gGpmcUdmaBlkCopyCh0RingMem,
    .ringMemSize   = GPMC_UDMA_BLK_COPY_CH_RING_MEM_SIZE,
    .ringElemCount = GPMC_UDMA_BLK_COPY_CH_RING_ELEM_CNT,
    .localEventID  = 26,
};
GPMC_DmaConfig gGpmcDmaConfig[CONFIG_GPMC_NUM_DMA_INSTANCES] =
{
    {
        .fxns        = &gGpmcDmaUdmaFxns,
        .gpmcDmaArgs = (void *)&gGpmcUdma0Args,
    }
};

uint32_t gGpmcDmaConfigNum = CONFIG_GPMC_NUM_DMA_INSTANCES;



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

    GPMC_init();
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
    GPMC_deinit();
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
