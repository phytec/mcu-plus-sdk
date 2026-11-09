*** Comments ***
DM mcu-r5fss0-0_freertos TEST FILE

*** Settings ***
Documentation    Suite for DM mcu-r5fss0-0_freertos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${SOC}    am62px
${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${SBL}    sbl_prebuilt/am62px-sk/sbl_uart.release.${DEVICE_TYPE}.tiimage
${APP_BINARY}    ../../source/safety_checkers/examples/pm_checkers_app/am62px-sk/mcu-r5fss0-0_freertos/ti-arm-clang/SafetyCheckersApp_pm.release.appimage.${DEVICE_TYPE}
${DM_BINARY}    ../../examples/drivers/ipc/ipc_rpmsg_echo/am62px-sk/wkup-r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo.release.appimage.${DEVICE_TYPE}

*** Test Cases ***
PM Safety Checker application
	[Tags]    core:mcu-r5fss0-0_freertos    component:DM    app_name:SafetyCheckersApp_pm    SITSW-4513
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
	DUTUSB3.EXPECT STRING AT UART PORT    All tests have PASSED.     30
