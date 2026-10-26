*** Comments ***
UART m4fss0-0_nortos TEST FILE

*** Settings ***
Documentation    Suite for UART m4fss0-0_nortos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${SOC}    am62x
${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${SBL}    sbl_prebuilt/am62x-sk/sbl_uart.release.${DEVICE_TYPE}.tiimage
${APP_BINARY}    ../../examples/drivers/uart/uart_echo_low_latency_interrupt/am62x-sk/m4fss0-0_nortos/ti-arm-clang/uart_echo_low_latency_interrupt.release.appimage.${DEVICE_TYPE}
${DM_BINARY}    ../../examples/hello_world/am62x-sk/r5fss0-0_freertos/ti-arm-clang/hello_world.release.appimage.${DEVICE_TYPE}

*** Test Cases ***
UART Low Latency Sample Application Interrupt
	[Tags]    board:am62x-sk    core:m4fss0-0_nortos    component:UART    app_name:uart_echo_low_latency_interrupt    SITSW-1308
	[Timeout]    630
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	DUTUSB0.EXPECT STRING AT UART PORT    CCC
	UartBootloader.WITH ARGS    ${USB0}    ${UartBootloaderPath}    --bootloader=${SBL} --file=${APP_BINARY} --file=${DM_BINARY}
	DUTUSB3.CONNECT TO UART PORT    ${USB3}
	DUTUSB3.EXPECT STRING AT UART PORT    Receives 8 characters then echo's back and exits..    20
	DUTUSB3.SEND COMMAND AND VERIFY    1\r\n
	DUTUSB3.SEND COMMAND AND VERIFY    2\r\n
	DUTUSB3.SEND COMMAND AND VERIFY    3\r\n
	DUTUSB3.SEND COMMAND AND VERIFY    4\r\n
	DUTUSB3.SEND COMMAND AND VERIFY    5\r\n
	DUTUSB3.SEND COMMAND AND VERIFY    6\r\n
	DUTUSB3.SEND COMMAND AND VERIFY    7\r\n
	DUTUSB3.SEND COMMAND AND VERIFY    8\r\n
	DUTUSB3.EXPECT STRING AT UART PORT    All tests have passed     120
