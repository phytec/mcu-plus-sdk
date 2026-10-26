*** Comments ***
SBL r5fss0-0_nortos TEST FILE

*** Settings ***
Documentation    Suite for SBL r5fss0-0_nortos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${CFG_FILE}    ${SDK_PATH}/tools/boot/sbl_prebuilt/am62x-sk-lp/default_sbl_gpmc_nand_linux_${DEVICE_TYPE}.cfg

*** Test Cases ***
Bootloader: SBL GPMC NAND Linux
	[Tags]    board:am62x-sk-lp    core:r5fss0-0_nortos    component:SBL    app_name:sbl_gpmc_nand_linux_multistage    SITSW-2707
	[Timeout]    900
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	UartUniFlash.WITH CFG    ${USB0}    ${UartUniFlashPath}    ${CFG_FILE}
	CHANGE BOOT MODE    ${GPMC_NAND_BOOT_MODE}
	DUT OFF
	DUT ON
