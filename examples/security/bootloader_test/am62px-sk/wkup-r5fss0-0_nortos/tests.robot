*** Comments ***
SBL wkup-r5fss0-0_nortos TEST FILE

*** Settings ***
Documentation    Suite for SBL wkup-r5fss0-0_nortos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${CFG_FILE}    ${SDK_PATH}/examples/security/bootloader_test/am62px-sk/default_security_bootloader_test_hs.cfg

*** Test Cases ***
Security: Bootloader test
	[Tags]    core:wkup-r5fss0-0_nortos    component:SBL    app_name:security_bootloader_test    SITSW-6011
	[Timeout]    600
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
	DUTUSB0.EXPECT STRING AT UART PORT    Image size    300
	DUTUSB0.EXPECT STRING AT UART PORT    All tests have passed!!    300
