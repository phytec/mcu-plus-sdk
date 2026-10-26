/*
 *  Copyright (C) 2021-2026 Texas Instruments Incorporated
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
#include <drivers/pinmux.h>

static Pinmux_PerCfg_t gPinMuxMainDomainCfg[] = {

    /* GPMC0 pin config */
            /* GPMC0_CSn0 -> GPMC0_CSn0 (J18) */
    {
        PIN_GPMC0_CSN0,
        ( PIN_MODE(0) | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },
            /* GPMC0_OEn_REn -> GPMC0_OEn_REn (K21) */
    {
        PIN_GPMC0_OEN_REN,
        ( PIN_MODE(0) | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },
            /* GPMC0_WAIT0 -> GPMC0_WAIT0 (P21) */
    {
        PIN_GPMC0_WAIT0,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },
            /* GPMC0_WEn -> GPMC0_WEn (J17) */
    {
        PIN_GPMC0_WEN,
        ( PIN_MODE(0) | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },
            /* GPMC0_BE0n_CLE -> GPMC0_BE0n_CLE (K17) */
    {
        PIN_GPMC0_BE0N_CLE,
        ( PIN_MODE(0) | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },
            /* GPMC0_ADVn_ALE -> GPMC0_ADVn_ALE (K20) */
    {
        PIN_GPMC0_ADVN_ALE,
        ( PIN_MODE(0) | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },
            /* GPMC0_AD0 -> GPMC0_AD0 (K19) */
    {
        PIN_GPMC0_AD0,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },
            /* GPMC0_AD1 -> GPMC0_AD1 (L19) */
    {
        PIN_GPMC0_AD1,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },
            /* GPMC0_AD2 -> GPMC0_AD2 (L20) */
    {
        PIN_GPMC0_AD2,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },
            /* GPMC0_AD3 -> GPMC0_AD3 (L21) */
    {
        PIN_GPMC0_AD3,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },
            /* GPMC0_AD4 -> GPMC0_AD4 (M21) */
    {
        PIN_GPMC0_AD4,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },
            /* GPMC0_AD5 -> GPMC0_AD5 (L17) */
    {
        PIN_GPMC0_AD5,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },
            /* GPMC0_AD6 -> GPMC0_AD6 (L18) */
    {
        PIN_GPMC0_AD6,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },
            /* GPMC0_AD7 -> GPMC0_AD7 (M20) */
    {
        PIN_GPMC0_AD7,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },


    /* USART0 pin config */
            /* UART0_RXD -> UART0_RXD (A13) */
    {
        PIN_UART0_RXD,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },
            /* UART0_TXD -> UART0_TXD (E11) */
    {
        PIN_UART0_TXD,
        ( PIN_MODE(0) | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },


    /* USART1 pin config */
            /* UART1_RXD -> MCASP0_AFSR (D15) */
    {
        PIN_MCASP0_AFSR,
        ( PIN_MODE(2) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },
            /* UART1_TXD -> MCASP0_ACLKR (D16) */
    {
        PIN_MCASP0_ACLKR,
        ( PIN_MODE(2) | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },
            /* UART1_RTSn -> MCASP0_AXR2 (B17) */
    {
        PIN_MCASP0_AXR2,
        ( PIN_MODE(2) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },
            /* UART1_CTSn -> MCASP0_AXR3 (B18) */
    {
        PIN_MCASP0_AXR3,
        ( PIN_MODE(2) | PIN_PULL_DISABLE | PIN_DRV_STR_NOMINAL )
    },

    {PINMUX_END, 0U}
};

static Pinmux_PerCfg_t gPinMuxMcuDomainCfg[] = {






    {PINMUX_END, 0U}
};

/*
 * Pinmux
 */
void Pinmux_init(void)
{
    SOC_fixFastDriveStrength();
    Pinmux_config(gPinMuxMainDomainCfg, PINMUX_DOMAIN_ID_MAIN);
    Pinmux_config(gPinMuxMcuDomainCfg, PINMUX_DOMAIN_ID_MCU);
}

