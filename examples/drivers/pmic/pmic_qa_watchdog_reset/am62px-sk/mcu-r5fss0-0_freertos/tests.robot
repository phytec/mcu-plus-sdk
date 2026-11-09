*** Comments ***
PMIC mcu-r5fss0-0_freertos TEST FILE

*** Settings ***
Documentation    Suite for PMIC mcu-r5fss0-0_freertos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${CFG_FILE}    ${SDK_PATH}/examples/drivers/pmic/pmic_qa_watchdog_reset/am62px-sk/default_pmic_qa_watchdog_reset_${DEVICE_TYPE}.cfg

*** Test Cases ***
PMIC: Q&A watchdog reset mode example
	[Tags]    core:mcu-r5fss0-0_freertos    component:PMIC    app_name:pmic_qa_watchdog_reset    SITSW-4633
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
