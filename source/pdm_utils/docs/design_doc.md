# DM Power Analysis Tool High-Level Design 
## Introduction
DM Power Analysis tool is a software tool that enables the retrieval of clock tree, PLLs, and PSCs settings from a device at runtime. This functionality allows for a comprehensive understanding of the device from a Device Management perspective.

## Overview

DM Power Analysis tool provides APIs to print the current status of PLLs, PSCs and clock tree of a given device. It does this by utilizing MMRs to read the PLL & PSC configuration and also PM driver APIs to construct the clock tree for the module clocks.

## Architecture

The DM Power Analysis Tool architecture consists of the following source files:
each functionality of the tool is categorized into one source file as below.

1. pdm_utils_clock.c  
2. pdm_utils_pet.c  
3. pdm_utils_pll.c  
4. pdm_utils_psc.c
5. pdm_utils_soc.c

*pdm_utils_clock.c*: Implementation of clock tree for SoC module clocks is done here
*pdm_utils_pet.c* : Implementation of PET clock table is done here
*pdm_utils_pll.c* : Implementation to read PLL status and configuration is done here
*pdm_utils_psc.c* : Implementation to read PSC status is done here
*pdm_utils_soc.c* : SoC abstraction layer 

## Implementation

1. PdmUtils_getPllDataBook() API gets the PLL status/configuration from the MMRs directly and updates the provided buffer.
2. PdmUtils_getPscDataBook() API gets the PSC status/configuration from MMRs directly and updates the provided buffer.
3. PdmUtils_getPetClockBook() API utilizes the PM driver APIs and recursively gets the clock parents for a given module clock,constructs the clock tree, and updates the provided buffer.
4. PdmUtils_getSocClockTree() API prints a table with IP names and their frequencies similar to the representation of PET(Power Estimation Tool). This helps user to directly use this table as input for the PET.

Currently this tool is supported on all R5 & C7x cores

### PdmUtils_getPllDataBook():

1. This API iterates though MAIN and MCU PLLs and accesses the corresponding MMRs of the PLL. Reads the configuration registers and populates the PLL data structure (PdmUtils_PllData) at each step.
   This structure holds the configuration of PLL such as PllId, domain, pllDivData, number of HSDIVs connected, status of the HSDIVs, VCO clock frequency etc.

### PdmUtils_getPscDataBook():

1. This API iterates through MAIN and MCU PSCs. Each PSC has one or more PDs. Each PD has one or more LPSC. Each LPSC has one or more IPs connected to it.
   This API collects data of each of the PSCs, PDs and LPSCs, get the status of each of them by reading the corresponding MMRs, and prints in a table format.

### PdmUtils_getPetClockBook():

1. This API iterates through each Module and identifies how many input clocks are present for each IP.
   identifies parent clock to each of these input clocks till the Oscillator, using the PM library APIs. Thus creating the clock tree for each input clock.
   At each stage of the clock tree, this API also captures the frequency of the clock using the Sciclient API.

### PdmUtils_getSocClockTree():

1. Incase of PdmUtils_printClockTree() API, data related to all clocks and all IPs are dumped together. Hence it might be difficult to look at few of the important IP frequencies since it needs to be searched in the data.
   PdmUtils_printPetClockTable() API solves this problem by providing a table of important IPs and its clocks, which resembles the Power Estimation Tool.
2. A static data structure is maintained, which holds the device and clock IDs of specific IPs. Then Sciclient APIs are used to get the frequency of each clock and and updates the provided buffer.

## Output

Refer to [user_guide ](user_guide.md)
