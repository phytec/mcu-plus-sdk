#ifdef WIN32
uint8_t staticRefInCase18[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase18[] =
#endif
     {
        106, 134, 4, 97,
        231, 108, 75, 254,
        251, 163, 127, 143,
        144, 124, 126, 48,

     };

#ifdef WIN32
uint32_t staticRefOutCase18[] =
#else
__attribute__((section (".staticData")))
     static uint32_t staticRefOutCase18[] =
#endif
     {
        1, 0, 1, 0, 1, 1, 2, 3, 3, 0, 1, 0, 0, 0, 1, 2,
     };
