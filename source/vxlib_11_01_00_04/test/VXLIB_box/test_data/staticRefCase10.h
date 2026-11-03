#ifdef WIN32
uint8_t staticRefInCase10[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase10[] =
#endif
     {
        205, 170, 144,
        195, 39, 50,
        67, 68, 209,

     };

#ifdef WIN32
uint8_t staticRefOutCase10[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase10[] =
#endif
     {
        127,

     };
