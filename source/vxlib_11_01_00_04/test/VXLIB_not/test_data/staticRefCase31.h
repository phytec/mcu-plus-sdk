#ifdef WIN32
uint16_t staticRefInCase31[] =
#else
__attribute__((section (".staticData")))
     static uint16_t staticRefInCase31[] =
#endif
     {
        47245, 40381, 37635,
        55951, 48270, 64744,
        6779, 16204, 57662,

     };

#ifdef WIN32
uint16_t staticRefOutCase31[] =
#else
__attribute__((section (".staticData")))
     static uint16_t staticRefOutCase31[] =
#endif
     {
        18290, 25154, 27900,
        9584, 17265, 791,
        58756, 49331, 7873,

     };
