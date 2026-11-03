#ifdef WIN32
uint8_t staticRefInCase42[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase42[] =
#endif
     {
        188, 116, 93, 232, 107, 81, 148, 193, 128,
        71, 218, 160, 145, 71, 206, 213, 238, 191,
        70, 209, 4, 103, 47, 29, 27, 131, 93,
        223, 146, 95, 43, 66, 65, 137, 170, 19,
        246, 233, 30, 43, 225, 170, 12, 33, 57,
        10, 208, 207, 206, 79, 51, 36, 98, 201,
        189, 120, 179, 2, 104, 159, 5, 78, 210,
        207, 189, 170, 1, 212, 62, 100, 215, 99,
        186, 55, 253, 62, 26, 217, 244, 3, 249,

     };

#ifdef WIN32
int16_t staticRefFilterCase42[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefFilterCase42[] =
#endif
     {
        0, -1, 1, 2, 0, 2, -1,
        1, -1, 0, 1, 1, 1, 0,
        0, 0, -1, 0, 1, -1, 0,
        -1, 1, 2, 0, -1, -1, 1,
        1, 0, 0, -1, 2, 0, 0,
        -1, 0, 1, -1, 0, 1, -1,
        2, 0, 0, -1, -1, 0, -1,

     };

#ifdef WIN32
int16_t staticRefOutCase42[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefOutCase42[] =
#endif
     {
        -7, 36, 32,
        42, 37, -4,
        -10, 1, 35,

     };
