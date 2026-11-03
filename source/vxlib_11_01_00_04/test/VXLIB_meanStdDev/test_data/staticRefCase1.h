#ifdef WIN32
uint8_t staticRefInCase1[] =
#else
__attribute__((section (".staticData")))
     static uint8_t staticRefInCase1[] =
#endif
     {
        96, 39, 53, 197, 41, 252,
        116, 243, 90, 91, 168, 132,
        113, 226, 35, 66, 7, 15,
        109, 55, 36, 164, 11, 113,
        190, 68, 70, 48, 201, 1,
        33, 31, 168, 34, 52, 46,

     };

#ifdef WIN32
uint32_t staticRefPixelsProcessedInCase1[] =
#else
__attribute__((section (".staticData")))
     static uint32_t staticRefPixelsProcessedInCase1[] =
#endif
     {
        0,
     };

#ifdef WIN32
uint32_t staticRefCurrentSumInCase1[] =
#else
__attribute__((section (".staticData")))
     static uint32_t staticRefCurrentSumInCase1[] =
#endif
     {
        0,
     };

#ifdef WIN32
uint32_t staticRefCurrentSqSumInCase1[] =
#else
__attribute__((section (".staticData")))
     static uint32_t staticRefCurrentSqSumInCase1[] =
#endif
     {
        0,
     };

#ifdef WIN32
float staticRefOut0Case1[] =
#else
__attribute__((section (".staticData")))
     static float staticRefOut0Case1[] =
#endif
     {
        94.72222137451172,
     };

#ifdef WIN32
float staticRefOut1Case1[] =
#else
__attribute__((section (".staticData")))
     static float staticRefOut1Case1[] =
#endif
     {
        70.58077239990234,
     };

#ifdef WIN32
uint32_t staticRefPixelsProcessedOutCase1[] =
#else
__attribute__((section (".staticData")))
     static uint32_t staticRefPixelsProcessedOutCase1[] =
#endif
     {
        36,
     };

#ifdef WIN32
uint32_t staticRefCurrentSumOutCase1[] =
#else
__attribute__((section (".staticData")))
     static uint32_t staticRefCurrentSumOutCase1[] =
#endif
     {
        3410,
     };

#ifdef WIN32
uint32_t staticRefCurrentSqSumOutCase1[] =
#else
__attribute__((section (".staticData")))
     static uint32_t staticRefCurrentSqSumOutCase1[] =
#endif
     {
        502342,
     };
