*** Comments ***
RTC r5fss0-0_freertos TEST FILE

*** Settings ***
Documentation    Suite for RTC r5fss0-0_freertos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${CFG_FILE}    ${SDK_PATH}/examples/drivers/rtc/rtc_led_blink/am62x-sk/r5fss0-0_freertos/default_rtc_led_blink_${DEVICE_TYPE}.cfg

*** Test Cases ***
RTC Led Blink Example
	[Tags]    board:am62x-sk    core:r5fss0-0_freertos    component:RTC    app_name:rtc_led_blink    SITSW-6021
	[Timeout]    1000
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	UartUniFlash.WITH CFG    ${USB0}    ${UartUniFlashPath}    ${CFG_FILE}
	CHANGE BOOT MODE    ${OSPI_NOR_BOOT_MODE}
	DUT OFF
	DUT ON
