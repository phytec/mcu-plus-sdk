*** Comments ***
DDR r5fss0-0_freertos TEST FILE

*** Settings ***
Documentation    Suite for DDR r5fss0-0_freertos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${SOC}    am62x
${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${SBL}    sbl_prebuilt/am62x-sip-sk/sbl_uart.release.${DEVICE_TYPE}.tiimage
${APP_BINARY}    ../../examples/drivers/ddr/ddr_perf/am62x-sip-sk/r5fss0-0_freertos/ti-arm-clang/ddr_perf_app.release.appimage.${DEVICE_TYPE}

*** Test Cases ***
Utility: DDR load measurement
	[Tags]    board:am62x-sip-sk    core:r5fss0-0_freertos    component:DDR    app_name:ddr_perf_app    SITSW-3722
	[Timeout]    1400
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	DUTUSB0.EXPECT STRING AT UART PORT    CCC
	UartBootloader.WITH ARGS    ${USB0}    ${UartBootloaderPath}    --soc=${SOC} --bootloader=${SBL} --file=${APP_BINARY}
	DUTUSB2.CONNECT TO UART PORT    ${USB2}
	DUTUSB2.EXPECT STRING AT UART PORT    All tests have passed     800
