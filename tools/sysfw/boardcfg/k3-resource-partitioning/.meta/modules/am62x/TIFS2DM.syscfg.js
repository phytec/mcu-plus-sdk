
const {createHostModule} = system.getScript("/.meta/modules/sysfwResPart.js");
const hostInfo = {
  "Description": "TIFS to DM communication",
  "Security": "Non Secure",
  "displayName": "TIFS2DM",
  "hostId": 251,
  "hostName": "TIFS2DM"
};
const modDef = createHostModule(hostInfo);
exports = modDef;
