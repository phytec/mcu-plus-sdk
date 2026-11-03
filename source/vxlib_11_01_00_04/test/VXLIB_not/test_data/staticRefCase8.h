#ifdef WIN32
uint8_t staticRefInCase8[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase8[] =
#endif
     {
        82, 104, 72,
        11, 81, 176,
        117, 42, 236,

     };

#ifdef WIN32
uint8_t staticRefOutCase8[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase8[] =
#endif
     {
        173, 151, 183,
        244, 174, 79,
        138, 213, 19,

     };
