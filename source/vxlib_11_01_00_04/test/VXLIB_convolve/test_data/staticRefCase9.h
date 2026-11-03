#ifdef WIN32
uint8_t staticRefInCase9[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase9[] =
#endif
     {
        217, 16, 97, 62, 78, 254,
        165, 140, 29, 50, 147, 65,
        39, 150, 229, 32, 25, 13,
        115, 83, 132, 226, 156, 224,
        21, 58, 243, 52, 241, 99,
        123, 19, 139, 78, 116, 105,

     };

#ifdef WIN32
int16_t staticRefFilterCase9[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefFilterCase9[] =
#endif
     {
        1, 0, -1,
        0, 1, 1,
        0, -1, 2,

     };

#ifdef WIN32
int16_t staticRefOutCase9[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefOutCase9[] =
#endif
     {
        57, -1, 0, 14,
        24, 48, 18, 0,
        21, 17, 48, 29,
        15, 24, 19, 38,

     };
