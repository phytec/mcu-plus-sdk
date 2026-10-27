
let common = system.getScript("/common");

const driverVer = {
    "hsmclient": {
        version: "v0",
    }
};

const topModules_main = [
];

const topModules_mcu = [

];

function getCpuID() {
    let corename_map = {
        "CPU1" : "C29_CPU_1",
        "CPU2" : "C29_CPU_2",
        "CPU3" : "C29_CPU_3",
    };
    if(common.getSelfSysCfgCoreName().includes("hsm")) {
            corename_map = system.getScript(`/imports/drivers/soc/drivers_${common.getSocName()}_hsm.syscfg.js`).corename_map_hsm;
        }

    return corename_map[common.getSelfSysCfgCoreName()];
}

function getSelfCoreID() {
    let corename_map = {
        "CPU1" : "C29_CPU_1",
        "CPU2" : "C29_CPU_2",
        "CPU3" : "C29_CPU_3",
    };

    return corename_map[common.getSelfSysCfgCoreName()];
}

exports = {
    getTopModules: function() {

        let topModules = topModules_main;

        if(common.getSelfSysCfgCoreName().includes("hsm")) {
            topModules = topModules_mcu;
        }

        return topModules;
    },
    getDriverVer: function(driverName) {
        return driverVer[driverName].version;
    },
    getCpuID,
    getSelfCoreID,
};