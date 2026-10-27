var ENET_LLD =
[
    [ "Enet LLD Introduction", "enetlld_top.html", [
      [ "Introduction", "enetlld_top.html#enetlld_intro", null ],
      [ "Application Programming Interface", "enetlld_top.html#enetlld_api_overview", [
        [ "Control path API", "enetlld_top.html#autotoc_md2992", null ],
        [ "Data path (DMA) API", "enetlld_top.html#autotoc_md2993", null ],
        [ "Life cycle of an Enet LLD based application", "enetlld_top.html#autotoc_md2994", null ]
      ] ],
      [ "Enet Peripherals", "enetlld_top.html#enetlld_enetpers", [
        [ "CPSW Peripheral", "enetlld_top.html#enetper_cpsw", null ],
        [ "ICSSG Peripheral", "enetlld_top.html#enetper_icssg", [
          [ "ICSSG Dual-MAC", "enetlld_top.html#enetper_icssg_dualmac", null ],
          [ "ICSSG Switch Mode", "enetlld_top.html#enetper_icssg_switch", null ]
        ] ]
      ] ],
      [ "Document Revision History", "enetlld_top.html#enetlld_hist", null ]
    ] ],
    [ "Enet LLD IOCTL interface", "enet_ioctl_interface.html", [
      [ "Introduction", "enet_ioctl_interface.html#enet_ioctl_intro", [
        [ "Using the IOCTL interface", "enet_ioctl_interface.html#using_enet_ioctl", null ],
        [ "Synchronous and Asynchronous IOCTLs", "enet_ioctl_interface.html#enet_async_ioctl", null ]
      ] ]
    ] ],
    [ "Ethernet PHY Link Configuration", "enetphy_link_config_top.html", [
      [ "Link Configuration Guidelines", "enetphy_link_config_top.html#enetphy_link_config_guidelines", [
        [ "Manual Mode", "enetphy_link_config_top.html#enetphy_link_manual", [
          [ "Half-Duplex Mode", "enetphy_link_config_top.html#enetphy_link_manual_half_duplex", null ],
          [ "Full-Duplex Mode", "enetphy_link_config_top.html#enetphy_link_manual_full_duplex", null ]
        ] ],
        [ "Auto-Negotiation Mode", "enetphy_link_config_top.html#enetphy_link_autoneg", null ],
        [ "Strapping", "enetphy_link_config_top.html#enetphy_link_strapping", null ]
      ] ]
    ] ],
    [ "Ethernet PHY Integration Guide", "phy_integration_guide_top.html", "phy_integration_guide_top" ],
    [ "MAC2MAC support", "enet_mac2mac_top.html", [
      [ "Introduction", "enet_mac2mac_top.html#mac2mac_intro", null ],
      [ "Enable MAC2MAC through Sysconfig", "enet_mac2mac_top.html#mac2mac_syscfg_support", null ]
    ] ],
    [ "Enet Integration Guide", "enet_integration_guide_top.html", [
      [ "Introduction", "enet_integration_guide_top.html#cpsw_integration_guide_intro", null ],
      [ "Getting Familiar with Enet LLD APIs", "enet_integration_guide_top.html#GettingFamiliarWithAPIs", [
        [ "IOCTL Interface", "enet_integration_guide_top.html#IOCTL_description", null ]
      ] ],
      [ "Integrating Enet LLD into User's Application", "enet_integration_guide_top.html#enet_integration_in_app", [
        [ "Init Sequence", "enet_integration_guide_top.html#enet_init_sequence", null ],
        [ "Peripheral Open Sequence", "enet_integration_guide_top.html#enet_open_sequence", null ],
        [ "Port Open Sequence", "enet_integration_guide_top.html#enet_openport_sequence", [
          [ "MAC-PHY link", "enet_integration_guide_top.html#autotoc_md2995", null ],
          [ "MAC-to-MAC link", "enet_integration_guide_top.html#autotoc_md2996", null ]
        ] ],
        [ "Packet Send/Receive Sequence", "enet_integration_guide_top.html#enet_pktrxtx_sequence", null ],
        [ "IOCTL Sequence", "enet_integration_guide_top.html#enet_ioctl_sequence", null ],
        [ "Port Close Sequence", "enet_integration_guide_top.html#enet_closeport_sequence", null ],
        [ "Peripheral Close Sequence", "enet_integration_guide_top.html#enet_close_sequence", null ],
        [ "Deinit Sequence", "enet_integration_guide_top.html#enet_deinit_sequence", null ],
        [ "Peripheral-specific", "enet_integration_guide_top.html#enetper_specific_handling", null ]
      ] ]
    ] ],
    [ "MDIO Manual Mode Enablement", "enetmdio_manualmode.html", [
      [ "Workaround for details errata i2329-MDIO interface corruption and its impact:", "enetmdio_manualmode.html#autotoc_md2998", null ],
      [ "Limitations", "enetmdio_manualmode.html#autotoc_md2999", null ],
      [ "Not supported MDIO IOCTL APIs in MDIO Manual mode", "enetmdio_manualmode.html#autotoc_md3000", null ]
    ] ],
    [ "MDIO PHY Register Access - Clause45 Support", "enet_mdio_clause45_support.html", [
      [ "Overview", "enet_mdio_clause45_support.html#autotoc_md3001", null ],
      [ "Background", "enet_mdio_clause45_support.html#autotoc_md3002", [
        [ "Clause 22 v/s Clause 45", "enet_mdio_clause45_support.html#autotoc_md3003", null ],
        [ "MMD (Management/MDIO Manageable Device) : Required for Clause45 support", "enet_mdio_clause45_support.html#autotoc_md3004", null ]
      ] ],
      [ "Implementation Requirements", "enet_mdio_clause45_support.html#autotoc_md3005", null ],
      [ "Implementation Steps", "enet_mdio_clause45_support.html#autotoc_md3006", [
        [ "Step-1: Modify PHY Driver code with the MMD register as an input argument", "enet_mdio_clause45_support.html#autotoc_md3007", null ],
        [ "Step-2: Update EnetPhy Configuration", "enet_mdio_clause45_support.html#autotoc_md3008", null ],
        [ "Step-3: Common PHY registers access, such as PHY alive, PHY link status, etc uses Clause 22 in order to suport backward compatibility. Replace them with Clause 45 support", "enet_mdio_clause45_support.html#autotoc_md3009", null ]
      ] ],
      [ "Detailed API Reference", "enet_mdio_clause45_support.html#autotoc_md3010", [
        [ "Clause 45 Read Operation", "enet_mdio_clause45_support.html#autotoc_md3011", null ],
        [ "Clause 45 Write Operation", "enet_mdio_clause45_support.html#autotoc_md3012", null ],
        [ "Clause 45 Read-Modify-Write Operation", "enet_mdio_clause45_support.html#autotoc_md3013", null ]
      ] ],
      [ "Key Parameters Explained", "enet_mdio_clause45_support.html#autotoc_md3014", null ],
      [ "Current Limitations", "enet_mdio_clause45_support.html#autotoc_md3015", null ],
      [ "Summary", "enet_mdio_clause45_support.html#autotoc_md3016", null ],
      [ "Limitations", "enet_mdio_clause45_support.html#autotoc_md3017", null ]
    ] ],
    [ "Version Updates from earlier SDKs to Latest", "enet_mcupsdk_10_00_update.html", [
      [ "While upgrading from 11.01 or earlier to latest SDK", "enet_mcupsdk_10_00_update.html#autotoc_md884", [
        [ "Change Set", "enet_mcupsdk_10_00_update.html#autotoc_md885", [
          [ "Change-1 Description", "enet_mcupsdk_10_00_update.html#autotoc_md886", null ],
          [ "Change-1 Impact", "enet_mcupsdk_10_00_update.html#autotoc_md887", null ],
          [ "Change-2 Description", "enet_mcupsdk_10_00_update.html#autotoc_md888", null ],
          [ "Change-2 Impact", "enet_mcupsdk_10_00_update.html#autotoc_md889", null ]
        ] ]
      ] ],
      [ "While upgrading from 11.00 SDK to 11.01 SDK", "enet_mcupsdk_10_00_update.html#autotoc_md890", [
        [ "Change Set", "enet_mcupsdk_10_00_update.html#autotoc_md891", [
          [ "Change-1 Description", "enet_mcupsdk_10_00_update.html#autotoc_md892", null ]
        ] ]
      ] ],
      [ "While upgrading from 10.00 SDK", "enet_mcupsdk_10_00_update.html#autotoc_md893", [
        [ "Change Set", "enet_mcupsdk_10_00_update.html#autotoc_md894", [
          [ "Change-1 Description", "enet_mcupsdk_10_00_update.html#autotoc_md895", null ],
          [ "Change-1 Impact", "enet_mcupsdk_10_00_update.html#autotoc_md896", null ],
          [ "Change-1 Solution", "enet_mcupsdk_10_00_update.html#autotoc_md897", null ],
          [ "Change-2 Description", "enet_mcupsdk_10_00_update.html#autotoc_md898", null ],
          [ "Change-2 Impact", "enet_mcupsdk_10_00_update.html#autotoc_md899", null ],
          [ "Change-2 Solution", "enet_mcupsdk_10_00_update.html#autotoc_md900", null ]
        ] ]
      ] ],
      [ "While upgrading from 09.02 SDK or earlier", "enet_mcupsdk_10_00_update.html#autotoc_md901", [
        [ "Change-1 Description", "enet_mcupsdk_10_00_update.html#autotoc_md902", null ],
        [ "Change-1 Impact", "enet_mcupsdk_10_00_update.html#autotoc_md903", null ],
        [ "Change-1 Solution", "enet_mcupsdk_10_00_update.html#autotoc_md904", [
          [ "Option 1:", "enet_mcupsdk_10_00_update.html#autotoc_md905", null ],
          [ "Option 2:", "enet_mcupsdk_10_00_update.html#autotoc_md906", null ]
        ] ],
        [ "Change-2 Description", "enet_mcupsdk_10_00_update.html#autotoc_md907", null ],
        [ "Change-2 Impact", "enet_mcupsdk_10_00_update.html#autotoc_md908", null ],
        [ "Change-2 Solution", "enet_mcupsdk_10_00_update.html#autotoc_md909", null ]
      ] ]
    ] ],
    [ "Ethernet Performance", "enetlld_performance.html", [
      [ "Introduction", "enetlld_performance.html#autotoc_md3027", null ],
      [ "Setup Details", "enetlld_performance.html#autotoc_md3028", null ],
      [ "Layer 2 Performance", "enetlld_performance.html#autotoc_md3029", [
        [ "Configuration Details", "enetlld_performance.html#autotoc_md3030", [
          [ "For R5F", "enetlld_performance.html#autotoc_md3031", null ],
          [ "Layer 2 Latency", "enetlld_performance.html#autotoc_md3032", null ],
          [ "For A53", "enetlld_performance.html#autotoc_md3033", null ],
          [ "Layer 2 Latency", "enetlld_performance.html#autotoc_md3034", null ]
        ] ]
      ] ],
      [ "Layer-2 Hardware Switching Latency for CPSW", "enetlld_performance.html#autotoc_md3035", [
        [ "Test Setup", "enetlld_performance.html#autotoc_md3036", null ],
        [ "CPSW Latency for RGMII", "enetlld_performance.html#autotoc_md3037", null ]
      ] ],
      [ "TCP/IP Performance", "enetlld_performance.html#autotoc_md3038", [
        [ "Configuration Details", "enetlld_performance.html#autotoc_md3039", [
          [ "TCP Throughput", "enetlld_performance.html#autotoc_md3040", null ],
          [ "UDP Throughput", "enetlld_performance.html#autotoc_md3041", null ]
        ] ]
      ] ],
      [ "See Also", "enetlld_performance.html#autotoc_md3042", null ]
    ] ],
    [ "Enet EST/TAS Support", "enet_tas_top.html", [
      [ "Introduction", "enet_tas_top.html#enet_est_intro", [
        [ "IEEE 802.1Qbv EST/TAS", "enet_tas_top.html#enet_est_intro_est_tas", null ],
        [ "Guard band", "enet_tas_top.html#enet_est_intro_guard_band", null ]
      ] ],
      [ "Enet LLD API", "enet_tas_top.html#enet_est_api", null ],
      [ "CPSW Support", "enet_tas_top.html#enet_est_cpsw", null ]
    ] ],
    [ "Enet Migration Guide", "enet_migration_guide_top.html", [
      [ "Introduction", "enet_migration_guide_top.html#enet_migration_guide_intro", null ],
      [ "Need for sysconfig", "enet_migration_guide_top.html#NeedForSysconfig", null ],
      [ "Enet Driver Initialization Sequence Change", "enet_migration_guide_top.html#EnetInitSeqChange", null ],
      [ "Enet DMA channel open changes", "enet_migration_guide_top.html#EnetDmaChOpenChange", null ],
      [ "Runtime Control API (Enet_ioctl) change", "enet_migration_guide_top.html#EnetIoctlChange", null ],
      [ "Packet Transmit/Receive API related changes", "enet_migration_guide_top.html#PacketTxRxChange", null ],
      [ "Custom Board Support", "enet_migration_guide_top.html#CustomBoardSupport", null ],
      [ "External PHY management", "enet_migration_guide_top.html#ExternalPhyManagement", null ],
      [ "Tuning memory usage of enet driver for non-lwip apps", "enet_migration_guide_top.html#MemoryTuningNonLwip", null ],
      [ "Tuning memory usage of enet driver for lwip apps", "enet_migration_guide_top.html#MemoryTuningLwip", null ],
      [ "Compatibilty Breaks During MCU+ SDK Version Update", "enet_migration_guide_top.html#autotoc_md3025", [
        [ "Updating to version 10.00", "enet_migration_guide_top.html#autotoc_md3026", null ]
      ] ]
    ] ],
    [ "Ethernet Packet Pool Allocation Guidelines", "PACKETPOOL_CONFIG_TOP.html", null ],
    [ "PRU-ICSSG for Ethernet Networking", "ICSSG_ETH_TOP.html", [
      [ "Mode of Operation", "ICSSG_ETH_TOP.html#autotoc_md3048", null ],
      [ "ICSSG Switch and Dual-MAC architecture", "ICSSG_ETH_TOP.html#autotoc_md3049", null ],
      [ "ICSSG Packet flow paths", "ICSSG_ETH_TOP.html#autotoc_md3050", null ],
      [ "Memory usage by ICSSG Queues", "ICSSG_ETH_TOP.html#autotoc_md3051", [
        [ "Switch mode", "ICSSG_ETH_TOP.html#autotoc_md3052", null ],
        [ "Dual-MAC mode", "ICSSG_ETH_TOP.html#autotoc_md3053", null ]
      ] ],
      [ "Modify Port Pool memory usage", "ICSSG_ETH_TOP.html#autotoc_md3054", [
        [ "A. Size per queue and/or", "ICSSG_ETH_TOP.html#autotoc_md3055", null ],
        [ "B. Number of Queues initialized", "ICSSG_ETH_TOP.html#autotoc_md3056", null ]
      ] ],
      [ "Modify Host Pool memory usage", "ICSSG_ETH_TOP.html#autotoc_md3057", [
        [ "A. Size per Queue (and/or)", "ICSSG_ETH_TOP.html#autotoc_md3058", null ],
        [ "B. Number of Queues initialized", "ICSSG_ETH_TOP.html#autotoc_md3059", null ],
        [ "Locally inject different Traffic classes", "ICSSG_ETH_TOP.html#autotoc_md3060", null ]
      ] ]
    ] ]
];