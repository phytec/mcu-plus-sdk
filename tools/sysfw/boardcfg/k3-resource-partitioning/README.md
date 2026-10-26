# Resource Partitioning Tool

Note: All contents are placed under `.meta` folder.

- To view the folder on Linux system, do `ls -a`.
- To view the folder on Windows system, update settings to view hidden folders.

***

## Introduction

Also known as the k3-respart-tool, the Resource Partitioning tool is
based on Texas Instrument’s SysConfig tool. It allows you to configure
various system level parameters and generate the necessary data to be
fed into many software components.

Typical usage for this tool is for system integrators, where one would
be able to partition **various resources** across different software
components. These resources includes DMA channels, rings, proxies,
interrupts, etc. Apart from this, the tool supports the configuration of
QoS (Quality of Service) to help partition **peripheral devices** across
different CPUs or virtual machines.

## Getting Started

To start using this tool, follow these instructions:

1. Open the [K3 Resource Partitioning
    Tool](https://dev.ti.com/sysconfig/?product=K3-RESOURCE-CONFIGURATION)
2. Click on `Device` and select for the platform that you are
    interested in.
3. Click on a `Baseline Design` for your platform and SDK version. (Use this as the
    starting point for any customization)
    - A baseline design is created for each SDK release whenever the resource
        configuration changes.
    - Select a baseline design based on the SDK release you are working on.
    - If there is no baseline design for  the SDK release, select the baseline
        design corresponding to the previous SDK release.
    - We do not recommend you to start from scratch. Always load the
        baseline file. But for any reason you desire to start from
        scratch, click on the `Empty Design`.

## Usage

Once the design is loaded, the Resource Partitioning, Bandwidth (BW) Limiter,
and QoS Configuration modules will be available.

### Resource Partitioning

This module allows you to partition/allocate resources across different
hosts in the system. In particular, a **host** is a software component
which has a dedicated communication context with **System Firmware**
(SYSFW). A **Resource Management Board Config** file describes how
these resources are partitioned for these hosts, and is passed by the
bootloader to SYSFW as part of the boot up sequence. Additionally, once
configured, this module will automatically generate the board config
file.

In the left pane of GUI, you will see different hosts available and each
host describes the resources allocated to it. All the resources are
organized into different **groups** where users can specify the required
**count** for each resource. To help with this process, the Resource
Partitioning tool automatically keeps track of the remaining resources
available as you make your allocations.

Apart from the resource allocation, the tool also has an option to
configure different **host capabilities**. Click on the **?** next to
the host name to read the documentation for that host.

#### Review Resource Allocation

At any point, users can review the current resource allocation. Select
the **Resource Allocation Table** pane from the three dots shown at the
top right corner of the tool. Here, a table will appear that shows the
exact resources allocated for each host. Each column describes the
resource ranges for a certain host, and each row describes how hosts
consume the given resource.

##### Resource Totals

The last column, labeled \"ALL\", represents the total number of
resources that can be consumed by all hosts. This column is specifically
designated for the `HOST_ID_ALL` value.

It\'s important to note that certain resources, such as
`GPIO interrupts` and `Virtual interrupts`, have fixed hardware
connections. For instance, **DMASS Interrupt Aggregator Virtual
Interrupts** are physically connected to specific cores, which means
those interrupts cannot be randomly allocated to any core. In other
words, certain interrupts can only be allocated to certain cores. So,
the Resource Partitioning tool only allows resource allocations that are
valid.

As a result, when resources allocated to a specific host are
added/removed, the Resource Partitioning tool **does not adjust the
corresponding count in the \"ALL\" column of the table, since those
resources are not available for other cores to consume.**

### Bandwidth Limiter

This module allows users to generate the data required to configure the
various rate limiters available for the SoC. Each rate limiter is
expected to be connected directly to a single source vbusm interface that
is being limited. The limiter allows the user to impose bandwidth limits
for reads or writes, as well as limit the maximum outstanding
transactions for reads or writes. These limits are orthogonal to one
another and can be programmed independently.

In the GUI, users should select a device and enable bandwidth and/or
transaction limits. Then, the corresponding registers can be programmed
with the required limits. The tool will autogenerate a simple
address-value pair data structure in the **qos_data.c** output file.
This can be used to program all the BW limiter settings (typically by
the bootloader).

### QoS Configuration

This module allows users to generate the data required for configuring
CBASS QoS (Quality of Service) endpoints. QoS configuration includes two
types of parameters. Performance tuning parameters for DMA transactions
in the interconnect, and IOMMU path parameters for the masters.
Additionally, for each device, there are multiple master ports from
which DMA requests are made and each device is capable of driving
different values of channel_id for the DMA request. A unique QoS
configuration can be programmed for each channel.

In the GUI, users should select a device, choose the endpoints, and then
select a list of channels for which QoS should be programmed. It is possible
to add multiple instances of QoS modules with the same
device as long as the endpoints and channels do not overlap. Once
configured, the tool generates a simple address-value pair data
structure in the **qos-config.c** output file, which can be used to
program all the QoS settings (typically by the bootloader).

## Generated Output Files

The Resource Partitioning tool generates several files containing the
Resource Management (RM) board config data, QoS configurations \-- all of which
are described in the table below:

| Filename                              | Used by            | Output destination                                         | Comments                                                                                                                                                 |
| ------------------------------------- | ------------------ | ---------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------- |
| rm-cfg.c                              | k3-image-gen       | soc/`<soc>`/`<profile>`/                                   | e.g. - k3-image-gen/soc/j721e/evm/rm-cfg.c                                                                                                               |
| tifs-rm-cfg.c                         | k3-image-gen       | soc/`<soc>`/`<profile>`/                                   | e.g. - k3-image-gen/soc/j721e/evm/tifs-rm-cfg.c                                                                                                          |
| sysfw_img_cfg.h                       | k3-image-gen       | soc/`<soc>`/`<profile>`/                                   | e.g. - k3-image-gen/soc/j721e/evm/sysfw_img_cfg.h                                                                                                        |
| `<soc>`_qos_data.c                    | U-boot             |                                                            |                                                                                                                                                          |
| `<soc>`_qos_data.c                    | SBL                |                                                            |                                                                                                                                                          |
| sciclient_defaultBoardcfg.c           | PDK sciclient      | packages/ti/drv/sciclient/soc/V`<X>`/                      | e.g. - pdk/packages/ti/drv/sciclient/soc/V1/sciclient_defaultBoardcfg.c                                                                                  |
| sciclient_defaultBoardcfg_rm.c        | PDK sciclient      | packages/ti/drv/sciclient/soc/V`<X>`/                      | e.g. - pdk/packages/ti/drv/sciclient/soc/V1/sciclient_defaultBoardcfg_rm.c                                                                               |
| sciclient_defaultBoardcfg_tifs_rm.c   | PDK sciclient      | packages/ti/drv/sciclient/soc/V`<X>`/                      | e.g. - pdk/packages/ti/drv/sciclient/soc/V2/sciclient_defaultBoardcfg_tifs_rm.c                                                                          |
| sciclient_defaultBoardcfg_rm_mcusdk.c | MCU+ SDK sciclient | source/drivers/sciclient/sciclient_default_boardcfg/am62x/ | e.g. - mcu_plus_sdk/source/drivers/sciclient/sciclient_default_boardcfg/am62x/sciclient_defaultBoardcfg_rm.c (`_mcusdk` should be dropped from filename) |

## Troubleshooting

- If you see the following error \"**XYZ is not generated when
    configuration errors exist**\", it means your resource allocation
    has contains an error(s). Adjust the allocations to fix the error(s)
    and then regenerate the output files.
- While removing certain resources allocated to certain core, the
    \"ALL\" column in the \"Resource Allocation Table\" doesn\'t change,
    it means those resources are restricted to that particular core and
    only that core can consume them. [Refer to "Resource Totals" under "Review Resource Allocation" section for more details](#resource-totals).

***

## Developer Notes

### Directory Structure

- **.metadata/product.json** - This file describes all the components that needs
to be loaded by the SysConfig tool. It also describes the supported platforms.
`product.json` describes the components and the components describe the list of
modules and templates that are applicable for the selected device.

- **modules** - This contains the UI module definition for different
configurables, their grouping, organization, and the JavaScript files for handling
onChange events and validations.
- **templates** - This contains the xdt files which describe the output file
formats and small code snippets to generate the data using templates. It also
has few views to  describe the data in a more visual format like a Markdown
table or HTML table.
- **scripts** - These are the JavaScript files for parsing different input data files
which generate the SoC specific JSON objects for the usage in the modules.
It also implements few utility functions which are frequently called by modules
and templates.
- **data** - This contains the JSON objects that the tool uses to populate the
UI items with SoC specific data. Many of these are auto generated using the
parsing scripts.
- **deviceData** - This contains Sysconfig patch files for devices that are
not yet officially supported in the Sysconfig Tool.

### Updating the device data

This tool needs lot of hardware and software data to present the GUI and to
allocate resources. Majority of this data is auto generated using SoC JSON files,
System firmware public documentation, etc. Most users do not need to update this
data. This is required only when adding support for a new SoC, migrating to new
SYSFW version or migrating to new SoC JSON, etc.

Make sure to add symbolic links to the appropriate repositories as shown below:

```bash
#  Do this ONLY if you want to update the data for SysConfig tool
dir=`git rev-parse --show-toplevel`
ln -s <path/to/system firmware repo> $dir/../system-firmware
ln -s <path/to/system firmware autogen repo> $dir/../system-firmware-autogen
```

There is a utility script `./.meta/scripts/generate-data.sh [SOCNAME | all]` to generate
all the required JSON objects for selected SoC or for all of them.

### Procedure for Generating Data Files for a New SoC for the First Time

These are the initial steps to follow when starting from scratch with a new SoC.

- First, follow the instructions in the previous section on adding symbolic links
to the system-firmware and system-firmware-autogen repos. Make sure that the branches
in the original locations are pointing to the latest data for the SoC that you are
trying to add.

- Now edit the data-generation utility script `./meta/scripts/generate-data.sh` and insert a
new soc case under "gen_file()" for the new SoC common name that you are adding. Make
sure to add the correct SoC common name (instead of "j7xyz", in the below example) and
also add the proper path to the SoC design JSON file from the design team under the
git submodule connected under "src_input" in the system-firmware-autogen link you
already established.
For example:

```bash
    j7xyz)
    sysfw_soc=j7xyz
    soc_json=$autogen_repo/src_input/csl/j7xyz_dsn/json/J7XYZ.json
    ;;
```

- Make sure to also add the command "gen_files j7xyz" (replace "j7xyz" with your new SoC name)
in `./meta/scripts/generate-data.sh` for the new SoC in the section towards the bottom of the script
where similar commands are listed for all the other SoCs when the argument "all" is given at
script execution time.

- Next, go to your local SysConfig tool installation and pick out some random device
name from the list of devices to act as a stand-in for the real SoC name which will
be added later to the SysConfig tool. Make sure it does NOT match any of the other "soc"
names used currently in the `data/SOC.json` file. Copy-paste this name (e.g.,
F280013x, or some such) at the end of the list of names in the "devices" array list in
the file `.metadata/product.json`.

- Add a new SoC section in the file `data/SOC.json` that is copied from one of the other
similar SoC sections in the same file (one that has the most similar architecture).
For example:

```json
    {
        "sRAMSize": 8,
        "sRamGranularity": 1,
        "sciClientPrefixReplacement": "TISCI_",
        "main_isolation_hostid": "TISCI_HOST_ID_WKUP_0_R5_0",
        "sciClientSocVersion": "V10",
        "shortName": "j7xyz",
        "soc": "F280013x",
        "wildCardPrivId": 195,
        "pdkUsage": true,
        "mcusdkUsage": true
    },
```

NOTE: replace the value of "sRAMSize" with the total size (in MBs) of MSMC memory on the
SoC (or 0, if no MSMC on the device), replace the value of "main_isolation_hostid" with
the ID of the Host to be allowed to send the main isolation SCI message on the SoC, replace
the "sciClientSoCVersion" value with the PDK folder version number for this SoC, replace
the "shortName" value with the official short name of the SoC (in all lower case), replace
the "soc" value with the name that you used already to add to the "devices" array in the
`.metadata/product.json` file above, and replace any other remaining values that might need
to be updated (uncommon).

- Now create a new SoC subfolder under the `data` folder that has the same "shortName" (e.g., j7xyz)
that you used in the `data/SOC.json` file above. Add a new file to the folder called `DeviceName.json`
and fill it with an empty array: `[]`

- Run the script to generate some initial data files for your new SoC, from the top level of the
repo, like this: `scripts/generate-data.sh j7xyz` (where "j7xyz" is the new SoC common name for
which you want to add the new resource files). If the script is using the proper file path to
your SoC JSON file (set above, earlier), then you should now have the following JSON files
under `data/j7xyz`: DeviceName.json, Firewall.json, Hosts.json, Qos.json and Resources.json.

- Manually add a new file to the `data/j7xyz` folder called BWlimiters.json and fill it with
an empty array: `[]` to start with. Populate this array with information for each rate limiter
available for the SOC. Refer to the file for j784s4 for the parameters expected.

- Now invoke the "gen_initial_user_json()" function in the script "generate-data.sh" in order
to generate a couple of other missing JSON files that we will need. If this is done correctly,
you should then have these additional JSON files in your `data/j7xyz` folder:
HostNames.json and ResDependencies.json.

- However, the file `DeviceName.json` will now have become corrupted (for our usage). So,
simply delete the newly updated `DeviceName.json` and re-create it with nothing but an
empty array in it again: `[]`

- Now, edit the new file `HostNames.json` and replace all the "displayName" values (manually)
that currently just have the word "FILL" in them with meaningful Host display names for each
"hostName" below that entry. NOTE: you can reuse any similar display names from one of the other
SoC data directories with a similar SoC architecture.  E.g., use "TI Foundational Security" for
the host "TIFS" and use "A53_0 Secure host" for the host "A53_0", etc.

- After replacing all the values marked "FILL" in the `HostNames.json` file with the actual host display
names, now run the utility script again (make sure it is returned to the normal usage with "gen_files"
function being used in it once again now): `scripts/generate-data.sh j7xyz`
After this, you should open up the file `Hosts.json` in the updated data folder for your new SoC and
you should see the displayName values inserted in each Host section, as new line items -- the names you
had previously entered in the other file `HostNames.json` before this.

- Now it is time to organize your resources into logical groups based on resource types. You will
start with the recently generated file `ResDependencies.json` and you will modify this to organize
your new SoC's resources into groups.
The best way to do this is to start with the layout of groupings in the `ResDependencies.json` file from
another similar SoC in one of the data/soc folders alongside your current SoC data folder.  So,
open up both of these files together and create similar group arrays using the same "groupName" entries
from the other (established) SoC with similar groups of resources.  You might have a few resources
extra (or a few missing) in the new SoC compared to the similar SoC. But, in general, the groupings
should be pretty much the same. You may have to do quite a bit of moving of lines to get into similar
type groupName arrays. This is okay as long as you don't lose any of the resource lines from the new
SoC's set of resources.
NOTE: you will need to add meaningful names not only for the "groupName" entries, but also for the
generic entries shown currently for each of the "utype" values. Replace these with human readable names
from the related SoC `ResDependencies.json` file. You will also need to copy the "copyFromUtype" lines
from the related SoC entries, if those lines exist in the other file. These are necessary to show that
certain resources need to be mapped together with related resources (like Rings with their related DMA
channel types).

- After this grouping is done, you will also have to manually update the Host restrictions on the
interrupt router and interrupt aggregator resources (VINTs, etc.) to represent the actual interrupt
connections that are allowed in the hardware.
See the section below, on "Updating ResDependencies.json", in order to go through this procedure.

- Next, after all manual updates have been made in your new SoC's `ResDependencies.json` file,
you will need to again run the utility script one more time: `scripts/generate-data.sh j7xyz`.
This ensures that all your final updates are translated properly into the output file:
`Resources.json`. Review this output file to ensure that it looks correct after you run the script.
Note that the `Resources.json` will also have many resource ranges (for each resource type) that were
not necessarily present in the `ResDependencies.json` file.

- Finally, you will need to create a new baseline version of the `out/j7xyz-evm.syscfg` file
to load into the SysConfig tool, as described towards the beginning of this README. It is recommended
to start from a copy of a related SoC's .syscfg file and then add (or remove) resource assignments
according to the new SoC's resources, to create a new baseline set of assignments for the new SoC.

### Updating ResDependencies.json  

ResDependencies.json file contains extra restrictions on the resource allocation.
For example all the interrupts may not be available for all the cores. this
information is added in this file. Basic structure of the file can be created
using the autogen script itself(by invoking the gen_initial_user_json function
in generate-data.sh)

To add interrupt related updates, look for interrupt_cfg.rst file in the folder
docs/public/5_soc_doc/\<soc> in system-firmware repo. In that
file, search for tables having its name ending with "Output Destinations".
Each table represents one type of resource and its interrupt routing information.
These resources include CMP_EVENT_INTROUTER0, MAIN_GPIOMUX_INTROUTER0,
MCU_MCU_GPIOMUX_INTROUTER0, TIMESYNC_EVENT_INTROUTER0 etc. Ignore the
TIMESYNC_EVENT_INTROUTER0 and CMP_EVENT_INTROUTER0 resource's table and look for
all other resource's table. Take one resource's table and look for the columns
"Destination Name" and "IR Output Index". One entry in the table represents that
the IR Output Index can be routed to the corresponding host. Select one host
from the "Destination Name" column and see which all "IR Output Index" can be
routed to the host. The IR Output Index might not be contiguous, but to avoid
further complexity, take the largest continuous range of output index that can
be assigned to the host. Similarly check for other hosts and find what ranges of
resource can be assigned to the host. Add this information as a "resRange" entry
with the following fields resStart: the starting index of resource, resCount:
number of resources that can be assigned,restrictHosts: the hosts that can be
assigned the particular range of resource for the corresponding resource, in
ResDependencies.json file.
For example:

```json
    "deviceName": "AM62X_DEV_WKUP_MCU_GPIOMUX_INTROUTER0",
    "subtypeName": "RESASG_SUBTYPE_IR_OUTPUT",
    "utype": "WKUP GPIO Interrupt Router",
    "resRange": [
        {
            "resStart": 6,
            "resCount": 4,
            "restrictHosts": [
                "A53_0",
                "A53_1",
                "A53_2",
                "A53_3"
            ]
        }
    ]
```

when assigning RESASG_SUBTYPE_IR_OUTPUT for A53, resource range from 6 to 4 nos
is a valid range. Adding this JSON entry will ensure that the tool can take care
of the custom range allocation

Similarly search for table's name ending with "Interrupt Destinations" in
interrupt_cfg.rst file mentioned in the above. These includes
DMASS0_INTAGGR_0 Interrupt Aggregator Virtual Interrupt Destinations,
SA3_SS0_INTAGGR_0 Interrupt Aggregator Virtual Interrupt Destinations etc.
These table represent resources related to  Virtual Interrupt. Do the same
procedure for these resources also as mentioned in the above paragraph.

***

## Adding package to TIREX server

1. Run the `package.sh` script.
   1. To package data for all SoCs -

        ```bash
        .meta/scripts/package.sh
        ```

   2. To package data for some SoCs -

        ```bash
        .meta/scripts/package.sh <soc1> <soc2> <soc3> ...
        ```

   3. The script will update the package name in handoff.json file as well.
2. Subscribe to the [`k3-respart-handoff`](<https://list.ti.com/List/ViewList?ListName=k3-respart-handoff>) mailing list to get updates about the handoff process.
3. Run the below command for handoff to **DEVELOPMENT** Server -

    ```bash
    ~/ti/ccs1281/ccs/ccs_base/cloudagent/node ~/ti/ccs1281/ccs/tirex4/ti-rex-core/scripts/tirex-scripts.js handoff -f handoff.json -u http://tgrex19.toro.design.ti.com/tirex4-handoff
    ```

4. Run the below command for handoff to **PRODUCTION** Server -

    ```bash
    ~/ti/ccs1281/ccs/ccs_base/cloudagent/node ~/ti/ccs1281/ccs/tirex4/ti-rex-core/scripts/tirex-scripts.js handoff -f handoff.json -u http://tirex-bu-handoff.toro.design.ti.com/tirex4-handoff
    ```

## Updating User's Guide on TIREX Server

If the User's Guide on TIREX server needs modification, the follow the below steps:

1. Clone Processor Hardware Metadata repository inside the `ti` folder.

    ```bash
    git clone ssh://git@bitbucket.itg.ti.com/shm/processors-hardware-metadata.git
    cd processors-hardware-metadata
    ```

2. Update the User's Guide file present inside `processors-utilities` directory.
3. Create a commit and a pull request for the change.
4. Once the pull request is
   2. Remove the second entry for `processors-devices.zip`. Only keep the first entry.
   3. Change the email to `k3-respart-handoff@list.ti.com`. merged, create a zip file of `processors-utilities` directory.
5. Update the handoff.json file present at the root to only submit `processors-utilities` package.
   1. To simply this step, copy the Resource Partitioning Tool's handoff.json file to the root and make required modifications like -
      1. Update the zip path to the path of `processors-utilities.zip`.
      2. If required, update the checklist, otherwise leave them as they are.
6. Run the below command for handoff to **DEVELOPMENT** Server -

    ```bash
    ~/ti/ccs1281/ccs/ccs_base/cloudagent/node ~/ti/ccs1281/ccs/tirex4/ti-rex-core/scripts/tirex-scripts.js handoff -f handoff.json -u http://tgrex19.toro.design.ti.com/tirex4-handoff
    ```

7. Run the below command for handoff to **PRODUCTION** Server -

    ```bash
    ~/ti/ccs1281/ccs/ccs_base/cloudagent/node ~/ti/ccs1281/ccs/tirex4/ti-rex-core/scripts/tirex-scripts.js handoff -f handoff.json -u http://tirex-bu-handoff.toro.design.ti.com/tirex4-handoff

## Removing package from TIREX Server

e.g. removing a specific version:

```bash
~/ti/ccs1281/ccs/ccs_base/cloudagent/node ~/ti/ccs1281/ccs/tirex4/ti-rex-core/scripts/tirex-scripts.js remove-package --id K3-RESOURCE-CONFIGURATION --package-version 1.0.0 -u http://tirex-bu-handoff.toro.design.ti.com/tirex4-handoff -e k3-respart-handoff@list.ti.com
```

e.g. removing all versions:

```bash
~/ti/ccs1281/ccs/ccs_base/cloudagent/node ~/ti/ccs1281/ccs/tirex4/ti-rex-core/scripts/tirex-scripts.js remove-package --id K3-RESOURCE-CONFIGURATION --package-version all -u http://tirex-bu-handoff.toro.design.ti.com/tirex4-handoff -e k3-respart-handoff@list.ti.com
```
