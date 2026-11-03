#ifdef WIN32
uint8_t staticRefInCase11[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase11[] =
#endif
     {
        94, 68, 32, 131,
        172, 226, 89, 244,
        77, 71, 149, 34,

     };

#ifdef WIN32
uint8_t staticRefOutCase11[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase11[] =
#endif
     {
        108, 115,

     };
