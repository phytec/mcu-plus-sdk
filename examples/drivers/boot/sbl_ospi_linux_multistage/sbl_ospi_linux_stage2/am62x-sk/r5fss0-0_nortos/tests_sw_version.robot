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
${CFG_FILE}    ${SDK_PATH}/test/drivers/boot/sbl_sw_version_test/am62x-sk/default_sbl_ospi_sw_version_test_${DEVICE_TYPE}.cfg

*** Test Cases ***
Bootloader Check appImage sw version
	[Tags]    board:am62x-sk    core:r5fss0-0_nortos    component:SBL    app_name:sbl_ospi_linux_multistage(sw_version_check)    SITSW-5111
	[Timeout]    660
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	UartUniFlash.WITH CFG    ${USB0}    ${UartUniFlashPath}    ${CFG_FILE}
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	CHANGE BOOT MODE    ${OSPI_NOR_BOOT_MODE}
	DUT OFF
	DUT ON
	DUTUSB0.EXPECT STRING AT UART PORT    Some tests have failed    200
