var NETWORKING =
[
    [ "Overview", "NETWORKING.html#autotoc_md2877", [
      [ "Salient Features", "NETWORKING.html#autotoc_md2878", null ],
      [ "Software Components Overview", "NETWORKING.html#autotoc_md2879", null ],
      [ "Examples and Demos", "NETWORKING.html#autotoc_md2880", null ],
      [ "Networking Features", "NETWORKING.html#autotoc_md2881", null ],
      [ "Ethernet Driver", "NETWORKING.html#autotoc_md2882", null ],
      [ "ICSS-EMAC Driver", "NETWORKING.html#autotoc_md2883", null ],
      [ "ICSS TimeSync", "NETWORKING.html#autotoc_md2884", null ],
      [ "TCP/IP Stack", "NETWORKING.html#autotoc_md2885", null ],
      [ "Time Sensitive Networking (TSN) Stack", "NETWORKING.html#autotoc_md2886", null ],
      [ "Enet CLI", "NETWORKING.html#autotoc_md2887", null ]
    ] ],
    [ "Ethernet Features(CPSW)", "NETWORKING_FEATURES.html", [
      [ "Overview", "NETWORKING_FEATURES.html#autotoc_md2892", null ],
      [ "Feature Summary", "NETWORKING_FEATURES.html#autotoc_md2893", null ],
      [ "Basic Layer 2 Switching", "NETWORKING_FEATURES.html#autotoc_md2894", null ],
      [ "Layer 3 switching with LwIP Stack", "NETWORKING_FEATURES.html#autotoc_md2895", null ],
      [ "TSN support", "NETWORKING_FEATURES.html#autotoc_md2896", null ],
      [ "EST/TAS support", "NETWORKING_FEATURES.html#autotoc_md2897", null ],
      [ "CBS", "NETWORKING_FEATURES.html#autotoc_md2898", null ],
      [ "IET", "NETWORKING_FEATURES.html#autotoc_md2899", null ],
      [ "Cut Through", "NETWORKING_FEATURES.html#autotoc_md2900", null ],
      [ "See Also", "NETWORKING_FEATURES.html#autotoc_md2901", null ]
    ] ],
    [ "Enet-LLD", "ENET_LLD.html", "ENET_LLD" ],
    [ "ICSS-EMAC", "ICSS_EMAC.html", "ICSS_EMAC" ],
    [ "ICSS TimeSync", "ICSS_TIMESYNC.html", "ICSS_TIMESYNC" ],
    [ "Lightweight IP (LwIP)", "NETWORKING_LWIP.html", "NETWORKING_LWIP" ],
    [ "Time-Sensitive Networking (TSN)", "ENET_CPSW_TSN.html", [
      [ "Overview", "ENET_CPSW_TSN.html#autotoc_md2937", null ],
      [ "Features and IEEE Standard Coverage", "ENET_CPSW_TSN.html#ENET_CPSW_TSN_FEATURES", [
        [ "Feature/Standard Supported", "ENET_CPSW_TSN.html#autotoc_md2939", [
          [ "Supported Features - gPTP", "ENET_CPSW_TSN.html#autotoc_md2940", null ],
          [ "Not Supported Features - gPTP", "ENET_CPSW_TSN.html#autotoc_md2941", null ]
        ] ]
      ] ],
      [ "Architecture", "ENET_CPSW_TSN.html#autotoc_md2943", [
        [ "Software Block Diagram", "ENET_CPSW_TSN.html#autotoc_md2944", null ]
      ] ],
      [ "Resource Utilization", "ENET_CPSW_TSN.html#autotoc_md2945", null ],
      [ "Examples and Feature Coverage", "ENET_CPSW_TSN.html#ENET_CPSW_TSN_EXAMPLES", null ],
      [ "Interoperability Tests", "ENET_CPSW_TSN.html#ENET_CPSW_TSN_INTEROP", [
        [ "gPTP Interoperability", "ENET_CPSW_TSN.html#autotoc_md2947", null ]
      ] ],
      [ "Memory Footprint", "ENET_CPSW_TSN.html#ENET_CPSW_TSN_MEMORY", [
        [ "Configuration 1: gPTP Only", "ENET_CPSW_TSN.html#autotoc_md2949", null ]
      ] ],
      [ "Performance Metrics", "ENET_CPSW_TSN.html#ENET_CPSW_TSN_PERFORMANCE", [
        [ "gPTP performance", "ENET_CPSW_TSN.html#autotoc_md2951", null ]
      ] ],
      [ "See Also", "ENET_CPSW_TSN.html#autotoc_md2953", null ]
    ] ],
    [ "TSN Developer Guidelines", "ENET_CPSW_TSN_DEV_GUIDE.html", [
      [ "Memory Footprint Optimization", "ENET_CPSW_TSN_DEV_GUIDE.html#ENET_CPSW_TSN_MEMORY_OPT", [
        [ "Disable unused modules", "ENET_CPSW_TSN_DEV_GUIDE.html#autotoc_md2974", null ],
        [ "Reduce SimpleDB entry counts", "ENET_CPSW_TSN_DEV_GUIDE.html#autotoc_md2975", null ],
        [ "Reduce UB_ESARRAY pool", "ENET_CPSW_TSN_DEV_GUIDE.html#autotoc_md2976", null ],
        [ "gPTP shared memory (clock domain IPC)", "ENET_CPSW_TSN_DEV_GUIDE.html#autotoc_md2977", null ]
      ] ],
      [ "gPTP Time-to-Sync Optimization", "ENET_CPSW_TSN_DEV_GUIDE.html#ENET_CPSW_TSN_GPTP_SYNC_OPT", [
        [ "Shorten the clock computation interval", "ENET_CPSW_TSN_DEV_GUIDE.html#autotoc_md2979", null ],
        [ "Increase frequency offset update rate", "ENET_CPSW_TSN_DEV_GUIDE.html#autotoc_md2980", null ],
        [ "Reduce IIR filter alpha (faster response)", "ENET_CPSW_TSN_DEV_GUIDE.html#autotoc_md2981", null ],
        [ "Shorten the sync interval", "ENET_CPSW_TSN_DEV_GUIDE.html#autotoc_md2982", null ],
        [ "Enable hardware phase adjustment", "ENET_CPSW_TSN_DEV_GUIDE.html#autotoc_md2983", null ]
      ] ],
      [ "Troubleshooting Guidelines", "ENET_CPSW_TSN_DEV_GUIDE.html#ENET_CPSW_TSN_TROUBLESHOOT", [
        [ "How to read gPTP log output", "ENET_CPSW_TSN_DEV_GUIDE.html#autotoc_md2985", null ],
        [ "gPTP is running but clock is not locked (gmsync=false)", "ENET_CPSW_TSN_DEV_GUIDE.html#autotoc_md2986", null ],
        [ "Sync gaps appear in the log (INFO \"sync gap\" or \"fup gap\")", "ENET_CPSW_TSN_DEV_GUIDE.html#autotoc_md2987", null ],
        [ "<tt>timeleap_past</tt> errors in gPTP log", "ENET_CPSW_TSN_DEV_GUIDE.html#autotoc_md2988", null ],
        [ "uniconf fails to start", "ENET_CPSW_TSN_DEV_GUIDE.html#autotoc_md2989", null ],
        [ "How to enable logging to a buffer (avoid gPTP jitter from slow UART)", "ENET_CPSW_TSN_DEV_GUIDE.html#autotoc_md2990", null ]
      ] ],
      [ "Known Limitations", "ENET_CPSW_TSN_DEV_GUIDE.html#ENET_CPSW_TSN_LIMITATIONS", null ]
    ] ],
    [ "TSN Userguide", "ENET_CPSW_TSN_ARCH_GUIDE.html", [
      [ "Introduction", "ENET_CPSW_TSN_ARCH_GUIDE.html#autotoc_md2954", null ],
      [ "IEEE 802.1AS-2020 (gPTP)", "ENET_CPSW_TSN_ARCH_GUIDE.html#autotoc_md2956", [
        [ "How gPTP Interacts With Hardware", "ENET_CPSW_TSN_ARCH_GUIDE.html#autotoc_md2957", null ],
        [ "Master Role", "ENET_CPSW_TSN_ARCH_GUIDE.html#autotoc_md2958", null ],
        [ "Slave Role", "ENET_CPSW_TSN_ARCH_GUIDE.html#autotoc_md2959", [
          [ "Clock Servo Design", "ENET_CPSW_TSN_ARCH_GUIDE.html#ENET_CPSW_TSN_ARCH_GUIDE_SERVO", [
            [ "Scatter Gather list related change", "enet_migration_guide_top.html#autotoc_md3018", null ],
            [ "DisableCacheOps related change", "enet_migration_guide_top.html#autotoc_md3019", null ],
            [ "Checksum offload related change", "enet_migration_guide_top.html#autotoc_md3020", null ],
            [ "Board config C file", "enet_migration_guide_top.html#autotoc_md3021", null ],
            [ "Ethernet MAC address Management", "enet_migration_guide_top.html#autotoc_md3022", null ],
            [ "1. Using Syscfg GUI tool", "enet_migration_guide_top.html#autotoc_md3023", null ],
            [ "2. Using Custom Board Option", "enet_migration_guide_top.html#autotoc_md3024", [
              [ "Board config C file", "enetphy_guide_top.html#autotoc_md2997", null ],
              [ "To Configure DHCP", "NETWORKING_LWIP_STATIC_IP.html#autotoc_md2916", null ],
              [ "To Configure Static IP", "NETWORKING_LWIP_STATIC_IP.html#autotoc_md2917", null ]
            ] ],
            [ "Frequency Offset Loop", "ENET_CPSW_TSN_ARCH_GUIDE.html#autotoc_md2960", null ],
            [ "Phase Offset Loop", "ENET_CPSW_TSN_ARCH_GUIDE.html#autotoc_md2961", null ],
            [ "Tunable Constants", "ENET_CPSW_TSN_ARCH_GUIDE.html#autotoc_md2962", null ],
            [ "QUICK_SYNC_ALGO — Fast-Sync Path", "ENET_CPSW_TSN_ARCH_GUIDE.html#autotoc_md2963", null ]
          ] ]
        ] ],
        [ "Bridge (Boundary Clock)", "ENET_CPSW_TSN_ARCH_GUIDE.html#autotoc_md2964", null ]
      ] ],
      [ "Unibase, Uniconf, Combase Libraries", "ENET_CPSW_TSN_ARCH_GUIDE.html#autotoc_md2967", null ],
      [ "Configuring TSN Hardware Features via Uniconf", "ENET_CPSW_TSN_ARCH_GUIDE.html#autotoc_md2969", [
        [ "Configuring EST (802.1Qbv Scheduled Traffic)", "ENET_CPSW_TSN_ARCH_GUIDE.html#ENET_CPSW_TSN_ARCH_GUIDE_EST", null ],
        [ "Configuring IET (802.3br / 802.1Qbu Frame Preemption)", "ENET_CPSW_TSN_ARCH_GUIDE.html#autotoc_md2970", null ],
        [ "Configuring CBS (802.1Qav Credit-Based Shaper)", "ENET_CPSW_TSN_ARCH_GUIDE.html#ENET_CPSW_TSN_ARCH_GUIDE_CBS", null ]
      ] ],
      [ "See Also", "ENET_CPSW_TSN_ARCH_GUIDE.html#autotoc_md2972", null ]
    ] ],
    [ "Ethernet TSN and gPTP Stack - API and Integration Guide", "ENET_CPSW_TSN_GPTP.html", [
      [ "Pre-requisites", "ENET_CPSW_TSN_GPTP.html#autotoc_md2919", null ],
      [ "Introduction", "ENET_CPSW_TSN_GPTP.html#autotoc_md2920", null ],
      [ "Demo and Examples", "ENET_CPSW_TSN_GPTP.html#autotoc_md2921", null ],
      [ "TSN Stack", "ENET_CPSW_TSN_GPTP.html#autotoc_md2922", [
        [ "Compilation", "ENET_CPSW_TSN_GPTP.html#autotoc_md2923", null ],
        [ "Modules", "ENET_CPSW_TSN_GPTP.html#autotoc_md2924", null ],
        [ "Stack Initialization", "ENET_CPSW_TSN_GPTP.html#ENET_CPSW_TSN_STACK_INITIALIZATION", null ],
        [ "Logging", "ENET_CPSW_TSN_GPTP.html#ENET_CPSW_TSN_LOGGING", null ],
        [ "Starting uniconf and gPTP", "ENET_CPSW_TSN_GPTP.html#ENET_CPSW_TSN_UNICONF_INITIALIZATION", null ],
        [ "TSN Deinitialization", "ENET_CPSW_TSN_GPTP.html#ENET_CPSW_TSN_STACK_DEINITIALIZATION", null ]
      ] ],
      [ "Integration", "ENET_CPSW_TSN_GPTP.html#autotoc_md2925", [
        [ "Source integration", "ENET_CPSW_TSN_GPTP.html#ENET_CPSW_TSN_SOURCE_INTEGRATION", null ],
        [ "Uniconf configuration", "ENET_CPSW_TSN_GPTP.html#ENET_CPSW_TSN_UNICONF_CONFIGURATION", null ],
        [ "gPTP Yang Config Parameters", "ENET_CPSW_TSN_GPTP.html#ENET_CPSW_TSN_YANG_CONFIG_PARAMS", [
          [ "gPTP string-based to key-based mapping", "ENET_CPSW_TSN_GPTP.html#autotoc_md2926", null ],
          [ "ieee1588-ptp-tt_access.c/h", "ENET_CPSW_TSN_GPTP.html#autotoc_md2927", null ],
          [ "Default example configurations", "ENET_CPSW_TSN_GPTP.html#autotoc_md2928", null ]
        ] ],
        [ "gPTP Non-Yang Config Parameters", "ENET_CPSW_TSN_GPTP.html#autotoc_md2929", [
          [ "gptpgcfg wrapper APIs to modify Non-Yang parameter", "ENET_CPSW_TSN_GPTP.html#autotoc_md2930", null ],
          [ "Default example configurations", "ENET_CPSW_TSN_GPTP.html#autotoc_md2931", null ],
          [ "gPTP Multiple Domains", "ENET_CPSW_TSN_GPTP.html#autotoc_md2932", null ],
          [ "gPTP Shorter Sync Interval", "ENET_CPSW_TSN_GPTP.html#autotoc_md2933", null ],
          [ "gPTP Performance optimization", "ENET_CPSW_TSN_GPTP.html#autotoc_md2934", null ]
        ] ]
      ] ],
      [ "Limitations", "ENET_CPSW_TSN_GPTP.html#autotoc_md2935", null ],
      [ "See Also", "ENET_CPSW_TSN_GPTP.html#autotoc_md2936", null ]
    ] ],
    [ "Ethernet TSN gPTP Examples", "EXAMPLES_ENET_CPSW_TSN_GPTP.html", "EXAMPLES_ENET_CPSW_TSN_GPTP" ],
    [ "Enet CLI", "ENET_CLI.html", [
      [ "Introduction", "ENET_CLI.html#autotoc_md2902", null ],
      [ "Features", "ENET_CLI.html#autotoc_md2903", [
        [ "List of Built-In Commands", "ENET_CLI.html#autotoc_md2904", null ]
      ] ],
      [ "Demo and Examples", "ENET_CLI.html#autotoc_md2905", null ],
      [ "Usage Guide", "ENET_CLI.html#autotoc_md2906", null ],
      [ "Adding Custom Commands", "ENET_CLI.html#autotoc_md2907", [
        [ "FreeRTOS_Plus_CLI", "ENET_CLI.html#autotoc_md2908", null ]
      ] ]
    ] ],
    [ "Enet CLI Example", "EXAMPLES_ENET_CLI_APP.html", [
      [ "Introduction", "EXAMPLES_ENET_CLI_APP.html#autotoc_md2085", null ],
      [ "Supported Combinations", "EXAMPLES_ENET_CLI_APP.html#autotoc_md2086", null ],
      [ "Packet pool configuration", "EXAMPLES_ENET_CLI_APP.html#autotoc_md2087", null ],
      [ "Steps to Run the Example", "EXAMPLES_ENET_CLI_APP.html#autotoc_md2088", [
        [ "Build the Example", "EXAMPLES_ENET_CLI_APP.html#autotoc_md2089", null ],
        [ "Sample Outputs", "EXAMPLES_ENET_CLI_APP.html#autotoc_md2090", null ],
        [ "Accessing the LwIP Shell", "EXAMPLES_ENET_CLI_APP.html#autotoc_md2091", null ]
      ] ],
      [ "See Also", "EXAMPLES_ENET_CLI_APP.html#autotoc_md2092", null ]
    ] ]
];