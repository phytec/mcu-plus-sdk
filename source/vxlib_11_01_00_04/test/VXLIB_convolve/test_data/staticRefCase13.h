#ifdef WIN32
uint8_t staticRefInCase13[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase13[] =
#endif
     {
        230, 164, 131, 81, 21,
        103, 31, 58, 102, 117,
        181, 109, 15, 157, 146,
        37, 16, 245, 110, 217,
        141, 35, 157, 187, 127,
        186, 88, 172, 6, 33,
        241, 242, 149, 89, 87,
        191, 61, 16, 164, 20,
        15, 165, 45, 159, 252,

     };

#ifdef WIN32
int16_t staticRefFilterCase13[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefFilterCase13[] =
#endif
     {
        1, 0, 0,
        0, 1, 0,
        0, -1, 0,

     };

#ifdef WIN32
int16_t staticRefOutCase13[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefOutCase13[] =
#endif
     {
        -8, 5, 10,
        20, 4, 17,
        4, 26, 5,
        11, -6, 6,
        12, 6, -6,
        10, 8, 6,
        -9, 1, 20,

     };
