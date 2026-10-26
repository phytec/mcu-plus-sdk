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
 * OSPI
 */
#include <drivers/ospi.h>

/* OSPI Instance Macros */
#define CONFIG_OSPI0 (0U)
#define CONFIG_OSPI_NUM_INSTANCES (1U)
#define CONFIG_OSPI_NUM_DMA_INSTANCES (1U)
/*
 * BOOTLOADER
 */
#include <drivers/bootloader.h>

extern Bootloader_MemArgs gMemBootloaderArgs;

/* BOOTLOADER Instance Macros */
#define CONFIG_BOOTLOADER_FLASH_MCU (0U)
#define CONFIG_BOOTLOADER_FLASH_SBL (1U)
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
#define PBIST_NUM_INSTANCE                              (1U)

/* Number of Auxiliary Devices of selected PBIST instances */
#define MCU_NUM_AUX_DEVICES            0

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
