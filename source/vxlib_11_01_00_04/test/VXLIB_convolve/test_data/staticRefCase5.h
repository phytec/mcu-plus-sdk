#ifdef WIN32
uint8_t staticRefInCase5[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase5[] =
#endif
     {
        4, 231, 24, 192, 121,
        25, 17, 175, 14, 143,
        105, 119, 246, 80, 14,
        22, 6, 57, 226, 74,
        126, 204, 195, 113, 219,
        94, 97, 254, 240, 121,
        54, 76, 174, 179, 120,
        59, 226, 197, 63, 88,
        199, 154, 164, 166, 87,

     };

#ifdef WIN32
int16_t staticRefFilterCase5[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefFilterCase5[] =
#endif
     {
        -1, 2, -1,
        1, 0, 2,
        2, 1, 2,

     };

#ifdef WIN32
uint8_t staticRefOutCase5[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase5[] =
#endif
     {
        24, 75, 54,
        50, 27, 92,
        63, 59, 37,
        28, 75, 75,
        75, 84, 102,
        79, 85, 81,
        49, 75, 83,

     };
