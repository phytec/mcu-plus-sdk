MCU_PLUS_SDK_PATH ?= $(abspath .)
include imports.mak

# Default device
DEVICE ?= am62x

# debug, release
PROFILE?=release

# yes = build fftlib/mathlib/vxlib/dsplib/audiolib/tisp and their examples
BUILD_XLIBS ?= no

# GP, HS, HS_FS
ifeq ($(DEVICE),$(filter $(DEVICE), j722s))
DEVICE_TYPE?=HS_FS
else
DEVICE_TYPE?=GP
endif

ifeq ($(DEVICE),$(filter $(DEVICE), am62x))
  SYSCFG_DEVICE = AM62x
  SYSCFG_DEVICE_VARIANT = Default
  SYSCFG_DEVICE_PACKAGE = ALW
  # default syscfg CPU to use,
  # options on am62x are m4fss0-0
  SYSCFG_CPU = m4fss0-0
endif
ifeq ($(DEVICE),$(filter $(DEVICE), am62ax))
  SYSCFG_DEVICE = AM62Ax
  SYSCFG_DEVICE_VARIANT = Default
  SYSCFG_DEVICE_PACKAGE = AMB
  # default syscfg CPU to use,
  # options on am62x are m4fss0-0
  SYSCFG_CPU = r5fss0-0
endif
ifeq ($(DEVICE),$(filter $(DEVICE), am62px))
  SYSCFG_DEVICE = AM62Px
  SYSCFG_DEVICE_VARIANT = Default
  SYSCFG_DEVICE_PACKAGE = AMH
  # default syscfg CPU to use,
  # options on am62ax are wkup-r5fss0-0, mcu-r5fss0-0
  SYSCFG_CPU = mcu-r5fss0-0
endif
ifeq ($(DEVICE),$(filter $(DEVICE), am62dx))
  SYSCFG_DEVICE = AM62Dx
  SYSCFG_DEVICE_VARIANT = AM62D24-G
  SYSCFG_DEVICE_PACKAGE = ANF
  # default syscfg CPU to use,
  # options on am62dx are mcu-r5fss0-0, r5fss0-0, c75ss0-0, a53ss0-0
  SYSCFG_CPU = mcu-r5fss0-0
endif
ifeq ($(DEVICE),$(filter $(DEVICE), am275x))
  SYSCFG_DEVICE = AM275x
  SYSCFG_DEVICE_VARIANT = AM2754
  SYSCFG_DEVICE_PACKAGE = ANJ
  # default syscfg CPU to use,
  # options on am275x are wkup-r5fss0-0, r5fss0-1, r5fss1-0, r5fss1-1, c75ss0-0, c75ss1-0
  SYSCFG_CPU = r5fss0-0
endif
ifeq ($(DEVICE),$(filter $(DEVICE), am62lx))
  SYSCFG_DEVICE = AM62L
  SYSCFG_DEVICE_VARIANT = AM62L32-G-ANB
  SYSCFG_DEVICE_PACKAGE = ANB
  # default syscfg CPU to use,
  # options on am62lx are a53ss0-0
  SYSCFG_CPU = a53ss0-0
endif
ifeq ($(DEVICE),$(filter $(DEVICE), j722s))
  SYSCFG_DEVICE = AM67
  SYSCFG_DEVICE_VARIANT = Default
  SYSCFG_DEVICE_PACKAGE = AMW
  # Default syscfg CPU to use, out of the following core options on j722s:
  # main-r5fss0-0, mcu-r5fss0-0, wkup-r5fss0-0, c75ss0-0, c75ss1-0,
  # a53ss0-0, a53ss0-1, a53ss1-0, a53ss1-1, hsm0-0
  SYSCFG_CPU = mcu-r5fss0-0
endif

all:
	$(MAKE) -C . -f makefile.$(DEVICE) all PROFILE=$(PROFILE)

clean:
	$(MAKE) -C . -f makefile.$(DEVICE) clean PROFILE=$(PROFILE)

