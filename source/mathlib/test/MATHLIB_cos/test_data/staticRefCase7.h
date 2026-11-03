#ifdef WIN32
double staticRefInCase7[] =
#else
__attribute__((section (".staticData")))
     static double staticRefInCase7[] =
#endif
     {
        -1.5707963267948966,
     };

#ifdef WIN32
double staticRefOutCase7[] =
#else
__attribute__((section (".staticData")))
     static double staticRefOutCase7[] =
#endif
     {
        6.123233995736766e-17,
     };
