#ifdef WIN32
uint8_t staticRefInpCase1[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInpCase1[] =
#endif
     {
        232, 48, 11, 253,
        190, 118, 201, 118,
        125, 87, 249, 222,
        141, 99, 50, 18,

     };

#ifdef WIN32
uint8_t staticRefOutCase1[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase1[] =
#endif
     {
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,

     };
