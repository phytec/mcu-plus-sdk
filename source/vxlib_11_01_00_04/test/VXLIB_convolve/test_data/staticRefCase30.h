#ifdef WIN32
uint8_t staticRefInCase30[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase30[] =
#endif
     {
        148, 32, 174, 77, 9,
        71, 25, 245, 147, 174,
        53, 122, 86, 250, 93,
        103, 73, 146, 85, 30,
        125, 144, 33, 186, 94,
        48, 122, 160, 66, 112,
        130, 179, 39, 104, 166,
        131, 254, 202, 194, 249,
        151, 108, 237, 29, 83,

     };

#ifdef WIN32
int16_t staticRefFilterCase30[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefFilterCase30[] =
#endif
     {
        2, 1, -1, -1, 0,
        -1, 1, 0, -1, 2,
        2, 0, 2, -1, -1,
        0, 0, 0, 1, 0,
        0, 0, 2, 1, 2,

     };

#ifdef WIN32
int16_t staticRefOutCase30[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefOutCase30[] =
#endif
     {
        79,
        72,
        37,
        84,
        30,

     };
