#ifdef WIN32
int8_t staticRefInCase61[] =
#else
__attribute__((section (".staticData")))
     static int8_t staticRefInCase61[] =
#endif
     {
        39, 69, -43, -18,
        50, -87, -110, -33,

     };

#ifdef WIN32
int8_t staticRefOutCase61[] =
#else
__attribute__((section (".staticData")))
     static int8_t staticRefOutCase61[] =
#endif
     {
        -40, -70, 42, 17,
        -51, 86, 109, 32,

     };
