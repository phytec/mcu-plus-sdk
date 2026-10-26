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
${APP_BINARY}    ../../examples/drivers/uart/uart_echo/am62x-sk/m4fss0-0_nortos/ti-arm-clang/uart_echo.release.appimage.${DEVICE_TYPE}
${DM_BINARY}    ../../examples/hello_world/am62x-sk/r5fss0-0_freertos/ti-arm-clang/hello_world.release.appimage.${DEVICE_TYPE}

*** Test Cases ***
UART Echo Sample Application
	[Tags]    board:am62x-sk    core:m4fss0-0_nortos    component:UART    app_name:uart_echo    SITSW-1306
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
	DUTUSB3.EXPECT STRING AT UART PORT    Receives 8 characters then echo's back. Please input..    20
	DUTUSB3.SEND COMMAND AND VERIFY    12345678
	DUTUSB3.EXPECT STRING AT UART PORT    All tests have passed     120
