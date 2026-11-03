#ifdef WIN32
int8_t staticRefIn0Case8[] =
#else
__attribute__((section (".staticData")))
     static int8_t staticRefIn0Case8[] =
#endif
     {
        -99, 7, 12,
        93, 103, -58,
        -85, -122, -31,

     };

#ifdef WIN32
int8_t staticRefIn1Case8[] =
#else
__attribute__((section (".staticData")))
     static int8_t staticRefIn1Case8[] =
#endif
     {
        -11, 104, -91,
        88, 89, -58,
        18, -57, -96,

     };

#ifdef WIN32
uint8_t staticRefOutCase8[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase8[] =
#endif
     {
        110, 111, 103,
        181, 192, 116,
        103, 179, 127,

     };
