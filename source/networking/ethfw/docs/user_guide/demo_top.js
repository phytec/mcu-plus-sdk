var demo_top =
[
    [ "Ethernet Firmware differentiating features demos", "demo_ethfw_combined_top.html", [
      [ "Introduction", "demo_ethfw_combined_top.html#demo_ethfw_combined_intro", [
        [ "Dependencies", "demo_ethfw_combined_top.html#demo_ethfw_combined_depend", null ]
      ] ],
      [ "Compile Time Configurations", "demo_ethfw_combined_top.html#demo_ethfw_combined_cfg", [
        [ "Ethernet Firmware Demos Configuration", "demo_ethfw_combined_top.html#demo_ethfw_demos_cfg", null ]
      ] ],
      [ "Demo Setup", "demo_ethfw_combined_top.html#demo_ethfw_combined_setup_cfg", [
        [ "Prerequisites", "demo_ethfw_combined_top.html#demo_ethfw_combined_prerequisites", [
          [ "packETH tool", "demo_ethfw_combined_top.html#demo_ethfw_combined_prereq_packEth", null ],
          [ "Python3 and Pip3", "demo_ethfw_combined_top.html#demo_ethfw_combined_prereq_python", null ],
          [ "Wireshark", "demo_ethfw_combined_top.html#demo_ethfw_combined_prereq_wireshark", null ],
          [ "iperf", "demo_ethfw_combined_top.html#demo_ethfw_combined_prereq_iperf", null ],
          [ "bmon", "demo_ethfw_combined_top.html#demo_ethfw_combined_prereq_bmon", null ],
          [ "DHCP Server", "demo_ethfw_combined_top.html#demo_ethfw_dhcp_server", null ],
          [ "Static IP (Optional)", "demo_ethfw_combined_top.html#demo_ethfw_static_ip", null ],
          [ "gPTP stack with Yang support", "demo_ethfw_combined_top.html#demo_ethfw_ptp_stack", null ]
        ] ],
        [ "CCS Boot", "demo_ethfw_combined_top.html#demo_ethfw_combined_CCS", [
          [ "Prerequisites", "demo_ethfw_combined_top.html#demo_l2_switchin_CCS_prereqs", null ],
          [ "Steps", "demo_ethfw_combined_top.html#demo_ethfw_combined_CCS_steps", null ]
        ] ],
        [ "SD Card Boot", "demo_ethfw_combined_top.html#demo_ethfw_combined_sdcard", [
          [ "Steps", "demo_ethfw_combined_top.html#demo_ethfw_combined_sdcard_steps", null ]
        ] ]
      ] ],
      [ "Running the Demo", "demo_ethfw_combined_top.html#demo_ethfw_combined_execution", [
        [ "Connecting External Devices", "demo_ethfw_combined_top.html#ethfw_demo_connections", null ],
        [ "Virtual Net Driver on A72", "demo_ethfw_combined_top.html#ethfw_virt_net_driver", null ],
        [ "iperf", "demo_ethfw_combined_top.html#ethfw_running_iperf", null ],
        [ "iperf with ETHFW server", "demo_ethfw_combined_top.html#ethfw_running_iperf_ethfw", null ],
        [ "iperf with virtual client", "demo_ethfw_combined_top.html#ethfw_running_iperf_virtmac", null ],
        [ "gPTP Stack", "demo_ethfw_combined_top.html#ethfw_demo_gptp", null ],
        [ "GUI Configurator Tool", "demo_ethfw_combined_top.html#ethfw_gui_tool_configuration", null ],
        [ "InterVLAN Routing", "demo_ethfw_combined_top.html#ethfw_intervlan_routing", [
          [ "Software InterVLAN Routing", "demo_ethfw_combined_top.html#ethfw_sw_intervlan_routing", [
            [ "ALE configuration", "demo_ethfw_combined_top.html#ethfw_sw_intervlan_configuration", null ]
          ] ],
          [ "Hardware InterVLAN Routing", "demo_ethfw_combined_top.html#ethfw_hw_intervlan_routing", [
            [ "ALE configuration", "demo_ethfw_combined_top.html#ethfw_hw_intervlan_configuration", null ]
          ] ]
        ] ],
        [ "IP Next Header Filtering", "demo_ethfw_combined_top.html#ethfw_ip_nxthdr_filtering", null ],
        [ "Rate Limiting", "demo_ethfw_combined_top.html#ethfw_rate_limiting", null ],
        [ "Inter-core Virtual Ethernet communication with VEPA", "demo_ethfw_combined_top.html#ethfw_intercore_communication_vepa", [
          [ "RTOS client test", "demo_ethfw_combined_top.html#intercore_rtos_client_test_vepa", null ],
          [ "Linux client test", "demo_ethfw_combined_top.html#intercore_linux_client_test_vepa", null ]
        ] ],
        [ "Inter-core Virtual Ethernet communication with shared memory transport", "demo_ethfw_combined_top.html#ethfw_intercore_communication", [
          [ "RTOS client test", "demo_ethfw_combined_top.html#intercore_rtos_client_test", null ],
          [ "Linux client test", "demo_ethfw_combined_top.html#intercore_linux_client_test", [
            [ "TAP User-space Application", "demo_ethfw_combined_top.html#intercore_linux_tap_app", null ],
            [ "Running the test", "demo_ethfw_combined_top.html#intercore_running_linux_client_test", null ]
          ] ]
        ] ],
        [ "TX QoS test on linux client on J7200", "demo_ethfw_combined_top.html#ethfw_tx_qos_linux", null ],
        [ "RX QoS test on linux client on J7200", "demo_ethfw_combined_top.html#ethfw_rx_qos_linux", null ],
        [ "Sample output", "demo_ethfw_combined_top.html#demo_ethfw_combined_output", [
          [ "J721E", "demo_ethfw_combined_top.html#demo_ethfw_combined_output_j721e", [
            [ "UART Console Logs (MCU2_0 Server Application)", "demo_ethfw_combined_top.html#demo_ethfw_combined_logs_uart_j721e", null ],
            [ "CCS Console Logs (MCU2_1 Client Application)", "demo_ethfw_combined_top.html#demo_ethfw_combined_logs_sysmin_j721e", null ]
          ] ],
          [ "J7200", "demo_ethfw_combined_top.html#demo_ethfw_combined_output_j7200", [
            [ "UART Console Logs (MCU2_0 Server Application)", "demo_ethfw_combined_top.html#demo_ethfw_combined_logs_uart_j7200", null ],
            [ "CCS Console Logs (MCU2_1 Client Application)", "demo_ethfw_combined_top.html#demo_ethfw_combined_logs_sysmin_j7200", null ]
          ] ],
          [ "J784S4", "demo_ethfw_combined_top.html#demo_ethfw_combined_output_j784s4", [
            [ "UART Console Logs (MCU2_0 Server Application)", "demo_ethfw_combined_top.html#demo_ethfw_combined_logs_uart_j784s4", null ],
            [ "CCS Console Logs (MCU2_1 Client Application)", "demo_ethfw_combined_top.html#demo_ethfw_combined_logs_sysmin_j784s4", null ]
          ] ],
          [ "J742S2", "demo_ethfw_combined_top.html#demo_ethfw_combined_output_j742s2", [
            [ "UART Console Logs (MCU2_0 Server Application)", "demo_ethfw_combined_top.html#demo_ethfw_combined_logs_uart_j742s2", null ],
            [ "CCS Console Logs (MCU2_1 Client Application)", "demo_ethfw_combined_top.html#demo_ethfw_combined_logs_sysmin_j742s2", null ]
          ] ]
        ] ],
        [ "PPS signal generation", "demo_ethfw_combined_top.html#pps_sig_gen", null ],
        [ "Enhanced Schedule Traffic", "demo_ethfw_combined_top.html#ethfw_est_demo", null ]
      ] ],
      [ "Document Revision History", "demo_ethfw_combined_top.html#demo_ethfw_combined_rev_history", null ]
    ] ]
];