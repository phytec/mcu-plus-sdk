*** Comments ***
MMCSD r5fss0-0_freertos TEST FILE

*** Settings ***
Documentation    Suite for MMCSD r5fss0-0_freertos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${SOC}    am62x
${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${SBL}    sbl_prebuilt/am62x-sip-sk/sbl_uart.release.${DEVICE_TYPE}.tiimage
${APP_BINARY}    ../../examples/drivers/mmcsd/mmcsd_raw_io/am62x-sip-sk/r5fss0-0_freertos/ti-arm-clang/mmcsd_raw_io.release.appimage.${DEVICE_TYPE}

*** Test Cases ***
MMCSD: Raw Write/Read example for eMMC
	[Tags]    board:am62x-sip-sk    core:r5fss0-0_freertos    component:MMCSD    app_name:mmcsd_raw_io    SITSW-2174
	[Timeout]    630
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	DUTUSB0.EXPECT STRING AT UART PORT    CCC
	UartBootloader.WITH ARGS    ${USB0}    ${UartBootloaderPath}    --soc=${SOC} --bootloader=${SBL} --file=${APP_BINARY}
	DUTUSB2.CONNECT TO UART PORT    ${USB2}
	DUTUSB2.EXPECT STRING AT UART PORT    All tests have passed     300