scrub:
	$(MAKE) -C . -f makefile.$(DEVICE) scrub PROFILE=$(PROFILE)

ifeq ($(DEVICE),$(filter $(DEVICE), am62x am62ax am62dx am62px am275x))
hsm:
	$(MAKE) -C . -f makefile.$(DEVICE) hsm PROFILE=$(PROFILE)

hsm-clean:
	$(MAKE) -C . -f makefile.$(DEVICE) hsm-clean PROFILE=$(PROFILE)

hsm-scrub:
	$(MAKE) -C . -f makefile.$(DEVICE) hsm-scrub PROFILE=$(PROFILE)
endif

ifeq ($(DEVICE),$(filter $(DEVICE), am62x am62ax am62px))
linux: 
	$(MAKE) -C . -f makefile.$(DEVICE) linux PROFILE=$(PROFILE)

linux-clean: 
	$(MAKE) -C . -f makefile.$(DEVICE) linux-clean PROFILE=$(PROFILE)

linux-scrub: 
	$(MAKE) -C . -f makefile.$(DEVICE) linux-scrub PROFILE=$(PROFILE)
endif

libs:
	$(MAKE) -C . -f makefile.$(DEVICE) libs PROFILE=$(PROFILE) DEVICE_TYPE=$(DEVICE_TYPE)

libs-clean:
	$(MAKE) -C . -f makefile.$(DEVICE) libs-clean PROFILE=$(PROFILE)

libs-scrub:
	$(MAKE) -C . -f makefile.$(DEVICE) libs-scrub PROFILE=$(PROFILE)

libs-external:
	$(MAKE) -C . -f makefile.$(DEVICE) libs-external PROFILE=$(PROFILE) DEVICE_TYPE=$(DEVICE_TYPE)

libs-external-clean:
	$(MAKE) -C . -f makefile.$(DEVICE) libs-external-clean PROFILE=$(PROFILE)

libs-external-scrub:
	$(MAKE) -C . -f makefile.$(DEVICE) libs-external-scrub PROFILE=$(PROFILE)

examples:
	$(MAKE) -C . -f makefile.$(DEVICE) examples PROFILE=$(PROFILE)

examples-clean:
	$(MAKE) -C . -f makefile.$(DEVICE) examples-clean PROFILE=$(PROFILE)

examples-scrub:
	$(MAKE) -C . -f makefile.$(DEVICE) examples-scrub PROFILE=$(PROFILE)

help:
	$(MAKE) -C . -f makefile.$(DEVICE) -s help PROFILE=$(PROFILE)

sbl:
	$(MAKE) -C . -f makefile.$(DEVICE) sbl PROFILE=$(PROFILE)

sbl-hs:
	$(MAKE) -C . -f makefile.$(DEVICE) sbl-hs PROFILE=$(PROFILE)

sbl-clean:
	$(MAKE) -C . -f makefile.$(DEVICE) sbl-clean PROFILE=$(PROFILE)

sbl-scrub:
	$(MAKE) -C . -f makefile.$(DEVICE) sbl-scrub PROFILE=$(PROFILE)

syscfg-gui:
	$(SYSCFG_GUI_SCRIPT) --product $(SYSCFG_SDKPRODUCT) --device $(SYSCFG_DEVICE) --context $(SYSCFG_CPU)

devconfig:
	$(SYSCFG_GUI_SCRIPT) --product $(MCU_PLUS_SDK_PATH)/devconfig/devconfig.json --device $(SYSCFG_DEVICE) --context $(SYSCFG_CPU) --output devconfig/ $(MCU_PLUS_SDK_PATH)/devconfig/devconfig.syscfg

.PHONY: all clean scrub
.PHONY: libs libs-clean libs-scrub
.PHONY: libs-external libs-external-clean libs-external-scrub
.PHONY: examples examples-clean examples-scrub
.PHONY: help
.PHONY: sbl sbl-clean sbl-scrub
.PHONY: syscfg-gui
.PHONY: devconfig


