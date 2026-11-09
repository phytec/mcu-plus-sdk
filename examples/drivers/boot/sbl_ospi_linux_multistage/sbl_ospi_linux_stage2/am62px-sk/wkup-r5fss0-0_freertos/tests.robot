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
${CFG_FILE}    ${SDK_PATH}/examples/drivers/boot/sbl_ospi_linux_multistage/sbl_ospi_linux_stage2/am62px-sk/wkup-r5fss0-0_freertos/sbl_ospi_linux_${DEVICE_TYPE}.cfg

*** Test Cases ***
Bootloader: SBL OSPI NOR Linux
	[Tags]    core:wkup-r5fss0-0_freertos    component:SBL    app_name:sbl_ospi_linux_multistage    SITSW-1632
	[Timeout]    1200
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	UartUniFlash.WITH CFG    ${USB0}    ${UartUniFlashPath}    ${CFG_FILE}
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	DUTUSB2.CONNECT TO UART PORT    ${USB2}
	DUTUSB3.CONNECT TO UART PORT    ${USB3}
	CHANGE BOOT MODE    ${OSPI_NOR_BOOT_MODE}
	DUT OFF
	DUT ON
	NFS.SETUP NFS USING UBOOT AND BOOT    USB0
	DUTUSB0.EXPECT STRING AT UART PORT    Arago Project    300
	DUTUSB0.SEND COMMAND AND VERIFY    \n    login:    300
	DUTUSB0.SEND COMMAND AND VERIFY    root    root@    300
	DUTUSB2.EXPECT STRING AT UART PORT    Starting Sciserver..... PASSED    300
	DUTUSB3.EXPECT STRING AT UART PORT    Remote Core waiting for messages at end point    300
