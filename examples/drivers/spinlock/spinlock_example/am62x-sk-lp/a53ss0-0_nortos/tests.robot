*** Comments ***
Spinlock a53ss0-0_nortos TEST FILE

*** Settings ***
Documentation    Suite for Spinlock a53ss0-0_nortos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${SOC}    am62x
${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${CFG_FILE}    ${SDK_PATH}/examples/drivers/spinlock/spinlock_example/am62x-sk-lp/spinlock_example_sbl_uart_${DEVICE_TYPE}.cfg

*** Test Cases ***
Spinlock Example application
	[Tags]    board:am62x-sk-lp    core:a53ss0-0_nortos    component:Spinlock    app_name:spinlock_example    SITSW-4836
	[Timeout]    630
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	DUTUSB0.EXPECT STRING AT UART PORT    CCC
	UartBootloader.WITH CFG    ${USB0}    ${UartBootloaderPath}    ${CFG_FILE}
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	DUTUSB0.EXPECT STRING AT UART PORT    All tests have passed     120
