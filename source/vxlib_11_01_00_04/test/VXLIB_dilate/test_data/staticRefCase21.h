#ifdef WIN32
uint16_t staticRefInCase21[] =
#else
__attribute__((section (".staticData")))
     static uint16_t staticRefInCase21[] =
#endif
     {
        3130, 45808, 60174, 27205, 36460,
        22779, 23758, 3328, 60078, 53619,
        63956, 24874, 22403, 56242, 3066,
        30421, 5359, 58456, 25398, 45963,
        42600, 62378, 28540, 52697, 2564,

     };

#ifdef WIN32
uint16_t staticRefOutCase21[] =
#else
__attribute__((section (".staticData")))
     static uint16_t staticRefOutCase21[] =
#endif
     {
        63956, 60174, 60174,
        63956, 60078, 60078,
        63956, 62378, 58456,

     };
