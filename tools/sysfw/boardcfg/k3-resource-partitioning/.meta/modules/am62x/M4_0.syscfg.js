
const {createHostModule} = system.getScript("/.meta/modules/sysfwResPart.js");
const hostInfo = {
  "Description": "M4",
  "Security": "Non Secure",
  "displayName": "M4 host",
  "hostId": 30,
  "hostName": "M4_0",
  "privId": 100
};
const modDef = createHostModule(hostInfo);
exports = modDef;
