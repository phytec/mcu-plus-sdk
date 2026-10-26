*** Comments ***
UART a53ss0-0_freertos TEST FILE

*** Settings ***
Documentation    Suite for UART a53ss0-0_freertos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${SOC}    am62x
${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${SBL}    sbl_prebuilt/am62x-sip-sk/sbl_uart.release.${DEVICE_TYPE}.tiimage
${APP_BINARY}    ../../examples/drivers/uart/uart_echo_callback/am62x-sip-sk/a53ss0-0_freertos/gcc-aarch64/uart_echo_callback.release.appimage.${DEVICE_TYPE}
${DM_BINARY}    ../../examples/hello_world/am62x-sip-sk/r5fss0-0_freertos/ti-arm-clang/hello_world.release.appimage.${DEVICE_TYPE}

*** Test Cases ***
UART Echo Non-Blocking Sample Application
	[Tags]    board:am62x-sip-sk    core:a53ss0-0_freertos    component:UART    app_name:uart_echo_callback    SITSW-1307
	[Timeout]    630
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	DUTUSB0.EXPECT STRING AT UART PORT    CCC
	UartBootloader.WITH ARGS    ${USB0}    ${UartBootloaderPath}    --bootloader=${SBL} --file=${APP_BINARY} --file=${DM_BINARY}
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	DUTUSB0.EXPECT STRING AT UART PORT    Receives 8 characters then echo's back. Please input..    20
	DUTUSB0.SEND COMMAND AND VERIFY    12345678
	DUTUSB0.EXPECT STRING AT UART PORT    All tests have passed     60
