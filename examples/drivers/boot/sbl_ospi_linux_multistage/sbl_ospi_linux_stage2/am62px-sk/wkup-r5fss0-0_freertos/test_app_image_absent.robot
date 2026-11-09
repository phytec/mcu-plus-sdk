*** Comments ***
SBL wkup-r5fss0-0_freertos TEST FILE

*** Settings ***
Documentation    Suite for SBL wkup-r5fss0-0_freertos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${CFG_FILE}    ${SDK_PATH}/test/drivers/boot/sbl_core_appImage_not_present/am62px-sk/default_sbl_ospi_core_appImage_not_present_${DEVICE_TYPE}.cfg

*** Test Cases ***
Bootloader: AM62P SBL Core AppImage Absent
	[Tags]    core:wkup-r5fss0-0_freertos    component:SBL    app_name:sbl_ospi_linux_multistage(app_image_absent)    SITSW-5058
	[Timeout]    900
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	UartUniFlash.WITH CFG    ${USB0}    ${UartUniFlashPath}    ${CFG_FILE}
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	CHANGE BOOT MODE    ${OSPI_NOR_BOOT_MODE}
	DUT OFF
	DUT ON
	DUTUSB0.EXPECT STRING AT UART PORT    Starting 2nd stage bootloader    300
	DUTUSB0.EXPECT STRING AT UART PORT    Starting linux and RTOS/Baremetal application    300
	DUTUSB0.EXPECT STRING AT UART PORT    switch to partitions #0, OK    300
