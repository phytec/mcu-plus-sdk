
DEVICE ?= am62x

# Include device configuration
-include $(MCU_PLUS_SDK_PATH)/devconfig/devconfig.mak

GCC_ARCH64_VERSION=9.2-2019.12
CGT_ARMLLVM_VERSION=4.0.5.LTS
CGT_PRU_VERSION=2.3.3
SYSCONFIG_VERSION=1.26.2
SYSCONFIG_BUILD=4477
SW_VERSION=0x0C01001F
CCS_FOLDER_VERSION=2031

ifeq ($(OS),Windows_NT)
    TOOLS_PATH?=C:/ti
    CCS_PATH?=$(TOOLS_PATH)/ccs$(CCS_FOLDER_VERSION)/ccs
    CCS_ECLIPSE=$(CCS_PATH)/eclipse/eclipsec
    CYGWIN_PATH?=$(CCS_PATH)/utils/cygwin
    MKDIR=$(CYGWIN_PATH)/mkdir -p
    RMDIR=$(CYGWIN_PATH)/rm -rf
    RM=$(CYGWIN_PATH)/rm -f
    COPY=$(CYGWIN_PATH)/cp
    MOVE=$(CYGWIN_PATH)/mv
    CAT=$(CYGWIN_PATH)/cat
    SED=$(CYGWIN_PATH)/sed
    TOUCH=$(CYGWIN_PATH)/touch
    PATHSEP=\\
    CHMOD=$(CYGWIN_PATH)/echo
    SCRIPT_EXT=bat
    SHELL=cmd.exe
    CGT_GCC_AARCH64_PATH=$(TOOLS_PATH)/gcc-arm-$(GCC_ARCH64_VERSION)-mingw-w64-i686-aarch64-none-elf
    CGT_GCC_ARM_PATH=$(TOOLS_PATH)/gcc-arm-none-eabi-7-2017-q4-major-win32
    CGT_GCC_ARMV7_PATH=$(CGT_GCC_ARM_PATH)
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        export TOOLS_PATH?=$(HOME)/ti
        export CCS_PATH?=$(TOOLS_PATH)/ccs$(CCS_FOLDER_VERSION)/ccs
        export CCS_ECLIPSE=$(CCS_PATH)/eclipse/eclipse
        export MKDIR=mkdir -p
        export RMDIR=rm -rf
        export RM=rm -f
        export COPY=cp
        export MOVE=mv
        export CAT=cat
        export SED=sed
        export TOUCH=touch
        export PATHSEP=/
        export CHMOD=chmod
        export SCRIPT_EXT=sh
        CGT_GCC_AARCH64_PATH=$(TOOLS_PATH)/gcc-arm-$(GCC_ARCH64_VERSION)-x86_64-aarch64-none-elf
        CGT_GCC_ARM_PATH=$(TOOLS_PATH)/gcc-arm-none-eabi-7-2017-q4-major
        CGT_GCC_ARMV7_PATH=$(CGT_GCC_ARM_PATH)
    endif
endif

CGT_TI_PRU_PATH=$(TOOLS_PATH)/ti-cgt-pru_$(CGT_PRU_VERSION)
CGT_TI_ARM_CLANG_PATH=$(CCS_PATH)/tools/compiler/ti-cgt-armllvm_$(CGT_ARMLLVM_VERSION)
ifeq ($(wildcard $(CGT_TI_ARM_CLANG_PATH)),)
    CGT_TI_ARM_CLANG_PATH=$(TOOLS_PATH)/ti-cgt-armllvm_$(CGT_ARMLLVM_VERSION)
endif
CCS_NODE = $(CCS_PATH)/tools/node/node
SYSCFG_PATH ?= $(TOOLS_PATH)/sysconfig_$(SYSCONFIG_VERSION)
SYSCFG_CLI_PATH ?= $(SYSCFG_PATH)
SYSCFG_NODE = $(SYSCFG_PATH)/nodejs/node
SYSCFG_NWJS = $(SYSCFG_PATH)/nw/nw
SYSCFG_SDKPRODUCT=$(MCU_PLUS_SDK_PATH)/.metadata/product.json
SYSCFG_GUI_SCRIPT=$(SYSCFG_PATH)/sysconfig_gui.$(SCRIPT_EXT)
SYSCFG_TEST_FLAGS?=--excludeTests eslint

# Variable pointing to location of prebuilt industrial communication libraries
MCU_PLUS_SDK_IND_COMMS_LIBS_PATH ?= $(MCU_PLUS_SDK_PATH)/source/commercial/industrial_comms_libs

OPTISHARE = $(CCS_NODE) $(CGT_TI_ARM_CLANG_PATH)/opti-share/opti-share.js
OPTISAVE = $(CCS_NODE) $(CGT_TI_ARM_CLANG_PATH)/opti-share/utils/opti-save.js
