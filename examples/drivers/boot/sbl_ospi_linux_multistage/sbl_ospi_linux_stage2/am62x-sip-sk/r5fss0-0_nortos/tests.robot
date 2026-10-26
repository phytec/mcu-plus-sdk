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
${CFG_FILE}    ${SDK_PATH}/tools/boot/sbl_prebuilt/am62x-sip-sk/default_sbl_ospi_linux_${DEVICE_TYPE}.cfg

*** Test Cases ***
Bootloader: SBL OSPI NOR Linux
	[Tags]    board:am62x-sip-sk    core:r5fss0-0_nortos    component:SBL    app_name:sbl_ospi_linux_stage2    SITSW-1632
	[Timeout]    900
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
	NFS.SETUP NFS USING UBOOT AND BOOT    USB0
	DUTUSB0.EXPECT STRING AT UART PORT    Arago Project    300
	DUTUSB0.SEND COMMAND AND VERIFY    \n    login:    300
	DUTUSB0.SEND COMMAND AND VERIFY    root    root@    300
	DUTUSB2.EXPECT STRING AT UART PORT    Starting Sciserver..... PASSED    300
