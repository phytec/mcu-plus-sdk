#ifdef WIN32
uint8_t staticRefInCase1[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase1[] =
#endif
     {
        45, 74, 253, 58, 6,
        188, 69, 245, 52, 155,
        226, 214, 17, 181, 85,
        75, 208, 68, 35, 21,
        21, 141, 85, 154, 135,

     };

#ifdef WIN32
uint8_t staticRefOutCase1[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase1[] =
#endif
     {
        253, 253, 253,
        245, 245, 245,
        226, 214, 181,

     };
