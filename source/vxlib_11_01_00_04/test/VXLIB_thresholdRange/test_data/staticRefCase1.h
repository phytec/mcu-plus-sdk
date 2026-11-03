#ifdef WIN32
uint8_t staticRefInpCase1[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInpCase1[] =
#endif
     {
        238, 128, 192, 235,
        190, 175, 151, 185,
        168, 24, 171, 20,
        182, 89, 242, 141,

     };

#ifdef WIN32
uint8_t staticRefOutCase1[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase1[] =
#endif
     {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,

     };
