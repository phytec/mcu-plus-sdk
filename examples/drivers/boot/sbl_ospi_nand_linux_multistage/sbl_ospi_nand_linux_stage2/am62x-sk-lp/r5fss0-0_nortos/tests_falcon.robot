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
${CFG_FILE}    ${SDK_PATH}/tools/boot/sbl_prebuilt/am62x-sk-lp/default_sbl_ospi_nand_linux_falcon_${DEVICE_TYPE}.cfg

*** Test Cases ***
Skip A53 SPL and U-boot for fastboot
	[Tags]    board:am62x-sk-lp    core:r5fss0-0_nortos    component:SBL    app_name:sbl_ospi_nand_linux_multistage(falcon_boot)    SITSW-3281
	[Timeout]    3600
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	UartUniFlash.WITH CFG    ${USB0}    ${UartUniFlashPath}    ${CFG_FILE}
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	DUTUSB2.CONNECT TO UART PORT    ${USB2}
	CHANGE BOOT MODE    ${OSPI_NAND_BOOT_MODE}
	DUT OFF
	DUT ON
	DUTUSB0.EXPECT STRING AT UART PORT    am62xx-evm login:    300
	DUTUSB2.EXPECT STRING AT UART PORT    Starting Sciserver..... PASSED    300
