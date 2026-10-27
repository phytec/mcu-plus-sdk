
let common = system.getScript("/common");

let pru_icss_config = [
    {
        name            : "ICSSG0",
        mdioBaseAddr    : "CSL_PRU_ICSSG0_PR1_MDIO_V1P7_MDIO_BASE",
        clockIds        : [ "TISCI_DEV_PRU_ICSSG0" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_PRU_ICSSG0",
                clkId   : "TISCI_DEV_PRU_ICSSG0_CORE_CLK",
                clkRate : 200000000,
                clkParentId: "TISCI_DEV_PRU_ICSSG0_CORE_CLK_PARENT_HSDIV4_16FFT_MAIN_2_HSDIVOUT0_CLK",
                used : 0,
            },
            {
                moduleId: "TISCI_DEV_PRU_ICSSG0",
                clkId   : "TISCI_DEV_PRU_ICSSG0_UCLK_CLK",
                clkRate : 192000000,
            },
            {
                moduleId: "TISCI_DEV_PRU_ICSSG0",
                clkId   : "TISCI_DEV_PRU_ICSSG0_IEP_CLK",
                clkRate : 200000000,
                clkParentId: "TISCI_DEV_PRU_ICSSG0_IEP_CLK_PARENT_POSTDIV4_16FF_MAIN_0_HSDIVOUT6_CLK",
                used    : 0,
            },
        ],
    },
    {
        name            : "ICSSG1",
        mdioBaseAddr    : "CSL_PRU_ICSSG1_PR1_MDIO_V1P7_MDIO_BASE",
        clockIds        : [ "TISCI_DEV_PRU_ICSSG1" ],
        clockFrequencies: [
            {
                moduleId: "TISCI_DEV_PRU_ICSSG1",
                clkId   : "TISCI_DEV_PRU_ICSSG1_CORE_CLK",
                clkRate : 200000000,
                clkParentId: "TISCI_DEV_PRU_ICSSG0_CORE_CLK_PARENT_HSDIV4_16FFT_MAIN_2_HSDIVOUT0_CLK",
                used : 0,
            },
            {
                moduleId: "TISCI_DEV_PRU_ICSSG1",
                clkId   : "TISCI_DEV_PRU_ICSSG1_UCLK_CLK",
                clkRate : 192000000,
            },
            {
                moduleId: "TISCI_DEV_PRU_ICSSG1",
                clkId   : "TISCI_DEV_PRU_ICSSG1_IEP_CLK",
                clkRate : 200000000,
                clkParentId: "TISCI_DEV_PRU_ICSSG0_IEP_CLK_PARENT_POSTDIV4_16FF_MAIN_0_HSDIVOUT6_CLK",
                used    : 0,
            },
        ],
    },
    /*
    * Shared Clock Parent Macros for ICSSG Validation
    * 
    * These macros are intentionally reused for both ICSSG0 and ICSSG1 within the
    * PossibleClkParentId array. This design allows the validation function to 
    * recognize that both ICSSG instances can use the same set of PLL dividers
    * as clock sources.
    * 
    * Although the TISCI device IDs differ between instances:
    * - TISCI_DEV_PRU_ICSSG0_CORE_CLK_PARENT_HSDIV4_16FFT_MAIN_2_HSDIVOUT0_CLK
    * - TISCI_DEV_PRU_ICSSG1_CORE_CLK_PARENT_HSDIV4_16FFT_MAIN_2_HSDIVOUT0_CLK
    * 
    * Their enumerated values are identical, enabling shared validation logic
    * for clock parent selection across both ICSSG blocks.
    */
    {
        "coreClockParentIdCombinations" : {
            PossibleClkParentId : ["TISCI_DEV_PRU_ICSSG0_CORE_CLK_PARENT_HSDIV4_16FFT_MAIN_2_HSDIVOUT0_CLK", "TISCI_DEV_PRU_ICSSG0_CORE_CLK_PARENT_POSTDIV4_16FF_MAIN_0_HSDIVOUT9_CLK"],
            PossibleClkRate :[[200*1000000, 225*1000000, 300*1000000],[200*1000000, 250*1000000, 333333333]]
        },
        "iepClockParentIdCombinations" : {
            PossibleClkParentId : ["TISCI_DEV_PRU_ICSSG0_IEP_CLK_PARENT_POSTDIV4_16FF_MAIN_2_HSDIVOUT5_CLK", "TISCI_DEV_PRU_ICSSG0_IEP_CLK_PARENT_POSTDIV4_16FF_MAIN_0_HSDIVOUT6_CLK", "TISCI_DEV_PRU_ICSSG0_IEP_CLK_PARENT_K3_PLL_CTRL_WRAP_MAIN_0_CHIP_DIV1_CLK_CLK"],
            PossibleClkRate :[[225*1000000, 300*1000000], [200*1000000, 250*1000000, 333333333], [500*1000000]]
        }
    }
];

function getConfigArr() {

    return pru_icss_config;
}

exports = {
    getConfigArr,
};