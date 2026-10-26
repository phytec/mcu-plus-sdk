*** Comments ***
Security r5fss0-0_freertos TEST FILE

*** Settings ***
Documentation    Suite for Security r5fss0-0_freertos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${SOC}    am62x
${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${CFG_FILE}    ${SDK_PATH}/examples/security/fwl_exception_log/am62x-sk/r5fss0-0_freertos/default_fwl_exception_sbl_uart_${DEVICE_TYPE}.cfg

*** Test Cases ***
Security: Combined firewall example log test
	[Tags]    board:am62x-sk    core:r5fss0-0_freertos    component:Security    app_name:fwl_exception_log    SITSW-3925
	[Timeout]    660
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	DUTUSB0.EXPECT STRING AT UART PORT    CCC
	UartBootloader.WITH CFG    ${USB0}    ${UartBootloaderPath}    ${CFG_FILE}
	DUTUSB2.CONNECT TO UART PORT    ${USB2}
	DUTUSB3.CONNECT TO UART PORT    ${USB3}
	DUTUSB2.EXPECT STRING AT UART PORT    Waiting for CMBN firewall exceptions    120
	DUTUSB3.EXPECT STRING AT UART PORT    to trigger CMBN firewall exception    120
	DUTUSB3.SEND COMMAND AND VERIFY    C    send_enter=${False}
	DUTUSB3.SEND COMMAND AND VERIFY    \r    send_enter=${False}
	DUTUSB2.EXPECT STRING AT UART PORT    All tests have passed    60
