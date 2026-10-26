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

#include "ti_board_open_close.h"


int32_t Board_driversOpen(void)
{
    int32_t status = SystemP_SUCCESS;
    if(status==SystemP_SUCCESS)
    {
        status = Board_flashOpen();
    }
    return status;
}

void Board_driversClose(void)
{
    Board_flashClose();
}


/*
 * FLASH
 */
uint8_t gNandDataScratchMem[4096] __attribute__((aligned(128)));
uint8_t gNandEccScratchMem[256];

/* FLASH Object - initialized during Flash_open() */
Flash_NandGpmcObject gFlashObject_MT29F8G08ADAFAH4 =
{
    .gpmcHandle = NULL,
    {
    .eccAlgo = GPMC_NAND_ECC_ALGO_BCH_8BIT,
    },
    .dataMemScratch = gNandDataScratchMem,
    .eccMemScratch = gNandEccScratchMem,
};

/* FLASH Attrs */
Flash_Attrs gFlashAttrs_MT29F8G08ADAFAH4 =
{
    .flashType = CONFIG_FLASH_TYPE_PARALLEL,
    .flashName = "MT29F8G08ADAFAH4",
    .deviceId = 0xD3D0,
    .manufacturerId = 0x2C,
    .flashSize = 1073741824,
    .blockCount = 4096,
    .blockSize = 262144,
    .pageCount = 64,
    .pageSize = 4096,
    .spareAreaSize = 256,
};

/* FLASH DevConfig */
Flash_DevConfig gFlashDevCfg_MT29F8G08ADAFAH4 =
{
    .idCfg = {
        .cmd =0x90,
        .numBytes = 3,
    },
    .eraseCfg = {
        .cmdBlockErase = 0x60,
        .cmdBlockEraseCyc2 = 0xD0,
        .blockSize =  262144,
    },
    .cmdPageLoadCyc1 = 0x00,
    .cmdPageLoadCyc2 = 0x30,
    .cmdRandomReadCyc1 = 0x05,
    .cmdRandomReadCyc2 = 0xE0,
    .cmdRandomInput  = 0x85,
    .cmdPageProgCyc1 = 0x80,
    .cmdPageProgCyc2 = 0x10,
    .pageColAddrCyc = 0x02,
    .pageRowAddrCyc = 0x03,
    .cmdReadStatus = 0x70,
    .cmdReset = 0xFF,
};




/* FLASH Driver handles - opened during Board_flashOpen() */
Flash_Handle gFlashHandle[CONFIG_FLASH_NUM_INSTANCES];

/* FLASH Config */
Flash_Config gFlashConfig[CONFIG_FLASH_NUM_INSTANCES] =
{
    {
        .attrs = &gFlashAttrs_MT29F8G08ADAFAH4,
        .fxns = &gFlashNandGpmcFxns,
        .devConfig = &gFlashDevCfg_MT29F8G08ADAFAH4,
        .object = (void *)&gFlashObject_MT29F8G08ADAFAH4,
        .fallBackCfg = NULL,
        .layoutCfg = NULL,
    },
};

/* FLASH Open Params - populated from SysConfig options */
Flash_Params gFlashParams[CONFIG_FLASH_NUM_INSTANCES] =
{
    {

        .quirksFxn = NULL,
        .custProtoFxn = NULL,
    },
};

uint32_t gFlashConfigNum = CONFIG_FLASH_NUM_INSTANCES;


int32_t Board_flashOpen()
{
    uint32_t instCnt;
    int32_t  status = SystemP_SUCCESS;

    for(instCnt = 0U; instCnt < CONFIG_FLASH_NUM_INSTANCES; instCnt++)
    {
        gFlashHandle[instCnt] = NULL;   /* Init to NULL so that we can exit gracefully */
    }

    /* Set the underlying driver instance to the FLASH config */
    gFlashAttrs_MT29F8G08ADAFAH4.driverInstance = CONFIG_GPMC0;

    /* Open all instances */
    for(instCnt = 0U; instCnt < CONFIG_FLASH_NUM_INSTANCES; instCnt++)
    {
        gFlashHandle[instCnt] = Flash_open(instCnt, &gFlashParams[instCnt]);
        if(NULL == gFlashHandle[instCnt])
        {
            DebugP_logError("FLASH open failed for instance %d !!!\r\n", instCnt);
            status = SystemP_FAILURE;
            break;
        }
    }

    if(SystemP_FAILURE == status)
    {
        Board_flashClose();   /* Exit gracefully */
    }
    return status;
}

void Board_flashClose(void)
{
    uint32_t instCnt;

    /* Close all instances that are open */
    for(instCnt = 0U; instCnt < CONFIG_FLASH_NUM_INSTANCES; instCnt++)
    {
            if(gFlashHandle[instCnt] != NULL)
            {
                Flash_close(gFlashHandle[instCnt]);
                gFlashHandle[instCnt] = NULL;
            }
    }
    return;
}

