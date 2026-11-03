#ifdef WIN32
uint8_t staticRefInCase17[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase17[] =
#endif
     {
        28, 79, 72, 14, 168, 149, 33,
        216, 198, 196, 74, 11, 61, 210,
        141, 45, 226, 128, 103, 13, 184,
        37, 52, 47, 245, 213, 121, 106,
        147, 29, 197, 181, 154, 77, 240,
        214, 222, 104, 122, 10, 231, 91,
        31, 6, 169, 112, 178, 21, 201,

     };

#ifdef WIN32
int16_t staticRefFilterCase17[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefFilterCase17[] =
#endif
     {
        0, 0, 1, 1, 0,
        -1, 1, 0, 0, 0,
        -1, -1, 0, -1, 2,
        -1, 2, 0, -1, 0,
        0, 1, 0, 0, 0,

     };

#ifdef WIN32
uint8_t staticRefOutCase17[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase17[] =
#endif
     {
        13, 9, 29,
        6, 0, 0,
        35, 3, 14,

     };
