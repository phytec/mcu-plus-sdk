#ifdef WIN32
uint8_t staticRefInCase26[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase26[] =
#endif
     {
        170, 226, 183, 43, 153, 95,
        5, 254, 243, 150, 178, 127,
        211, 68, 56, 220, 131, 219,
        68, 188, 233, 54, 251, 0,
        188, 193, 150, 212, 123, 234,
        61, 153, 59, 170, 196, 33,

     };

#ifdef WIN32
int16_t staticRefFilterCase26[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefFilterCase26[] =
#endif
     {
        2, 2, 1, 2, 0,
        1, 1, 1, 1, 1,
        2, -1, 0, 0, 2,
        2, 0, -1, 1, -1,
        -1, 0, 0, 1, 1,

     };

#ifdef WIN32
int16_t staticRefOutCase26[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefOutCase26[] =
#endif
     {
        191, 175,
        168, 147,

     };
