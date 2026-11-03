#ifdef WIN32
uint8_t staticRefInCase9[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase9[] =
#endif
     {
        66, 23, 172,
        100, 234, 146,
        133, 10, 224,

     };

#ifdef WIN32
uint8_t staticRefOutCase9[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase9[] =
#endif
     {
        130,

     };
