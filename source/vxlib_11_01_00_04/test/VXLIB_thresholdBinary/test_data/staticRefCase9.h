#ifdef WIN32
int8_t staticRefInpCase9[] =
#else
__attribute__((section (".staticData")))
     static int8_t staticRefInpCase9[] =
#endif
     {
        -33, 100, 82, 54,
        -21, 72, -96, -62,
        -56, 110, 36, 6,
        -78, -84, -50, 50,

     };

#ifdef WIN32
int8_t staticRefOutCase9[] =
#else
__attribute__((section (".staticData")))
     static int8_t staticRefOutCase9[] =
#endif
     {
        0, 1, 1, 1,
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 0, 1,

     };
