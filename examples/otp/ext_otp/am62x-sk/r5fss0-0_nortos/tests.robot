*** Comments ***
Security r5fss0-0_nortos TEST FILE

*** Settings ***
Documentation    Suite for Security r5fss0-0_nortos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${CFG_FILE}    ${SDK_PATH}/examples/otp/ext_otp/am62x-sk/r5fss0-0_nortos/default_ext_otp_${DEVICE_TYPE}.cfg

*** Test Cases ***
ext OTP writer for USB VID/PID
	[Tags]    board:am62x-sk    core:r5fss0-0_nortos    component:Security    app_name:ext_otp    SITSW-2167
	[Timeout]    1000
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	UartUniFlash.WITH CFG    ${USB0}    ${UartUniFlashPath}    ${CFG_FILE}
	DUTUSB2.CONNECT TO UART PORT    ${USB2}
	CHANGE BOOT MODE    ${OSPI_NOR_BOOT_MODE}
	DUT OFF
	DUT ON
	DUTUSB2.EXPECT STRING AT UART PORT    All tests have passed    60
