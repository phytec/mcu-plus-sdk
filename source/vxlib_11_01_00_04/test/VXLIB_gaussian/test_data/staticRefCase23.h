#ifdef WIN32
uint8_t staticRefInCase23[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase23[] =
#endif
     {
        251, 20, 219, 166, 226,
        41, 219, 227, 208, 208,
        139, 122, 128, 228, 124,
        22, 229, 153, 40, 231,
        70, 162, 109, 212, 47,

     };

#ifdef WIN32
uint8_t staticRefOutCase23[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase23[] =
#endif
     {
        162,

     };
