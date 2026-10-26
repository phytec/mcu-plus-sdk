*** Comments ***
DM r5fss0-0_freertos TEST FILE

*** Settings ***
Documentation    Suite for DM r5fss0-0_freertos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${CFG_FILE}    ${SDK_PATH}/source/safety_checkers/examples/pm_checkers_warm_reset/am62x-sk-lp/pm_checkers_warm_reset_sbl_null_${DEVICE_TYPE}.cfg

*** Test Cases ***
PM Warm reset Safety Checker application
	[Tags]    board:am62x-sk-lp    core:r5fss0-0_freertos    component:DM    app_name:SafetyCheckersApp_pmWarmReset    SITSW-4515
	[Timeout]    200
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	UartUniFlash.WITH CFG    ${USB0}    ${UartUniFlashPath}    ${CFG_FILE}
	DUTUSB2.CONNECT TO UART PORT    ${USB2}
	CHANGE BOOT MODE    ${OSPI_NAND_BOOT_MODE}
	DUT OFF
	DUT ON
	DUTUSB2.EXPECT STRING AT UART PORT    All tests have passed    120
