
let common = system.getScript("/common");

function getTimerClockSourceValue(instance) {
    let clkSelMuxValue = 0;

    return clkSelMuxValue;
}

function makeInstanceConfig() {
    let config = {};
    let staticConfigArr = getStaticConfigArr();
    let defaultInstanceIndex = getDefaultInstance();

    if(staticConfigArr.length == 0)
        return undefined;

    config.name = "instance";
    config.displayName = "Instance";
    config.description = "Select Instance";
    config.default = staticConfigArr[defaultInstanceIndex].name;
    config.options = [];

    for (let i = 0; i < staticConfigArr.length; i++) {
        let option = {};

        option.name = staticConfigArr[i].name;
        config.options.push(option);
    }

    return config;
}

function getDefaultInstance() {
    let cpu = common.getSelfSysCfgCoreName();
    let defaultInstanceMap = {
        "CPU1": 0,
        "CPU2": 1,
        "CPU3": 2,
        "hsm0-0": 0,
    }
    return defaultInstanceMap[cpu];
}

function getStaticConfigArr() {
    let cpu = common.getSelfSysCfgCoreName();
    let staticConfigArr;

    if(cpu.match(/hsm*/) || cpu.match(/m4f*/)) {
        staticConfigArr = system.getScript(`/imports/kernel/dpl/clock_${common.getSocName()}_hsm.syscfg.js`).staticConfig_m4f;

    }
    return staticConfigArr;
}

function getTimerClockSourceConfigArr() {
    let timerClockSourceConfig = system.getScript(`/imports/kernel/dpl/clock_${common.getSocName()}_hsm.syscfg.js`).timerClockSourceConfig_m4f;

    return timerClockSourceConfig;
}

function getDefaultTimerClockSourceMhz(clkSource) {
    let clkSourceHz = 0;
    let cpu = common.getSelfSysCfgCoreName();

    if(cpu.match(/hsm*/) || cpu.match(/m4f*/)) {
        clkSourceHz = system.getScript(`/imports/kernel/dpl/clock_${common.getSocName()}_hsm.syscfg.js`).defaultTimerClockSourceMhz.clkSourceHz;
        return clkSourceHz;
    }

    return clkSourceHz;
}

exports = {
    getStaticConfigArr,
    getTimerClockSourceConfigArr,
    getTimerClockSourceValue,
    getDefaultTimerClockSourceMhz,
    makeInstanceConfig,
};