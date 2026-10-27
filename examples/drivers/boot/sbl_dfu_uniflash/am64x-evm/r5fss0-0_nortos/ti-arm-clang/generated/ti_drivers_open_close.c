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

#include "ti_drivers_open_close.h"
#include <kernel/dpl/DebugP.h>

void Drivers_open(void)
{
    Drivers_mmcsdOpen();
    Drivers_ospiOpen();
    Drivers_usbOpen();
    Drivers_udmaOpen();
}

void Drivers_close(void)
{
    Drivers_ospiClose();
    Drivers_usbClose();
    Drivers_udmaClose();
    Drivers_mmcsdClose();
}

/*
 * OSPI
 */
/* OSPI Driver handles */
OSPI_Handle gOspiHandle[CONFIG_OSPI_NUM_INSTANCES];

/* OSPI Driver Parameters */
OSPI_Params gOspiParams[CONFIG_OSPI_NUM_INSTANCES] =
{
    {
        .ospiDmaChIndex = 0,
    },
};

void Drivers_ospiOpen(void)
{
    uint32_t instCnt;
    int32_t  status = SystemP_SUCCESS;

    for(instCnt = 0U; instCnt < CONFIG_OSPI_NUM_INSTANCES; instCnt++)
    {
        gOspiHandle[instCnt] = NULL;   /* Init to NULL so that we can exit gracefully */
    }

    /* Open all instances */
    for(instCnt = 0U; instCnt < CONFIG_OSPI_NUM_INSTANCES; instCnt++)
    {
        gOspiHandle[instCnt] = OSPI_open(instCnt, &gOspiParams[instCnt]);
        if(NULL == gOspiHandle[instCnt])
        {
            DebugP_logError("OSPI open failed for instance %d !!!\r\n", instCnt);
            status = SystemP_FAILURE;
            break;
        }
    }

    if(SystemP_FAILURE == status)
    {
        Drivers_ospiClose();   /* Exit gracefully */
    }

    return;
}

void Drivers_ospiClose(void)
{
    uint32_t instCnt;

    /* Close all instances that are open */
    for(instCnt = 0U; instCnt < CONFIG_OSPI_NUM_INSTANCES; instCnt++)
    {
        if(gOspiHandle[instCnt] != NULL)
        {
            OSPI_close(gOspiHandle[instCnt]);
            gOspiHandle[instCnt] = NULL;
        }
    }

    return;
}

/*
 * MMCSD
 */
/* MMCSD Device Data structures */
MMCSD_EmmcDeviceData gEmmcData0;

/* MMCSD temporary data buffers */
uint8_t gMmcsdDataBuf0[512U] __attribute__((aligned(128U)));;


/* MMCSD Driver handles */
MMCSD_Handle gMmcsdHandle[CONFIG_MMCSD_NUM_INSTANCES];

/* MMCSD Driver Parameters */
MMCSD_Params gMmcsdParams[CONFIG_MMCSD_NUM_INSTANCES] =
{
    {
        .deviceData = &gEmmcData0,
        .dataBuf    = &gMmcsdDataBuf0[0],
        .transferMode = MMCSD_MODE_BLOCKING,
        .txnCallbackFxn = NULL,
    },
};

void Drivers_mmcsdOpen(void)
{
    uint32_t instCnt;
    int32_t  status = SystemP_SUCCESS;

    for(instCnt = 0U; instCnt < CONFIG_MMCSD_NUM_INSTANCES; instCnt++)
    {
        gMmcsdHandle[instCnt] = NULL;   /* Init to NULL so that we can exit gracefully */
    }

    /* Open all instances */
    for(instCnt = 0U; instCnt < CONFIG_MMCSD_NUM_INSTANCES; instCnt++)
    {
        gMmcsdHandle[instCnt] = MMCSD_open(instCnt, &gMmcsdParams[instCnt]);
        if(NULL == gMmcsdHandle[instCnt])
        {
            DebugP_logError("MMCSD open failed for instance %d !!!\r\n", instCnt);
            status = SystemP_FAILURE;
            break;
        }
    }

    if(SystemP_FAILURE == status)
    {
        Drivers_mmcsdClose();   /* Exit gracefully */
    }

    return;
}

void Drivers_mmcsdClose(void)
{
    uint32_t instCnt;

    /* Close all instances that are open */
    for(instCnt = 0U; instCnt < CONFIG_MMCSD_NUM_INSTANCES; instCnt++)
    {
        if(gMmcsdHandle[instCnt] != NULL)
        {
            MMCSD_close(gMmcsdHandle[instCnt]);
            gMmcsdHandle[instCnt] = NULL;
        }
    }

    return;
}

/*
 * USB
 */
#define USB_CLK_SEL_HFOSC0_CLKOUT   (0x00U)
#define USB_CLK_SEL_HFOSC1_CLKOUT   (0x01U)
/* USB init Parameters */
static usb_init_param_t gUsbInitParam = {
    0,                          /*< for AM64x/AM243x only instance 0 is available */
    USB_CLK_SEL_HFOSC0_CLKOUT,  /*< select HFOSC0_CLKOUT for USB clock source */
    6,                          /*< for AM64x/AM243x EVM set PHY ref clock selection to 6 for 25Mhz */
    1,                          /*< enable USB 2.0 only (disable USB 3.0) */
    0,                          /*< no invert polarity */
    1,                          /*< VBUS_SEL for external divider */
    0                           /*< set to device mode */
};

void Drivers_usbOpen(void)
{
    /* initialize USB HW for TI SOC */
    usb_init(&gUsbInitParam);
    /* tiny USB init */
    tusb_init();

    return;
}

void Drivers_usbClose(void)
{
    return;
}

/*
 * UDMA
 */

void Drivers_udmaOpen(void)
{
}

void Drivers_udmaClose(void)
{
}

