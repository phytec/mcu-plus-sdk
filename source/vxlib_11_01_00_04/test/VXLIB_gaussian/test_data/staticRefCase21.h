#ifdef WIN32
uint8_t staticRefInCase21[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase21[] =
#endif
     {
        77, 242, 35, 149, 105,
        133, 236, 155, 71, 12,
        152, 8, 166, 35, 233,
        81, 120, 148, 188, 130,
        86, 81, 138, 219, 173,

     };

#ifdef WIN32
uint8_t staticRefOutCase21[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase21[] =
#endif
     {
        245,

     };
