#ifdef WIN32
uint8_t staticRefInCase11[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase11[] =
#endif
     {
        122, 34, 97, 183,
        161, 43, 90, 20,
        77, 250, 196, 10,

     };

#ifdef WIN32
uint8_t staticRefOutCase11[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase11[] =
#endif
     {
        108, 96,

     };
