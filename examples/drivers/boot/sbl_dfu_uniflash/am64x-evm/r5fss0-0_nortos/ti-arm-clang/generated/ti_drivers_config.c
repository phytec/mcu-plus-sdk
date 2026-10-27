/*
 *  Copyright (C) 2021 Texas Instruments Incorporated
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
#include <drivers/sciclient.h>
#include <string.h>

/*
 * OSPI
 */


/* Regions restricted for DMA. We should use CPU memcpy in these cases */
static OSPI_AddrRegion gOspiDmaRestrictRegions[] = 
{
    {
        .regionStartAddr = CSL_R5FSS0_ATCM_BASE,
        .regionSize      = CSL_R5FSS0_ATCM_SIZE,
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
        .protocol             = OSPI_PROTO_8D_8D_8D,
        .dataBaseAddr         = CSL_FSS0_DAT_REG1_BASE,
        .moduleId             = TISCI_DEV_FSS0_OSPI_0,
        .clkId                = TISCI_DEV_FSS0_OSPI_0_OSPI_RCLK_CLK,
        .inputClkFreq         = 133333333U,
        .intrNum              = 171U,
        .intrEnable           = FALSE,
        .intrPriority         = 4U,
        .dmaEnable            = TRUE,
        .phyEnable            = FALSE,
        .dacEnable            = FALSE,
        .chipSelect           = OSPI_CS0,
        .frmFmt               = OSPI_FF_POL0_PHA0,
        .decChipSelect        = OSPI_DECODER_SELECT4,
        .baudRateDiv          = 4,
        .dmaRestrictedRegions = gOspiDmaRestrictRegions,
        .validateOtp          = false,
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

#include <drivers/ospi/v0/lld/dma/udma/ospi_udma_lld.h>
#include <drivers/ospi/v0/lld/dma/soc/ospi_dma_soc.h>
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

OSPI_UdmaParams gOspiUdma0Args =
{
    .drvHandle     = &gUdmaDrvObj[CONFIG_UDMA0],
    .chHandle      = &gOspiUdmaBlkCopyChObj[0],
    .trpdMem       = &gOspiUdmaBlkCopyCh0TrpdMem,
    .trpdMemSize   = OSPI_UDMA_BLK_COPY_CH_TRPD_MEM_SIZE,
    .ringMem       = &gOspiUdmaBlkCopyCh0RingMem,
    .ringMemSize   = OSPI_UDMA_BLK_COPY_CH_RING_MEM_SIZE,
    .ringElemCount = OSPI_UDMA_BLK_COPY_CH_RING_ELEM_CNT,
    .isCqRingMem   = UDMA_COMP_QUEUE_RING_MEM_DISABLE,
};
OSPI_DmaConfig gOspiDmaConfig[CONFIG_OSPI_NUM_DMA_INSTANCES] =
{
    {
        .ospiDmaArgs = (void *)&gOspiUdma0Args,
    }
};

uint32_t gOspiDmaConfigNum = CONFIG_OSPI_NUM_DMA_INSTANCES;


/*
 * BOOTLOADER
 */

/* Bootloader boot media specific arguments */
Bootloader_MemArgs gBootloader0Args =
{
    .curOffset        = 0,
    .appImageBaseAddr = 0x00000000,
};

/* Configuration option for lockstep or standalone */
void* operatingMode = NULL;

Bootloader_MemArgs gMemBootloaderArgs =
{
    .curOffset = 0,
    .appImageBaseAddr = 0,
};

/* Bootloader driver configuration */
Bootloader_Config gBootloaderConfig[CONFIG_BOOTLOADER_NUM_INSTANCES] =
{
    {
        &gBootloaderMemFxns,
        &gBootloader0Args,
        BOOTLOADER_MEDIA_MEM,
        0,
        0,
        NULL,
        .socCoreOpMode= (void *)&operatingMode,
        .isAppimageSigned = TRUE,
        .disableAppImageAuth = FALSE,
        .initICSSCores = TRUE,
        BOOTLOADER_SCRATCH_MEM_ENABLE,
    },
};

uint32_t gBootloaderConfigNum = CONFIG_BOOTLOADER_NUM_INSTANCES;


/*
 * MMCSD
 */

/* MMCSD attributes */
static MMCSD_Attrs gMmcsdAttrs[CONFIG_MMCSD_NUM_INSTANCES] =
{
    {
        .ctrlBaseAddr         = CSL_MMCSD0_CTL_CFG_BASE,
        .ssBaseAddr           = CSL_MMCSD0_SS_CFG_BASE,
        .inputClkFreq         = 200000000U,
        .intrNum              = 165U,
        .intrEnable           = false,
        .enableDma            = false,
        .phyType              = MMCSD_PHY_TYPE_HW_PHY,
        .cardType             = MMCSD_CARD_TYPE_EMMC,
        .busWidth               = MMCSD_BUS_WIDTH_4BIT,
        .tuningType           = MMCSD_PHY_TUNING_TYPE_AUTO,
        .autoAssignMaxSpeed     = true,
        .uaBusSpeed             = MMCSD_MMC_MODE_HS200,
        .slotType               = MMCSD_SLOT_TYPE_VAL_EMBEDDED,
        .pllEnableSD            = false,
        .intrPriority           = 4,
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
 * UDMA
 */
 #include <drivers/udma.h>
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


/*
 * MCU_LBIST
 */

uint32_t gMcuLbistTestStatus = 0U;

void SDL_lbist_selftest(void)
{
}

void Pinmux_init(void);
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

        retVal = Sciclient_init(CSL_CORE_ID_R5FSS0_0);
        DebugP_assertNoLog(SystemP_SUCCESS == retVal);
    }

    
    PowerClock_init();
    /* Now we can do pinmux */
    Pinmux_init();
    /* finally we initialize all peripheral drivers */
    OSPI_init();
    MMCSD_init();
    /* UDMA */
    {
        uint32_t        instId;
        int32_t         retVal = UDMA_SOK;

        for(instId = 0U; instId < CONFIG_UDMA_NUM_INSTANCES; instId++)
        {
            retVal += Udma_init((Udma_DrvHandle)&gUdmaDrvObj[instId], &gUdmaInitPrms[instId]);
            DebugP_assert(UDMA_SOK == retVal);
        }
    }
}

void System_deinit(void)
{
    OSPI_deinit();
    MMCSD_deinit();
    /* UDMA */
    {
        uint32_t        instId;
        int32_t         retVal = UDMA_SOK;

        for(instId = 0U; instId < CONFIG_UDMA_NUM_INSTANCES; instId++)
        {
            retVal += Udma_deinit((Udma_DrvHandle)&gUdmaDrvObj[instId]);
            DebugP_assert(UDMA_SOK == retVal);
        }
    }
    PowerClock_deinit();
    /* SCICLIENT deinit */
    {
        int32_t         retVal = SystemP_SUCCESS;

        retVal = Sciclient_deinit();
        DebugP_assertNoLog(SystemP_SUCCESS == retVal);
    }

    Dpl_deinit();
}
