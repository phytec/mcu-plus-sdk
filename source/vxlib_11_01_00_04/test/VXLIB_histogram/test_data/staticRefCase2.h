#ifdef WIN32
uint8_t staticRefInCase2[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase2[] =
#endif
     {
        63, 42, 130, 8, 91, 21, 104, 132, 110, 99, 81, 113, 246, 46, 112, 134,
        207, 14, 181, 245, 27, 185, 24, 6, 80, 66, 185, 108, 155, 164, 143, 151,

     };

#ifdef WIN32
uint32_t staticRefOutCase2[] =
#else
__attribute__((section (".staticData")))
     static uint32_t staticRefOutCase2[] =
#endif
     {
        3, 3, 2, 1, 3, 1, 6, 0, 4, 2, 1, 3, 1, 0, 0, 2,
     };
