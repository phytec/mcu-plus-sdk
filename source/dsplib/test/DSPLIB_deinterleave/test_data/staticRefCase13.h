#ifdef WIN32
int16_t staticRefInCase13[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefInCase13[] =
#endif
     {
        -15675, -12984,

     };

#ifdef WIN32
int16_t staticRefOutCase13[] =
#else
__attribute__((section (".staticData")))
     static int16_t staticRefOutCase13[] =
#endif
     {
        -15675,
        -12984,

     };
