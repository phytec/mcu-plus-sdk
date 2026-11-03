#ifdef WIN32
uint8_t staticRefIn0Case8[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefIn0Case8[] =
#endif
     {
        80, 108, 132,
        153, 79, 187,
        80, 70, 254,

     };

#ifdef WIN32
uint8_t staticRefIn1Case8[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefIn1Case8[] =
#endif
     {
        180, 246, 69,
        228, 108, 253,
        111, 5, 186,

     };

#ifdef WIN32
uint8_t staticRefOutCase8[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefOutCase8[] =
#endif
     {
        244, 254, 197,
        253, 111, 255,
        127, 71, 254,

     };
