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
${CFG_FILE}    ${SDK_PATH}/tools/boot/sbl_prebuilt/am62x-sk/default_sbl_emmc_linux_${DEVICE_TYPE}.cfg

*** Test Cases ***
Bootloader: SBL EMMC Linux - Memtester Stress
	[Tags]    board:am62x-sk    core:r5fss0-0_nortos    component:SBL    app_name:sbl_emmc_linux_multistage(memtester)    SITSW-5565
	[Timeout]    36000
	DUT ON
	CHANGE BOOT MODE    ${UART_BOOT_MODE}
	DUT OFF
	DUT ON
	Sleep    2s
	UartUniFlash.WITH CFG    ${USB0}    ${UartUniFlashPath}    ${CFG_FILE}
	DUTUSB0.CONNECT TO UART PORT    ${USB0}
	CHANGE BOOT MODE    ${EMMC_BOOT_MODE}
	DUT OFF
	DUT ON
	NFS.SETUP NFS USING UBOOT AND BOOT    USB0
	DUTUSB0.EXPECT STRING AT UART PORT    login:    300
	DUTUSB0.SEND COMMAND AND VERIFY    root    root@    300
	DUTUSB0.SEND COMMAND AND VERIFY    memtester 500M 10    Done.    27000
