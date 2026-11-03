#ifdef WIN32
float staticRefInCase1[] =
#else
__attribute__((section (".staticData")))
     static float staticRefInCase1[] =
#endif
     {
        0.0,
     };

#ifdef WIN32
float staticRefOutCase1[] =
#else
__attribute__((section (".staticData")))
     static float staticRefOutCase1[] =
#endif
     {
        0.0,
     };
