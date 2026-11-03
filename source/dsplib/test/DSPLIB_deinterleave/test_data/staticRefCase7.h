#ifdef WIN32
float staticRefInCase7[] =
#else
__attribute__((section (".staticData")))
     static float staticRefInCase7[] =
#endif
     {
        -1.3521267492839595,

     };

#ifdef WIN32
float staticRefOutCase7[] =
#else
__attribute__((section (".staticData")))
     static float staticRefOutCase7[] =
#endif
     {
        -1.3521267492839595,

     };
