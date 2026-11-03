#ifdef WIN32
uint8_t staticRefInCase1[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase1[] =
#endif
     {
        131, 42, 220, 32, 18, 170,
        22, 228, 161, 105, 202, 189,
        39, 86, 200, 124, 10, 48,
        163, 20, 124, 42, 120, 149,
        105, 240, 155, 130, 32, 3,
        235, 175, 187, 151, 158, 90,

     };

#ifdef WIN32
int16_t staticRefFilterCase1[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefFilterCase1[] =
#endif
     {
        1, 1, 1,
        1, -1, -1,
        0, 2, -1,

     };

#ifdef WIN32
uint8_t staticRefOutCase1[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase1[] =
#endif
     {
        11, 32, 7, 4,
        51, 7, 1, 32,
        35, 46, 19, 3,
        17, 29, 12, 27,

     };
