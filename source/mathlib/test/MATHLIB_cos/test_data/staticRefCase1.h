#ifdef WIN32
float staticRefInCase1[] =
#else
__attribute__((section (".staticData")))
     static float staticRefInCase1[] =
#endif
     {
        -1.5707963267948966,
     };

#ifdef WIN32
float staticRefOutCase1[] =
#else
__attribute__((section (".staticData")))
     static float staticRefOutCase1[] =
#endif
     {
        6.123233995736766e-17,
     };
