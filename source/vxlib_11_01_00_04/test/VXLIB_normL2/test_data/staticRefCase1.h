#ifdef WIN32
int8_t staticRefIn0Case1[] =
#else
__attribute__((section (".staticData")))
     static int8_t staticRefIn0Case1[] =
#endif
     {
        90, -30, 22,
        -104, -120, 23,
        5, -114, 72,

     };

#ifdef WIN32
int8_t staticRefIn1Case1[] =
#else
__attribute__((section (".staticData")))
     static int8_t staticRefIn1Case1[] =
#endif
     {
        30, -45, 82,
        -70, -37, -8,
        -48, -108, 21,

     };

#ifdef WIN32
uint8_t staticRefOutCase1[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase1[] =
#endif
     {
        95, 54, 85,
        125, 126, 24,
        48, 157, 75,

     };
