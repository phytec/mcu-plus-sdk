var BOOTFLOW_GUIDE =
[
    [ "Introduction", "BOOTFLOW_GUIDE.html#autotoc_md677", [
      [ "What Is Bootloader?", "BOOTFLOW_GUIDE.html#autotoc_md678", null ],
      [ "Multi-Stage Bootloader", "BOOTFLOW_GUIDE.html#autotoc_md679", null ],
      [ "Multi-Core Bootloading", "BOOTFLOW_GUIDE.html#autotoc_md680", null ]
    ] ],
    [ "Bootloading in MCU+SDK", "BOOTFLOW_GUIDE.html#autotoc_md681", [
      [ "ROM Boot", "BOOTFLOW_GUIDE.html#autotoc_md682", [
        [ "System Controller Firmware (SYSFW)", "BOOTFLOW_GUIDE.html#autotoc_md683", null ],
        [ "Preparing the SBL for boot", "BOOTFLOW_GUIDE.html#autotoc_md684", null ]
      ] ],
      [ "Booting MCELF application", "BOOTFLOW_GUIDE.html#BOOTFLOW_MCELF_BOOT", [
        [ "Preparing the application for boot", "BOOTFLOW_GUIDE.html#autotoc_md685", null ],
        [ "Flashing the application for boot", "BOOTFLOW_GUIDE.html#autotoc_md686", null ],
        [ "Booting the application", "BOOTFLOW_GUIDE.html#autotoc_md687", null ]
      ] ]
    ] ],
    [ "Secure Boot", "BOOTFLOW_GUIDE.html#autotoc_md688", null ],
    [ "Deep Dive into SBLs", "BOOTFLOW_GUIDE.html#autotoc_md689", [
      [ "SBL NULL", "BOOTFLOW_GUIDE.html#autotoc_md690", null ],
      [ "SBL SD", "BOOTFLOW_GUIDE.html#BOOTFLOW_SBL_SD", null ],
      [ "SBL OSPI", "BOOTFLOW_GUIDE.html#autotoc_md691", null ],
      [ "SBL OSPI MULTI-PARTITION", "BOOTFLOW_GUIDE.html#autotoc_md692", null ],
      [ "SBL UART", "BOOTFLOW_GUIDE.html#autotoc_md693", null ],
      [ "SBL PCIE", "BOOTFLOW_GUIDE.html#autotoc_md694", null ],
      [ "SBL EMMC", "BOOTFLOW_GUIDE.html#autotoc_md695", null ],
      [ "SBL OSPI LINUX", "BOOTFLOW_GUIDE.html#autotoc_md696", null ],
      [ "SBL EMMC LINUX", "BOOTFLOW_GUIDE.html#autotoc_md697", null ]
    ] ],
    [ "Additional References", "BOOTFLOW_GUIDE.html#autotoc_md698", null ],
    [ "Enabling XIP or eXecute In Place", "BOOTFLOW_XIP.html", [
      [ "Introduction", "BOOTFLOW_XIP.html#autotoc_md699", null ],
      [ "Additional References", "BOOTFLOW_XIP.html#autotoc_md700", null ],
      [ "Pre-requisites", "BOOTFLOW_XIP.html#autotoc_md701", null ],
      [ "Enable XIP for an application", "BOOTFLOW_XIP.html#autotoc_md702", [
        [ "Using linker.cmd", "BOOTFLOW_XIP.html#autotoc_md703", null ],
        [ "Using Memory Configurator", "BOOTFLOW_XIP.html#autotoc_md704", [
          [ "Moving .rodata and .text to flash", "BOOTFLOW_XIP.html#autotoc_md705", null ],
          [ "Moving cfg rodata to internal memory", "BOOTFLOW_XIP.html#autotoc_md706", null ],
          [ "Moving CIO to internal memory", "BOOTFLOW_XIP.html#autotoc_md707", null ]
        ] ]
      ] ],
      [ "Enabling secure XIP using OTFA", "BOOTFLOW_XIP.html#autotoc_md708", [
        [ "Steps enable security in XIP image,", "BOOTFLOW_XIP.html#autotoc_md709", null ]
      ] ],
      [ "Debugging XIP applications", "BOOTFLOW_XIP.html#autotoc_md710", null ]
    ] ],
    [ "Enabling XIP or eXecute In Place", "BOOTFLOW_XIP.html", [
      [ "Introduction", "BOOTFLOW_XIP.html#autotoc_md699", null ],
      [ "Additional References", "BOOTFLOW_XIP.html#autotoc_md700", null ],
      [ "Pre-requisites", "BOOTFLOW_XIP.html#autotoc_md701", null ],
      [ "Enable XIP for an application", "BOOTFLOW_XIP.html#autotoc_md702", [
        [ "Using linker.cmd", "BOOTFLOW_XIP.html#autotoc_md703", null ],
        [ "Using Memory Configurator", "BOOTFLOW_XIP.html#autotoc_md704", [
          [ "Moving .rodata and .text to flash", "BOOTFLOW_XIP.html#autotoc_md705", null ],
          [ "Moving cfg rodata to internal memory", "BOOTFLOW_XIP.html#autotoc_md706", null ],
          [ "Moving CIO to internal memory", "BOOTFLOW_XIP.html#autotoc_md707", null ]
        ] ]
      ] ],
      [ "Enabling secure XIP using OTFA", "BOOTFLOW_XIP.html#autotoc_md708", [
        [ "Steps enable security in XIP image,", "BOOTFLOW_XIP.html#autotoc_md709", null ]
      ] ],
      [ "Debugging XIP applications", "BOOTFLOW_XIP.html#autotoc_md710", null ]
    ] ],
    [ "SBL Booting Linux From OSPI", "SBL_BOOTING_LINUX_OSPI.html", [
      [ "Introduction", "SBL_BOOTING_LINUX_OSPI.html#autotoc_md730", null ],
      [ "Features Supported", "SBL_BOOTING_LINUX_OSPI.html#autotoc_md731", null ],
      [ "Features NOT Supported", "SBL_BOOTING_LINUX_OSPI.html#autotoc_md732", null ],
      [ "Bootflow for SBL booting linux from OSPI", "SBL_BOOTING_LINUX_OSPI.html#autotoc_md733", null ],
      [ "SRAM memory layout for SBL booting Linux", "SBL_BOOTING_LINUX_OSPI.html#autotoc_md734", null ],
      [ "OSPI memory layout for SBL booting Linux from OSPI", "SBL_BOOTING_LINUX_OSPI.html#autotoc_md735", null ],
      [ "SD card Partitioning", "SBL_BOOTING_LINUX_OSPI.html#autotoc_md736", null ],
      [ "See Also", "SBL_BOOTING_LINUX_OSPI.html#autotoc_md737", null ]
    ] ],
    [ "SBL Booting Linux From eMMC", "SBL_BOOTING_LINUX_EMMC.html", [
      [ "Introduction", "SBL_BOOTING_LINUX_EMMC.html#autotoc_md723", null ],
      [ "Features Supported", "SBL_BOOTING_LINUX_EMMC.html#autotoc_md724", null ],
      [ "Features NOT Supported", "SBL_BOOTING_LINUX_EMMC.html#autotoc_md725", null ],
      [ "Bootflow for SBL booting linux from eMMC", "SBL_BOOTING_LINUX_EMMC.html#autotoc_md726", null ],
      [ "SRAM memory layout for SBL booting Linux", "SBL_BOOTING_LINUX_EMMC.html#autotoc_md727", null ],
      [ "EMMC Partitioning", "SBL_BOOTING_LINUX_EMMC.html#autotoc_md728", null ],
      [ "See Also", "SBL_BOOTING_LINUX_EMMC.html#autotoc_md729", null ]
    ] ]
];