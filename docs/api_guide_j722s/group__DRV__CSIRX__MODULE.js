var group__DRV__CSIRX__MODULE =
[
    [ "CSIRX Capture API", "group__CSIRX__PRIV__CAPTURE__API.html", "group__CSIRX__PRIV__CAPTURE__API" ],
    [ "CSIRX Driver Configurations", "group__DRV__CSIRX__CFG__MODULE.html", "group__DRV__CSIRX__CFG__MODULE" ],
    [ "CSIRX Driver Event API", "group__DRV__CSIRX__EVENT__MODULE.html", "group__DRV__CSIRX__EVENT__MODULE" ],
    [ "CSIRX Driver Header", "group__CSIRX__TOP__LEVEL.html", "group__CSIRX__TOP__LEVEL" ],
    [ "CSIRX SoC Config", "group__DRV__CSIRX__SOC__MODULE.html", "group__DRV__CSIRX__SOC__MODULE" ],
    [ "CSIRX private APIs", "group__DRV__CSIRX__PRIV__APIS.html", "group__DRV__CSIRX__PRIV__APIS" ],
    [ "UDMA Capture API", "group__CSIRX__UDMA__API.html", "group__CSIRX__UDMA__API" ],
    [ "Csirx_ChCfg", "structCsirx__ChCfg.html", [
      [ "chId", "structCsirx__ChCfg.html#aecc683bb04ebaec9b1b7c7f71667c174", null ],
      [ "chType", "structCsirx__ChCfg.html#a52e0a92680fdedd10b90bc4ed174f007", null ],
      [ "vcNum", "structCsirx__ChCfg.html#aa2e5390af10cab49ce51956cc414b15e", null ],
      [ "inCsiDataType", "structCsirx__ChCfg.html#ad1dc65bf79208995e0836b36b2916183", null ],
      [ "outFmt", "structCsirx__ChCfg.html#a6e1e67b116b6e0e1717d2d3337e621f7", null ],
      [ "rxChParams", "structCsirx__ChCfg.html#a5c23b4a457e65207b2be512607d347bc", null ],
      [ "ringOrderId", "structCsirx__ChCfg.html#ac03607f2a78b8b6519ce108bb9b36736", null ]
    ] ],
    [ "Csirx_InstCfg", "structCsirx__InstCfg.html", [
      [ "enableCsiv2p0Support", "structCsirx__InstCfg.html#a81e3ff298134a649566472875782d01c", null ],
      [ "numDataLanes", "structCsirx__InstCfg.html#a9b88885a9239e27c1c7d134faa064d2b", null ],
      [ "dataLanesMap", "structCsirx__InstCfg.html#ae1df4892752280bfef03a73a498649e7", null ],
      [ "enableErrbypass", "structCsirx__InstCfg.html#aa122fcf2f0b7e7844265bb015c3c7565", null ],
      [ "numPixelsStrm0", "structCsirx__InstCfg.html#a1188a252c04f56ecdc65d0ab07a6ee0f", null ],
      [ "enableStrm", "structCsirx__InstCfg.html#ab0a9393e7c845de793dc7e09be79e67a", null ]
    ] ],
    [ "Csirx_CreateParams", "structCsirx__CreateParams.html", [
      [ "numCh", "structCsirx__CreateParams.html#a87533b222d60a3f016906a3d5ad2408b", null ],
      [ "chCfg", "structCsirx__CreateParams.html#a86c69b4aa069129c0bd41a5e6480f723", null ],
      [ "instCfg", "structCsirx__CreateParams.html#a7956841051b05a5c3ac7620f9cd123a8", null ],
      [ "frameDropBuf", "structCsirx__CreateParams.html#a663bba1ea76d9d58ac70d0780d3fb21b", null ],
      [ "frameDropBufLen", "structCsirx__CreateParams.html#aa0bedb5863dd403565e87da7b90168d2", null ],
      [ "enableChDq", "structCsirx__CreateParams.html#a16d3dc26b6b3a9a87b1b6ca176624e0d", null ]
    ] ],
    [ "Csirx_InitParams", "structCsirx__InitParams.html", [
      [ "drvHandle", "structCsirx__InitParams.html#ab8bd828d484b99fef7689fa1482b75d8", null ]
    ] ],
    [ "Csirx_CreateStatus", "structCsirx__CreateStatus.html", [
      [ "retVal", "structCsirx__CreateStatus.html#a0120cb5d5904e2cb08527422fb4d1ab2", null ]
    ] ],
    [ "Csirx_InstStatus", "structCsirx__InstStatus.html", [
      [ "queueCount", "structCsirx__InstStatus.html#a522b05206493848bd64a4c03d28afe42", null ],
      [ "dequeueCount", "structCsirx__InstStatus.html#ae34354a21b1cbd3575b29b2f3cc193fd", null ],
      [ "dropCount", "structCsirx__InstStatus.html#ab1c6bfafa949eda46033bcb5dd469388", null ],
      [ "errorFrameCount", "structCsirx__InstStatus.html#a723700ea8a600636afc29e2c9fa6f28e", null ],
      [ "overflowCount", "structCsirx__InstStatus.html#a62916677070aec81ed99dda8a07248b4", null ],
      [ "spuriousUdmaIntrCount", "structCsirx__InstStatus.html#a398e97fb3652798e1116f084f959b350", null ],
      [ "frontFIFOOvflCount", "structCsirx__InstStatus.html#a8c8ae554179feb2da94d6248d2291119", null ],
      [ "crcCount", "structCsirx__InstStatus.html#a13f94b6ac99011d4d07af7b1ba081e37", null ],
      [ "eccCount", "structCsirx__InstStatus.html#ab8650f24d4db003b0cc65590389bff72", null ],
      [ "correctedEccCount", "structCsirx__InstStatus.html#a940b6682ecb3523a08adce5ee751f8fa", null ],
      [ "dataIdErrorCount", "structCsirx__InstStatus.html#a0093bd05b35ba47665f995c276aa7ec2", null ],
      [ "invalidAccessCount", "structCsirx__InstStatus.html#ae6cc444de1dd624040a771574d93a70f", null ],
      [ "invalidSpCount", "structCsirx__InstStatus.html#a41a365c06d627d19b49b2833f28dc7bd", null ],
      [ "strmFIFOOvflCount", "structCsirx__InstStatus.html#a780e89f40bed9d3b3e4731faa75fa9e5", null ],
      [ "deSkewEntryCount", "structCsirx__InstStatus.html#a7ae5e09f1b2fb3144b62214c457974e4", null ]
    ] ],
    [ "CSIRX_CH_TYPE_CAPT", "group__DRV__CSIRX__MODULE.html#ga4a2f63c204a1585e4895886309c396e2", null ],
    [ "CSIRX_CH_TYPE_OTF", "group__DRV__CSIRX__MODULE.html#gabc865186e1ae6c149d7d522a00f2f2ea", null ],
    [ "CSIRX_CH_TYPE_LPBK", "group__DRV__CSIRX__MODULE.html#gace6e1bd4e7ab72b8bd8d1f22f44527f8", null ],
    [ "CSIRX_CAPT_STREAM_ID", "group__DRV__CSIRX__MODULE.html#gac70b06c71954d22d7fcf063b414af698", null ],
    [ "CSIRX_LPBK_STREAM_ID", "group__DRV__CSIRX__MODULE.html#gab472dfe2b48a962b99cd6330898f0665", null ],
    [ "CSIRX_OTF_STREAM0_ID", "group__DRV__CSIRX__MODULE.html#gaa5a0abfd7aad5a93388d5241fbb0a790", null ],
    [ "CSIRX_OTF_STREAM1_ID", "group__DRV__CSIRX__MODULE.html#ga27d0eb71c6d17060c1f77c883cbe982e", null ],
    [ "CSIRX_BUF_ALIGNMENT", "group__DRV__CSIRX__MODULE.html#ga1120d6c7adf45a37b644ad2404e13bc6", null ],
    [ "Csirx_init", "group__DRV__CSIRX__MODULE.html#ga1f902abaf04da77eb41b3c7e2c7e3169", null ],
    [ "Csirx_deInit", "group__DRV__CSIRX__MODULE.html#ga440e96acc7f11e41498b2f6d699a6cf7", null ],
    [ "Csirx_initParamsInit", "group__DRV__CSIRX__MODULE.html#ga347c2266aedf842446bbe5c3014a617e", null ],
    [ "Csirx_createParamsInit", "group__DRV__CSIRX__MODULE.html#ga82815b7817b30c02d496e9a2831fc955", null ],
    [ "Csirx_chCfgInit", "group__DRV__CSIRX__MODULE.html#gaf898d6c69399973871dd09a24c351d86", null ],
    [ "Csirx_instCfgInit", "group__DRV__CSIRX__MODULE.html#ga9fcc9476cc789e35b32539bc46ed8e75", null ],
    [ "Csirx_instStatusInit", "group__DRV__CSIRX__MODULE.html#gac3e4a8331b7a530360f49b7c77538163", null ]
];