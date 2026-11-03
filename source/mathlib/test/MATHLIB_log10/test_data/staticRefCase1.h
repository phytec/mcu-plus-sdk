#ifdef WIN32
float staticRefInCase1[] =
#else
__attribute__((section (".staticData")))
     static float staticRefInCase1[] =
#endif
     {
        5909.383409805927,
     };

#ifdef WIN32
float staticRefOutCase1[] =
#else
__attribute__((section (".staticData")))
     static float staticRefOutCase1[] =
#endif
     {
        3.7715421685819854,
     };
