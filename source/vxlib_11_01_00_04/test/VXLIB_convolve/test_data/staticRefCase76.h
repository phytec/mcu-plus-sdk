#ifdef WIN32
uint8_t staticRefInCase76[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase76[] =
#endif
     {
        83, 175, 95, 50, 25, 112,
        227, 45, 254, 50, 173, 195,
        162, 192, 125, 16, 210, 222,
        220, 64, 211, 252, 199, 58,
        90, 214, 229, 244, 178, 98,
        11, 197, 174, 133, 128, 29,

     };

#ifdef WIN32
int16_t staticRefFilterCase76[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefFilterCase76[] =
#endif
     {
        1, 0, -1,
        -1, 1, 2,
        0, 2, 0,
        1, 0, 1,

     };

#ifdef WIN32
int16_t staticRefOutCase76[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefOutCase76[] =
#endif
     {
        40, 88, 16, 20,
        81, 28, 55, 72,
        46, 61, 82, 68,

     };
