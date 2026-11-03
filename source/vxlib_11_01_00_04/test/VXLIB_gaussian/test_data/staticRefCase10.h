#ifdef WIN32
uint8_t staticRefInCase10[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase10[] =
#endif
     {
        65, 251, 245,
        168, 39, 107,
        112, 59, 1,

     };

#ifdef WIN32
uint8_t staticRefOutCase10[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase10[] =
#endif
     {
        109,

     };
