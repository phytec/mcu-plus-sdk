*** Comments ***
MCAN m4fss0-0_freertos TEST FILE

*** Settings ***
Documentation    Suite for MCAN m4fss0-0_freertos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${SOC}    am62x
${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${SBL}    sbl_prebuilt/am62x-sk-lp/sbl_uart.release.${DEVICE_TYPE}.tiimage
${APP_BINARY}    ../../examples/drivers/mcan/mcan_loopback_polling/am62x-sk-lp/m4fss0-0_freertos/ti-arm-clang/mcan_loopback_polling.release.appimage.${DEVICE_TYPE}
${DM_BINARY}    ../../examples/hello_world/am62x-sk-lp/r5fss0-0_freertos/ti-arm-clang/hello_world.release.appimage.${DEVICE_TYPE}

*** Test Cases ***
MCAN Internal Loopback Sample Application Polling Mode
	[Tags]    board:am62x-sk-lp    core:m4fss0-0_freertos    component:MCAN    app_name:mcan_loopback_polling    SITSW-1302
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
	DUTUSB3.EXPECT STRING AT UART PORT    All tests have passed     30
