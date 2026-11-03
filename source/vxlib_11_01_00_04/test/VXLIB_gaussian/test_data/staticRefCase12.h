#ifdef WIN32
uint8_t staticRefInCase12[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase12[] =
#endif
     {
        148, 191, 54,
        3, 252, 195,
        181, 20, 18,
        227, 45, 73,
        81, 242, 236,
        246, 142, 199,
        12, 155, 110,
        192, 47, 196,
        201, 5, 172,
        92, 237, 42,
        103, 177, 21,
        106, 7, 73,
        164, 202, 251,
        136, 112, 246,
        111, 110, 218,
        174, 75, 18,

     };

#ifdef WIN32
uint8_t staticRefOutCase12[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase12[] =
#endif
     {
        139,
        98,
        113,
        170,
        168,
        129,
        111,
        116,
        129,
        109,
        105,
        152,
        161,
        127,

     };
