#ifdef WIN32
uint8_t staticRefInCase11[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase11[] =
#endif
     {
        122, 31, 142, 235, 226,
        153, 130, 162, 176, 68,
        80, 1, 239, 6, 29,
        75, 227, 31, 243, 210,
        238, 14, 231, 59, 161,

     };

#ifdef WIN32
uint8_t staticRefOutCase11[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase11[] =
#endif
     {
        162, 235, 235,
        239, 239, 239,
        239, 243, 243,
        238, 243, 243,

     };
