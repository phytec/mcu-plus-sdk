#ifdef WIN32
int8_t staticRefInpCase9[] =
#else
__attribute__((section (".staticData")))
     static int8_t staticRefInpCase9[] =
#endif
     {
        39, -8, -39, 0,
        40, 41, -19, -46,
        -11, 100, -105, -76,
        -57, -71, -31, 74,

     };

#ifdef WIN32
int8_t staticRefOutCase9[] =
#else
__attribute__((section (".staticData")))
     static int8_t staticRefOutCase9[] =
#endif
     {
        24, 24, 24, 24,
        40, 40, 24, 24,
        24, 24, 24, 24,
        24, 24, 24, 40,

     };
