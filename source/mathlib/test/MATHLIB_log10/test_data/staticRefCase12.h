#ifdef WIN32
double staticRefInCase12[] =
#else
__attribute__((section (".staticData")))
     static double staticRefInCase12[] =
#endif
     {
        8195.839918014608,
     };

#ifdef WIN32
double staticRefOutCase12[] =
#else
__attribute__((section (".staticData")))
     static double staticRefOutCase12[] =
#endif
     {
        3.9135934671276607,
     };
