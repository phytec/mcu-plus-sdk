*** Comments ***
TIFS r5fss0-0_freertos TEST FILE

*** Settings ***
Documentation    Suite for TIFS r5fss0-0_freertos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${SOC}    am62x
${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${CFG_FILE}    ${SDK_PATH}/test/security/tifs_safety_checker/am62x-sk/default_sbl_uart_${DEVICE_TYPE}.cfg

*** Test Cases ***
TIFS Safety Checker application
	[Tags]    board:am62x-sk    core:r5fss0-0_freertos    component:TIFS    app_name:SafetyCheckersApp_tifs    SITSW-4274
	[Timeout]    720
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	DUTUSB0.EXPECT STRING AT UART PORT    CCC
	UartBootloader.WITH CFG    ${USB0}    ${UartBootloaderPath}    ${CFG_FILE}
	DUTUSB2.CONNECT TO UART PORT    ${USB2}
	DUTUSB2.EXPECT STRING AT UART PORT    All tests have PASSED     120
