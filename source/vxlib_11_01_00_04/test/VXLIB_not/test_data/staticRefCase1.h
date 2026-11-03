#ifdef WIN32
uint8_t staticRefInCase1[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase1[] =
#endif
     {
        45, 240, 189,
        231, 105, 142,
        28, 199, 232,

     };

#ifdef WIN32
uint8_t staticRefOutCase1[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase1[] =
#endif
     {
        210, 15, 66,
        24, 150, 113,
        227, 56, 23,

     };
