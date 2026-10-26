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

#include "ti_drivers_open_close.h"
#include <kernel/dpl/DebugP.h>

void Drivers_open(void)
{


    Drivers_uartOpen();
    Drivers_udmaOpen();
    Drivers_gpmcOpen();


}

void Drivers_close(void)
{


    Drivers_udmaClose();
    Drivers_gpmcClose();
    Drivers_uartClose();

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

/*
 * GPMC
 */
/* GPMC Driver handles */
GPMC_Handle gGpmcHandle[CONFIG_GPMC_NUM_INSTANCES];

/* GPMC Driver Parameters */
GPMC_Params gGpmcParams[CONFIG_GPMC_NUM_INSTANCES] =
{
    {
        .gpmcDmaChIndex = 0,
        .devType                =   CSL_GPMC_CONFIG1_DEVICETYPE_NANDLIKE,
        .devSize                =   CSL_GPMC_CONFIG1_DEVICESIZE_EIGHTBITS,
        .chipSel                =   GPMC_CHIP_SELECT_CS0,
        .intrEnable             =   FALSE,
        .dmaEnable              =   TRUE,
        .transferMode           =   GPMC_TRANSFER_MODE_BLOCKING,
        .transferCallBckFunc    =   NULL,
    },
};

void Drivers_gpmcOpen(void)
{
    uint32_t instCnt;
    int32_t  status = SystemP_SUCCESS;

    for(instCnt = 0U; instCnt < CONFIG_GPMC_NUM_INSTANCES; instCnt++)
    {
        gGpmcHandle[instCnt] = NULL;   /* Init to NULL so that we can exit gracefully */
    }

    /* Open all instances */
    for(instCnt = 0U; instCnt < CONFIG_GPMC_NUM_INSTANCES; instCnt++)
    {
        gGpmcHandle[instCnt] = GPMC_open(instCnt, &gGpmcParams[instCnt]);
        if(NULL == gGpmcHandle[instCnt])
        {
            DebugP_logError("GPMC open failed for instance %d !!!\r\n", instCnt);
            status = SystemP_FAILURE;
            break;
        }
    }

    if(SystemP_FAILURE == status)
    {
        Drivers_gpmcClose();   /* Exit gracefully */
    }

    return;
}

void Drivers_gpmcClose(void)
{
    uint32_t instCnt;

    /* Close all instances that are open */
    for(instCnt = 0U; instCnt < CONFIG_GPMC_NUM_INSTANCES; instCnt++)
    {
        if(gGpmcHandle[instCnt] != NULL)
        {
            GPMC_close(gGpmcHandle[instCnt]);
            gGpmcHandle[instCnt] = NULL;
        }
    }

    return;
}


/*
 * UART
 */

/* UART Driver handles */
UART_Handle gUartHandle[CONFIG_UART_NUM_INSTANCES];

/* UART Driver Parameters */
UART_Params gUartParams[CONFIG_UART_NUM_INSTANCES] =
{
    {
        .baudRate           = 115200,
        .dataLength         = UART_LEN_8,
        .stopBits           = UART_STOPBITS_1,
        .parityType         = UART_PARITY_NONE,
        .readMode           = UART_TRANSFER_MODE_BLOCKING,
        .readReturnMode     = UART_READ_RETURN_MODE_FULL,
        .writeMode          = UART_TRANSFER_MODE_BLOCKING,
        .readCallbackFxn    = NULL,
        .writeCallbackFxn   = NULL,
        .hwFlowControl      = FALSE,
        .hwFlowControlThr   = UART_RXTRIGLVL_16,
        .transferMode       = UART_CONFIG_MODE_POLLED,
        .skipIntrReg        = FALSE,
        .uartDmaIndex = -1,
        .intrNum            = 210U,
        .intrPriority       = 4U,
        .operMode           = UART_OPER_MODE_16X,
        .rxTrigLvl          = UART_RXTRIGLVL_8,
        .txTrigLvl          = UART_TXTRIGLVL_32,
        .rxEvtNum           = 0U,
        .txEvtNum           = 0U,
    },
};

void Drivers_uartOpen(void)
{
    uint32_t instCnt;
    int32_t  status = SystemP_SUCCESS;

    for(instCnt = 0U; instCnt < CONFIG_UART_NUM_INSTANCES; instCnt++)
    {
        gUartHandle[instCnt] = NULL;   /* Init to NULL so that we can exit gracefully */
    }

    /* Open all instances */
    for(instCnt = 0U; instCnt < CONFIG_UART_NUM_INSTANCES; instCnt++)
    {
        gUartHandle[instCnt] = UART_open(instCnt, &gUartParams[instCnt]);
        if(NULL == gUartHandle[instCnt])
        {
            DebugP_logError("UART open failed for instance %d !!!\r\n", instCnt);
            status = SystemP_FAILURE;
            break;
        }
    }

    if(SystemP_FAILURE == status)
    {
        Drivers_uartClose();   /* Exit gracefully */
    }

    return;
}

void Drivers_uartClose(void)
{
    uint32_t instCnt;

    /* Close all instances that are open */
    for(instCnt = 0U; instCnt < CONFIG_UART_NUM_INSTANCES; instCnt++)
    {

        if(gUartHandle[instCnt] != NULL)
        {
            UART_Config        *config;
            config = (UART_Config *)gUartHandle[instCnt];

            if(config->traceInstance != TRUE)
            {
                UART_close(gUartHandle[instCnt]);
                gUartHandle[instCnt] = NULL;
            }

        }
    }

    return;
}
