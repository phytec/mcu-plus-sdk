*** Comments ***
SBL r5fss0-0_nortos TEST FILE

*** Settings ***
Documentation    Suite for SBL r5fss0-0_nortos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${CFG_FILE}    ${SDK_PATH}/tools/boot/sbl_prebuilt/am62x-sip-sk/default_sbl_ospi_freertos-smp_${DEVICE_TYPE}.cfg

*** Test Cases ***
Bootloader: SBL OSPI FreeRTOS-SMP
	[Tags]    board:am62x-sip-sk    core:r5fss0-0_nortos    component:SBL    app_name:sbl_ospi_stage2    SITSW-8470
	[Timeout]    720
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	UartUniFlash.WITH CFG    ${USB0}    ${UartUniFlashPath}    ${CFG_FILE}
	DUTUSB2.CONNECT TO UART PORT    ${USB2}
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	CHANGE BOOT MODE    ${OSPI_NOR_BOOT_MODE}
	DUT OFF
	DUT ON
	DUTUSB2.EXPECT STRING AT UART PORT    Hello World!    120
	DUTUSB0.EXPECT STRING AT UART PORT    All tests have passed!!    120
