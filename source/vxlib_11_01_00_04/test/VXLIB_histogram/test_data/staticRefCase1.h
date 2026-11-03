#ifdef WIN32
uint8_t staticRefInCase1[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase1[] =
#endif
     {
        70, 182, 207, 165, 221, 185, 18, 154,
        97, 168, 100, 60, 195, 208, 177, 203,

     };

#ifdef WIN32
uint32_t staticRefOutCase1[] =
#else
__attribute__((section (".staticData")))
     static uint32_t staticRefOutCase1[] =
#endif
     {
        0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 2, 3, 4, 1, 0, 0,
     };
