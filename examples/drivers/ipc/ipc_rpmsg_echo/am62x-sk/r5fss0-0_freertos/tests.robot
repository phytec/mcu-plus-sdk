*** Comments ***
IPC r5fss0-0_freertos TEST FILE

*** Settings ***
Documentation    Suite for IPC r5fss0-0_freertos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${SOC}    am62x
${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${CFG_FILE}    ${SDK_PATH}/examples/drivers/ipc/ipc_rpmsg_echo/am62x-sk/ipc_rpmsg_echo_sbl_uart_${DEVICE_TYPE}.cfg

*** Test Cases ***
IPC RpMsg Sample Application
	[Tags]    board:am62x-sk    core:r5fss0-0_freertos    component:IPC    app_name:ipc_rpmsg_echo    SITSW-1889
	[Timeout]    630
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	DUTUSB0.EXPECT STRING AT UART PORT    CCC
	UartBootloader.WITH CFG    ${USB0}    ${UartBootloaderPath}    ${CFG_FILE}
	DUTUSB2.CONNECT TO UART PORT    ${USB2}
	DUTUSB2.EXPECT STRING AT UART PORT    All tests have passed     30
