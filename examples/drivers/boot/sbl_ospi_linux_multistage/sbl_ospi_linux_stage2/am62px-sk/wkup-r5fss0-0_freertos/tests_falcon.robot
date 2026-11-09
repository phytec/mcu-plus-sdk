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
${CFG_FILE}    ${SDK_PATH}/tools/boot/sbl_prebuilt/am62px-sk/default_sbl_ospi_linux_falcon_${DEVICE_TYPE}.cfg

*** Test Cases ***
Skip A53 SPL and U-boot for fastboot
	[Tags]    core:wkup-r5fss0-0_freertos    component:SBL    app_name:sbl_ospi_linux_multistage(falcon_boot)    SITSW-3281
	[Timeout]    1000
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	UartUniFlash.WITH CFG    ${USB0}    ${UartUniFlashPath}    ${CFG_FILE}
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	DUTUSB2.CONNECT TO UART PORT    ${USB2}
	CHANGE BOOT MODE    ${OSPI_NOR_BOOT_MODE}
	DUT OFF
	DUT ON
	DUTUSB0.EXPECT STRING AT UART PORT    login:    300
	DUTUSB2.EXPECT STRING AT UART PORT    Starting Sciserver..... PASSED    300
