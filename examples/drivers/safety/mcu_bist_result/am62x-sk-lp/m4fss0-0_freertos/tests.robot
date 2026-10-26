*** Comments ***
SBL m4fss0-0_freertos TEST FILE

*** Settings ***
Documentation    Suite for SBL m4fss0-0_freertos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${CFG_FILE}    ${SDK_PATH}/examples/drivers/safety/mcu_bist_result/am62x-sk-lp/m4fss0-0_freertos/mcu_bist_result_${DEVICE_TYPE}.cfg

*** Test Cases ***
Test LBIST and PBIST results on MCU core after SBL started the BISTs.
	[Tags]    board:am62x-sk-lp    core:m4fss0-0_freertos    component:SBL    app_name:bist_check_result_main    SITSW-2706
	[Timeout]    700
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	UartUniFlash.WITH CFG    ${USB0}    ${UartUniFlashPath}    ${CFG_FILE}
	DUTUSB2.CONNECT TO UART PORT    ${USB2}
	DUTUSB3.CONNECT TO UART PORT    ${USB3}
	CHANGE BOOT MODE    ${OSPI_NOR_BOOT_MODE}
	DUT OFF
	DUT ON
	DUTUSB2.EXPECT STRING AT UART PORT    Starting Sciserver..... PASSED    30
	DUTUSB3.EXPECT STRING AT UART PORT    All tests have passed    30
