#ifdef WIN32
int16_t staticRefInpCase25[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefInpCase25[] =
#endif
     {
        -11605, -9216, -29258, -23994,
        1748, 17740, 21218, -29424,
        -31938, -17833, 10018, 1455,
        -18301, 485, -29218, 1270,

     };

#ifdef WIN32
int16_t staticRefOutCase25[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefOutCase25[] =
#endif
     {
        0, 0, 0, 0,
        1, 1, 1, 0,
        0, 0, 1, 1,
        0, 1, 0, 1,

     };
