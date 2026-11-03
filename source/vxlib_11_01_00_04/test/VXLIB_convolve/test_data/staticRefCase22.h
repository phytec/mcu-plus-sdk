#ifdef WIN32
uint8_t staticRefInCase22[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase22[] =
#endif
     {
        181, 4, 128, 19, 65,
        189, 41, 78, 196, 110,
        6, 66, 142, 138, 32,
        65, 144, 91, 254, 220,
        141, 113, 219, 60, 243,
        20, 83, 127, 120, 203,
        70, 37, 199, 184, 215,
        94, 218, 145, 136, 67,
        7, 138, 168, 41, 145,

     };

#ifdef WIN32
int16_t staticRefFilterCase22[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefFilterCase22[] =
#endif
     {
        -1, 1, -1, 1, -1,
        0, 1, 2, 0, 1,
        2, 0, -1, -1, 2,
        2, 2, 1, 1, -1,
        1, 0, 1, 0, -1,

     };

#ifdef WIN32
uint8_t staticRefOutCase22[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase22[] =
#endif
     {
        30,
        85,
        115,
        123,
        116,

     };
