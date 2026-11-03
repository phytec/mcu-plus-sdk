#ifdef WIN32
int8_t staticRefIn0Case1[] =
#else
__attribute__((section (".staticData")))
     static int8_t staticRefIn0Case1[] =
#endif
     {
        44, -51, -112,
        -110, -124, -82,
        78, 107, -60,

     };

#ifdef WIN32
int8_t staticRefIn1Case1[] =
#else
__attribute__((section (".staticData")))
     static int8_t staticRefIn1Case1[] =
#endif
     {
        19, 102, -82,
        -25, 101, 16,
        -23, 42, -84,

     };

#ifdef WIN32
uint8_t staticRefOutCase1[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase1[] =
#endif
     {
        63, 153, 194,
        135, 225, 98,
        101, 149, 144,

     };
