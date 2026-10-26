*** Comments ***
IPC m4fss0-0_freertos TEST FILE

*** Settings ***
Documentation    Suite for IPC m4fss0-0_freertos TESTING

# ------------- Resource Files ---------------------
Resource    test_infra.resource

# ------------- Setup and Teardown ---------------------
Test Setup    INFRA_TEST_SETUP
Test Teardown    INFRA_TEST_TEARDOWN

*** Variables ***

${DEVICE_TYPE}    ${{ 'hs' if 'hsse' in '${PLATFORM}' else 'hs_fs' }}
${CFG_FILE}    ${SDK_PATH}/tools/boot/sbl_prebuilt/am62x-sip-sk/default_sbl_emmc_linux_${DEVICE_TYPE}.cfg

*** Test Cases ***
IPC RpMsg Linux Sample Application
	[Tags]    board:am62x-sip-sk    core:m4fss0-0_freertos    component:IPC    app_name:ipc_rpmsg_echo_linux(emmc)    SITSW-1361
	[Timeout]    900
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	UartUniFlash.WITH CFG    ${USB0}    ${UartUniFlashPath}    ${CFG_FILE}
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	DUTUSB2.CONNECT TO UART PORT    ${USB2}
	CHANGE BOOT MODE    ${EMMC_BOOT_MODE}
	DUT OFF
	DUT ON
	NFS.SETUP NFS USING UBOOT AND BOOT    USB0
	DUTUSB0.EXPECT STRING AT UART PORT    Arago Project    300
	DUTUSB0.SEND COMMAND AND VERIFY    \n    login:    300
	DUTUSB0.SEND COMMAND AND VERIFY    root    root@    300
	DUTUSB0.SEND COMMAND AND VERIFY    rpmsg_char_simple -r9    TEST STATUS: PASSED    300
	DUTUSB0.SEND COMMAND AND VERIFY    rpmsg_char_simple -r15    TEST STATUS: PASSED    300
	DUTUSB2.EXPECT STRING AT UART PORT    Starting Sciserver..... PASSED    300
