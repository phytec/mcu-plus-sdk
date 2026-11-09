*** Comments ***
DSS wkup-r5fss0-0_freertos TEST FILE

*** Settings ***
Documentation    Suite for DSS wkup-r5fss0-0_freertos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${SOC}    am62px
${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${SBL}    sbl_prebuilt/am62px-sk/sbl_uart.release.${DEVICE_TYPE}.tiimage
${APP_BINARY}    ../../examples/drivers/dss/dss_display_test/am62px-sk/wkup-r5fss0-0_freertos/ti-arm-clang/dss_display_test.release.appimage.${DEVICE_TYPE}

*** Test Cases ***
dss_display_test application
	[Tags]    core:wkup-r5fss0-0_freertos    component:DSS    app_name:dss_display_test    SITSW-6080
	[Timeout]    620
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	DUTUSB0.EXPECT STRING AT UART PORT    CCC
	UartBootloader.WITH ARGS    ${USB0}    ${UartBootloaderPath}    --soc=${SOC} --bootloader=${SBL} --file=${APP_BINARY}
	DUTUSB2.CONNECT TO UART PORT    ${USB2}
	DUTUSB2.EXPECT STRING AT UART PORT    DSS display test Passed!!     30
