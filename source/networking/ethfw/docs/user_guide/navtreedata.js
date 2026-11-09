/*
@ @licstart  The following is the entire license notice for the
JavaScript code in this file.

Copyright (C) 1997-2017 by Dimitri van Heesch

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

@licend  The above is the entire license notice
for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "Ethernet Firmware", "index.html", [
    [ "Introduction", "index.html", [
      [ "Integrated Switch", "index.html#ethfw_c_ug_switch", null ],
      [ "Ethernet Firmware Software Stack", "index.html#ethfw_c_ug_fw_architecture", null ],
      [ "Document Revision History", "index.html#ethfw_main_rev_history", null ]
    ] ],
    [ "User Guide", "ethfw_c_ug_top.html", [
      [ "Supported Features", "ethfw_c_ug_top.html#ethfw_c_ug_features_list", null ],
      [ "Master Core (EthFw)", "ethfw_c_ug_top.html#ethfw_master_core", [
        [ "Resource Utilization", "ethfw_c_ug_top.html#ethfw_resource_utilization", null ]
      ] ],
      [ "Remote Core Clients", "ethfw_c_ug_top.html#ethfw_remote_clients", [
        [ "RTOS Client", "ethfw_c_ug_top.html#ethfw_client_rtos", [
          [ "Building RTOS client for Main R5F 1 Core 0", "ethfw_c_ug_top.html#ethfw_client_rtos_mcu30", null ]
        ] ],
        [ "Linux Client", "ethfw_c_ug_top.html#ethfw_client_linux", null ],
        [ "QNX Client", "ethfw_c_ug_top.html#ethfw_client_qnx", null ],
        [ "AUTOSAR Client", "ethfw_c_ug_top.html#ethfw_client_autosar", null ],
        [ "Component Location", "ethfw_c_ug_top.html#ethfw_component_location", null ]
      ] ],
      [ "MAC-only", "ethfw_c_ug_top.html#ethfw_maconly", [
        [ "Hardware physical ports", "ethfw_c_ug_top.html#ethfw_mac_port", null ],
        [ "Local switch port", "ethfw_c_ug_top.html#ethfw_local_switch_port", null ],
        [ "Virtual switch port", "ethfw_c_ug_top.html#ethfw_virtual_switch_port", null ],
        [ "Virtual MAC port", "ethfw_c_ug_top.html#ethfw_virtual_mac_port", null ],
        [ "Configuring additional ports in MAC-only mode", "ethfw_c_ug_top.html#ethfw_additional_maconly", null ]
      ] ],
      [ "Default Port Configuration", "ethfw_c_ug_top.html#ethfw_port_cfg", [
        [ "J721E Port Configuration", "ethfw_c_ug_top.html#ethfw_j721e_port_cfg", null ],
        [ "J7200 Port Configuration", "ethfw_c_ug_top.html#ethfw_j7200_port_cfg", null ],
        [ "J784S4 Port Configuration", "ethfw_c_ug_top.html#ethfw_j784s4_port_cfg", null ],
        [ "J742S2 Port Configuration", "ethfw_c_ug_top.html#ethfw_j742s2_port_cfg", [
          [ "ETHFW J742S2 Testing", "ethfw_c_ug_top.html#ethfw_j742s2_testing", null ]
        ] ]
      ] ],
      [ "Inter-core Virtual Ethernet via Shared Memory Transport", "ethfw_c_ug_top.html#ethfw_intercore_eth", [
        [ "Topology and Design overview", "ethfw_c_ug_top.html#ethfw_intercore_topology", null ],
        [ "EthFw Server integration", "ethfw_c_ug_top.html#ethfw_intercore_r5server", null ],
        [ "R5F RTOS Client integration", "ethfw_c_ug_top.html#ethfw_intercore_r5client", null ],
        [ "A72 Linux Client integration", "ethfw_c_ug_top.html#ethfw_intercore_a72client", null ]
      ] ],
      [ "Inter-core Virtual Ethernet via VEPA", "ethfw_c_ug_top.html#ethfw_intercore_vepa", [
        [ "Topology and Design overview", "ethfw_c_ug_top.html#ethfw_intercore_topology_vepa", null ],
        [ "EthFw Server integration", "ethfw_c_ug_top.html#ethfw_intercore_r5server_vepa", null ]
      ] ],
      [ "Multicast and Broadcast Support", "ethfw_c_ug_top.html#ethfw_mcast_support", [
        [ "Shared Multicast", "ethfw_c_ug_top.html#ethfw_shared_mcast", null ],
        [ "Exclusive Multicast", "ethfw_c_ug_top.html#ethfw_exclusive_mcast", null ],
        [ "Reserved Multicast", "ethfw_c_ug_top.html#ethfw_reserved_mcast", null ]
      ] ],
      [ "VLAN Support", "ethfw_c_ug_top.html#ethfw_vlan", [
        [ "VLAN Configuration", "ethfw_c_ug_top.html#ethfw_vlan_server_cfg", null ],
        [ "Joining and leaving VLANs", "ethfw_c_ug_top.html#ethfw_vlan_join_leave", null ]
      ] ],
      [ "CPSW Recovery", "ethfw_c_ug_top.html#ethfw_cpsw_recovery", [
        [ "Recovery Sequence", "ethfw_c_ug_top.html#ethfw_recovery_sequence", null ],
        [ "Remote Client Requirements", "ethfw_c_ug_top.html#ethfw_recovery_client_reqs", null ],
        [ "CPTS time synchronization", "ethfw_c_ug_top.html#ethfw_recovery_cpts_sync", null ],
        [ "Miscellaneous details", "ethfw_c_ug_top.html#ethfw_recovery_misc", null ]
      ] ],
      [ "Quality of Service (QoS)", "ethfw_c_ug_top.html#ethfw_qos", [
        [ "TX QoS", "ethfw_c_ug_top.html#ethfw_tx_qos", null ],
        [ "RX QoS", "ethfw_c_ug_top.html#ethfw_rx_qos", [
          [ "ALE Classification", "ethfw_c_ug_top.html#ethfw_ale_classification", null ]
        ] ]
      ] ],
      [ "Trace Support", "ethfw_c_ug_top.html#ethfw_tracing", null ],
      [ "Port Mirroring Support", "ethfw_c_ug_top.html#ethfw_port_mirroring", [
        [ "Destination port mirroring", "ethfw_c_ug_top.html#ethfw_dst_port_mirroring", null ],
        [ "Source port mirroring", "ethfw_c_ug_top.html#ethfw_src_port_mirroring", null ],
        [ "Table entry port mirroring", "ethfw_c_ug_top.html#ethfw_tbl_entry_port_mirroring", null ]
      ] ],
      [ "Heartbeat Mechanism", "ethfw_c_ug_top.html#ethfw_c_ug_heartbeat_mechanism", null ],
      [ "Multicore Timesync", "ethfw_c_ug_top.html#ethfw_c_ug_mts", null ],
      [ "EthFw Demos", "ethfw_c_ug_top.html#ethfw_c_ug_ethfw_demos", [
        [ "EthFw Switching & TCP/IP Apps Demo", "ethfw_c_ug_top.html#ethfw_switching_demo", null ],
        [ "Inter-VLAN Routing Demo", "ethfw_c_ug_top.html#ethfw_intervlan_demo", null ],
        [ "Enhanced Schedule Traffic", "ethfw_c_ug_top.html#ethfw_est_demo_support", null ]
      ] ],
      [ "Dependencies", "ethfw_c_ug_top.html#ethfw_instal_top", [
        [ "Hardware Dependencies", "ethfw_c_ug_top.html#ethfw_depend_hw", [
          [ "J721E/J7200 EVM", "ethfw_c_ug_top.html#ethfw_depend_evm_j721e", null ],
          [ "J721E GESI Expansion Board", "ethfw_c_ug_top.html#ethfw_depend_evm_gesi_j721e", null ],
          [ "J721E Quad-Port Eth Expansion Board", "ethfw_c_ug_top.html#ethfw_depend_evm_quadport_j721e", null ],
          [ "J7200 Quad-Port Eth Expansion Board", "ethfw_c_ug_top.html#ethfw_depend_evm_quadport_j7200", null ],
          [ "J784S4/J742S2 EVM", "ethfw_c_ug_top.html#ethfw_depend_evm_j784s4", null ],
          [ "J784S4 Quad-Port Eth Expansion Board", "ethfw_c_ug_top.html#ethfw_depend_evm_quadport_j784s4", null ]
        ] ],
        [ "Software Dependencies", "ethfw_c_ug_top.html#ethfw_depend_sw", [
          [ "PDK", "ethfw_c_ug_top.html#ethfw_depend_pdk", [
            [ "CSL", "ethfw_c_ug_top.html#ethfw_depend_pdk_csl", null ],
            [ "UDMA", "ethfw_c_ug_top.html#ethfw_depend_pdk_udma", null ],
            [ "Enet LLD", "ethfw_c_ug_top.html#ethfw_depend_pdk_enet", null ]
          ] ],
          [ "lwIP", "ethfw_c_ug_top.html#ethfw_depend_lwip", null ],
          [ "TSN stack", "ethfw_c_ug_top.html#ethfw_depend_tsn", null ],
          [ "Ethernet Firmware Proxy ARP", "ethfw_c_ug_top.html#ethfw_depend_lwip_proxyarp", null ],
          [ "SafeRTOS", "ethfw_c_ug_top.html#ethfw_depend_safertos", null ]
        ] ],
        [ "IDE (CCS)", "ethfw_c_ug_top.html#ethfw_instal_ccs", null ]
      ] ],
      [ "Installation Steps", "ethfw_c_ug_top.html#ethfw_instal_steps", null ],
      [ "Directory Structure", "ethfw_c_ug_top.html#ethfw_dir", [
        [ "Post Install Directory Structure", "ethfw_c_ug_top.html#ethfw_post_install_j721e", null ],
        [ "Utilities Directory Structure", "ethfw_c_ug_top.html#ethfw_dir_utils", null ],
        [ "Demo Application Sources Directory Structure", "ethfw_c_ug_top.html#ethfw_dir_demo", null ],
        [ "EthFw Demonstration Applications", "ethfw_c_ug_top.html#ethfw_dir_switch_demos", null ]
      ] ],
      [ "Build", "ethfw_c_ug_top.html#ethfw_build_top", [
        [ "Setup Environment", "ethfw_c_ug_top.html#ethfw_build_setup_env", null ],
        [ "Build", "ethfw_c_ug_top.html#ethfw_build", [
          [ "Build All", "ethfw_c_ug_top.html#ethfw_build_all", null ],
          [ "SafeRTOS Build", "ethfw_c_ug_top.html#ethfw_safertos_build_all", null ],
          [ "QNX Build", "ethfw_c_ug_top.html#ethfw_qnx_build_all", null ]
        ] ],
        [ "Clean", "ethfw_c_ug_top.html#ethfw_build_clean", [
          [ "Clean All", "ethfw_c_ug_top.html#ethfw_build_clean_all", null ],
          [ "Remove build output", "ethfw_c_ug_top.html#ethfw_build_clean_binaries", null ]
        ] ],
        [ "Profiles", "ethfw_c_ug_top.html#ethfw_build_profiles", null ],
        [ "Examples Linker File (Select memory location to hold example binary)", "ethfw_c_ug_top.html#ethfw_build_eg_linker", null ]
      ] ],
      [ "Running Examples", "ethfw_c_ug_top.html#ethfw_run_eg", [
        [ "Load Example Binaries", "ethfw_c_ug_top.html#ethfw_run_ccs_load_binary", null ]
      ] ],
      [ "Un Installation", "ethfw_c_ug_top.html#ethfw_uninstall", null ],
      [ "Known issues", "ethfw_c_ug_top.html#ethfw_known_issues", null ],
      [ "Compiler Flags used", "ethfw_c_ug_top.html#ethfw_cflag", [
        [ "Demo Application - Profile: Debug", "ethfw_c_ug_top.html#ethfw_cflag_debug", null ],
        [ "Demo Application - Profile: Release", "ethfw_c_ug_top.html#ethfw_cflag_release", null ]
      ] ],
      [ "Supported Device Families", "ethfw_c_ug_top.html#ethfw_supported_family", null ],
      [ "Document Revision History", "ethfw_c_ug_top.html#ethfw_rev_history", null ]
    ] ],
    [ "Porting Guide", "ethfw_c_porting_top.html", [
      [ "Introduction", "ethfw_c_porting_top.html#ethfw_porting_intro", null ],
      [ "Board initialization", "ethfw_c_porting_top.html#ethfw_porting_board_init", [
        [ "Ethernet port interface type selection", "ethfw_c_porting_top.html#ethfw_porting_board_init_mii", null ],
        [ "Enabling modules via SciClient", "ethfw_c_porting_top.html#ethfw_porting_board_init_sciclient", null ],
        [ "Pinmux settings", "ethfw_c_porting_top.html#ethfw_porting_board_init_pinmux", null ],
        [ "Ethernet PHY initialization", "ethfw_c_porting_top.html#ethfw_porting_board_init_phy", null ],
        [ "SerDes configuration", "ethfw_c_porting_top.html#ethfw_porting_board_init_serdes", [
          [ "Clock configuration", "ethfw_c_porting_top.html#ethfw_porting_board_init_serdes_clks", null ],
          [ "SerDes module configuration", "ethfw_c_porting_top.html#ethfw_porting_board_init_serdes_mod", null ]
        ] ],
        [ "CPSW clocks configuration", "ethfw_c_porting_top.html#ethfw_porting_board_init_cpsw", null ]
      ] ],
      [ "MAC address pool", "ethfw_c_porting_top.html#ethfw_porting_mac_pool", null ],
      [ "MAC port and PHY configuration", "ethfw_c_porting_top.html#ethfw_porting_phy_cfg", null ],
      [ "TI EVM Board Support", "ethfw_c_porting_top.html#ethfw_porting_tievm", null ],
      [ "Document Revision History", "ethfw_c_porting_top.html#ethfw_porting_guide_rev_history", null ]
    ] ],
    [ "EthFw Demo Applications", "demo_top.html", "demo_top" ],
    [ "TI Disclaimer", "TI_DISCLAIMER.html", null ]
  ] ]
];

var NAVTREEINDEX =
[
"TI_DISCLAIMER.html"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';