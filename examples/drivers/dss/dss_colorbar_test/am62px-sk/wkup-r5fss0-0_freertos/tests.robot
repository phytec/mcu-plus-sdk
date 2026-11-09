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
${APP_BINARY}    ../../examples/drivers/dss/dss_colorbar_test/am62px-sk/wkup-r5fss0-0_freertos/ti-arm-clang/dss_colorbar_test.release.appimage.${DEVICE_TYPE}

*** Test Cases ***
dss_colorbar_test application
	[Tags]    core:wkup-r5fss0-0_freertos    component:DSS    app_name:dss_colorbar_test    SITSW-6066
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
	DUTUSB2.EXPECT STRING AT UART PORT    DSS colorbar test Passed!!     30
