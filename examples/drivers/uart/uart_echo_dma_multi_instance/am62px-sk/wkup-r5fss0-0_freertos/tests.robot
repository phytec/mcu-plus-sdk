*** Comments ***
UART wkup-r5fss0-0_freertos TEST FILE

*** Settings ***
Documentation    Suite for UART wkup-r5fss0-0_freertos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${SOC}    am62px
${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${SBL}    sbl_prebuilt/am62px-sk/sbl_uart.release.${DEVICE_TYPE}.tiimage
${APP_BINARY}    ../../examples/drivers/uart/uart_echo_dma_multi_instance/am62px-sk/wkup-r5fss0-0_freertos/ti-arm-clang/UART_echoDma_multiInstance.release.appimage.${DEVICE_TYPE}

*** Test Cases ***
UART Echo DMA Multi Instance Mode Sample Application
	[Tags]    core:wkup-r5fss0-0_freertos    component:UART    app_name:UART_echoDma_multiInstance    SITSW-8008
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
	DUTUSB1.CONNECT TO UART PORT    ${USB1}
	DUTUSB2.EXPECT STRING AT UART PORT    Receives 8 characters then echo's back. Please input..    20
	DUTUSB2.SEND COMMAND AND VERIFY    12345678\r\n
	DUTUSB1.SEND COMMAND AND VERIFY    12345678\r\n
	DUTUSB2.EXPECT STRING AT UART PORT    All tests have passed     30
