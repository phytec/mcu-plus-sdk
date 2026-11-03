#ifdef WIN32
double staticRefInCase7[] =
#else
__attribute__((section (".staticData")))
     static double staticRefInCase7[] =
#endif
     {
        0.0,
     };

#ifdef WIN32
double staticRefOutCase7[] =
#else
__attribute__((section (".staticData")))
     static double staticRefOutCase7[] =
#endif
     {
        0.0,
     };
