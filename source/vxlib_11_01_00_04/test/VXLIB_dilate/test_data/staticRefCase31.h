#ifdef WIN32
uint16_t staticRefInCase31[] =
#else
__attribute__((section (".staticData")))
     static uint16_t staticRefInCase31[] =
#endif
     {
        11542, 40831, 34706, 36791, 34284,
        57005, 38286, 6446, 60888, 47206,
        31686, 62215, 36959, 29799, 56851,
        47252, 56824, 9930, 4635, 49281,
        34493, 50523, 63860, 14080, 32148,

     };

#ifdef WIN32
uint16_t staticRefOutCase31[] =
#else
__attribute__((section (".staticData")))
     static uint16_t staticRefOutCase31[] =
#endif
     {
        57005, 60888, 60888,
        62215, 62215, 60888,
        62215, 62215, 56851,
        63860, 63860, 63860,

     };
