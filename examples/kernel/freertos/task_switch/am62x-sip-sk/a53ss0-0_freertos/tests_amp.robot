*** Comments ***
AMP a53ss0-0_freertos TEST FILE

*** Settings ***
Documentation    Suite for AMP a53ss0-0_freertos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${SOC}    am62x
${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${CFG_FILE}    ${SDK_PATH}/examples/kernel/freertos/task_switch/am62x-sip-sk/task_switch_freertos-amp_sbl_uart_${DEVICE_TYPE}.cfg

*** Test Cases ***
FreeRTOS Task Switch:FreeRTOS-AMP
	[Tags]    board:am62x-sip-sk    core:a53ss0-0_freertos    component:AMP    app_name:task_switch(amp)    SITSW-5783
	[Timeout]    630
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	DUTUSB0.EXPECT STRING AT UART PORT    CCC
	UartBootloader.WITH CFG    ${USB0}    ${UartBootloaderPath}    ${CFG_FILE}
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	DUTUSB0.EXPECT STRING AT UART PORT    All tests have passed     30
