#ifdef WIN32
uint8_t staticRefInCase15[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase15[] =
#endif
     {
        222, 61, 177, 6,
        152, 134, 230, 40,

     };

#ifdef WIN32
uint8_t staticRefOutCase15[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase15[] =
#endif
     {
        33, 194, 78, 249,
        103, 121, 25, 215,

     };
