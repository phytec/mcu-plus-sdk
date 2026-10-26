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

#ifndef TI_DRIVERS_CONFIG_H_
#define TI_DRIVERS_CONFIG_H_

#include <stdint.h>
#include <drivers/hw_include/cslr_soc.h>
#include "ti_dpl_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Common Functions
 */
void System_init(void);
void System_deinit(void);



/*
 * BOOTLOADER
 */
#include <drivers/bootloader.h>

extern Bootloader_MemArgs gMemBootloaderArgs;

/* BOOTLOADER Instance Macros */
#define CONFIG_BOOTLOADER_EMMC_MCU (0U)
#define CONFIG_BOOTLOADER_EMMC_SBL (1U)
#define CONFIG_BOOTLOADER_NUM_INSTANCES (2U)

/*
 * UDMA
 */
#include <drivers/udma.h>

/* UDMA Instance Macros */
#define CONFIG_UDMA0 (0U)
#define CONFIG_UDMA_NUM_INSTANCES (1U)

/* UDMA Driver Objects */
extern Udma_DrvObject   gUdmaDrvObj[CONFIG_UDMA_NUM_INSTANCES];

/* UDMA functions as specified in SYSCONFIG */
/* For instance CONFIG_UDMA0 */
extern uint64_t Udma_defaultVirtToPhyFxn(const void *virtAddr, uint32_t chNum, void *appData);
extern void *Udma_defaultPhyToVirtFxn(uint64_t phyAddr, uint32_t chNum, void *appData);

/*
 * DDR
 */
#include <drivers/ddr.h>


/*
 * GTC
 */
#include <drivers/gtc.h>

/*
 * PBIST
 */
#include <kernel/dpl/AddrTranslateP.h>
#include <sdl/include/sdl_types.h>
#include <sdl/dpl/sdl_dpl.h>
#include <sdl/sdl_pbist.h>

/* Timeout for PBIST completion */
#define SDL_BIST_MAX_TIMEOUT_VALUE                      (10000000u)
#define SDL_NUM_HWIP_OBJECTS                            10

/* Number of PBIST Instances selected */
#define PBIST_NUM_INSTANCE                              (3U)

/* Number of Auxiliary Devices of selected PBIST instances */
#define MCU_NUM_AUX_DEVICES            0
#define MPU_NUM_AUX_DEVICES            6
#define MAIN_NUM_AUX_DEVICES            8

/* Used for BISOR override in SDL_PBIST_handleMPUAuxDevices */
#define SDL_WKUP_CTRL_MMR_CFG0_A53SS_DFT_CTL            (0x00010600U)

/* The following macros will be used in modifying PSC register values */
#define PBIST_PSC_NEXT_MASK                             (0x0000003F)
#define PBIST_PSC_FORCE_OFF                             (0x80000000)
#define PBIST_PSC_FORCE_ON                              (0x80000003)
#define PBIST_PSC_PTCMD_ADDR                            (0x400120)
#define PBIST_PSC_PTCMD_TIMEOUT                         (1000000U)
#define PBIST_PSC_PTSTAT_ADDR                           (0x400128)

/* Addresses of PBIST PSC devices */
#define PBIST_PSC_BASE_ADDR                             ((uint32_t)0x400A00)
#define PBIST_A53_0_CLUSTER_ADDR                            (PBIST_PSC_BASE_ADDR + 4 * CSL_MAIN_LPSC_A53_CLUSTER_0)
#define PBIST_A53_0_ADDR                            (PBIST_PSC_BASE_ADDR + 4 * CSL_MAIN_LPSC_A53_0)
#define PBIST_A53_1_ADDR                            (PBIST_PSC_BASE_ADDR + 4 * CSL_MAIN_LPSC_A53_1)
#define PBIST_A53_2_ADDR                            (PBIST_PSC_BASE_ADDR + 4 * CSL_MAIN_LPSC_A53_2)
#define PBIST_A53_3_ADDR                            (PBIST_PSC_BASE_ADDR + 4 * CSL_MAIN_LPSC_A53_3)
#define PBIST_USB0_ADDR                            (PBIST_PSC_BASE_ADDR + 4 * CSL_MAIN_LPSC_USB_0)
#define PBIST_USB1_ADDR                            (PBIST_PSC_BASE_ADDR + 4 * CSL_MAIN_LPSC_USB_1)
#define PBIST_PSC_NUM_ADDR                              7

typedef int32_t (*PBIST_auxHandleFunctionPtr)(bool init);

typedef struct PBIST_TestHandle_s
{
    SDL_PBIST_inst pbistInst;
    uint32_t numAuxDevices;                             /* Number of Aux devices */
    uint32_t *auxDeviceIds;                            /* Array of Aux device ids */
    PBIST_auxHandleFunctionPtr auxHandleFunction;       /* Auxiliary handle function */
} PBIST_TestHandle_t;

/* SDL functions for initialization or completion of PBIST tests */

int32_t SDL_PBIST_startAllTests(bool runNegTest);
int32_t SDL_PBIST_completeAllTests(void);

/* SDL functions for handling PSC devices */
int32_t SDL_PBIST_handlePSCdevices(bool powerOn);

/*
 * MMCSD
 */
#include <drivers/mmcsd.h>

/* MMCSD Instance Macros */
#define CONFIG_MMCSD0 (0U)
#define CONFIG_MMCSD_NUM_INSTANCES (1U)

/*
 * QoS
 */
#include <drivers/qos.h>

/*
 * UART
 */
#include <drivers/uart.h>

/* UART Instance Macros */
#define CONFIG_UART0 (0U)
#define CONFIG_UART_NUM_INSTANCES (1U)
#define CONFIG_UART_NUM_DMA_INSTANCES (0U)


#include <drivers/soc.h>
#include <kernel/dpl/CycleCounterP.h>

#ifdef __cplusplus
}
#endif

#endif /* TI_DRIVERS_CONFIG_H_ */
