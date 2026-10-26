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
${CFG_FILE}    ${SDK_PATH}/tools/boot/sbl_prebuilt/am62x-sk-lp/default_sbl_uart_linux_${DEVICE_TYPE}.cfg

*** Test Cases ***
Bootloader: UART Linux SBL
	[Tags]    board:am62x-sk-lp    core:r5fss0-0_nortos    component:SBL    app_name:sbl_uart_linux    SITSW-1758
	[Timeout]    900
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	DUTUSB0.EXPECT STRING AT UART PORT    CCC
	UartBootloader.WITH CFG    ${USB0}    ${UartBootloaderPath}    ${CFG_FILE}
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	DUTUSB2.CONNECT TO UART PORT    ${USB2}
	DUTUSB3.CONNECT TO UART PORT    ${USB3}
	NFS.SETUP NFS USING UBOOT AND BOOT    USB0
	DUTUSB0.EXPECT STRING AT UART PORT    Arago Project    300
	DUTUSB0.EXPECT STRING AT UART PORT    am62xx-lp-evm login:    300
	DUTUSB0.SEND COMMAND AND VERIFY    root    root@am62xx-lp-evm    30
	DUTUSB0.SEND COMMAND AND VERIFY    rpmsg_char_simple -r15    TEST STATUS: PASSED    30
	DUTUSB0.SEND COMMAND AND VERIFY    rpmsg_char_simple -r9    TEST STATUS: PASSED    30
	DUTUSB2.EXPECT STRING AT UART PORT    Starting Sciserver..... PASSED    30
	DUTUSB3.EXPECT STRING AT UART PORT    Remote Core waiting for messages at end point    30
