#ifdef WIN32
uint8_t staticRefInCase22[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase22[] =
#endif
     {
        129, 97, 78, 252, 219,
        173, 248, 62, 224, 1,
        73, 123, 113, 216, 1,
        190, 0, 38, 145, 65,
        41, 155, 105, 24, 246,

     };

#ifdef WIN32
uint8_t staticRefOutCase22[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase22[] =
#endif
     {
        119,

     };
