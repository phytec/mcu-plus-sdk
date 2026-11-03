// A Matrix
#ifdef WIN32
double staticRefInACase37[] =
#else
__attribute__((section (".staticData")))
     static double staticRefInACase37[] =
#endif
     {
        3.6027, -3.4970, -2.6833, -5.7724,
        7.9825, 5.7314, -6.7514, 2.6078,
        -8.6299, -2.2034, -4.0505, 1.6233,
        -4.4781, -2.6962, 2.0776, 4.0278,

     };

// B vector
#ifdef WIN32
double staticRefInBCase37[] =
#else
__attribute__((section (".staticData")))
     static double staticRefInBCase37[] =
#endif
     {
        -4.4100, 2.3133, -8.7248, 8.9482,
     };

// P Matrix
#ifdef WIN32
unsigned short staticRefOutPCase37[] =
#else
__attribute__((section (".staticData")))
     static unsigned short staticRefOutPCase37[] =
#endif
     {
        0, 0, 1, 0,
        0, 1, 0, 0,
        1, 0, 0, 0,
        0, 0, 0, 1,

     };

// L Matrix
#ifdef WIN32
double staticRefOutLCase37[] =
#else
__attribute__((section (".staticData")))
     static double staticRefOutLCase37[] =
#endif
     {
        1.0000, 0.0000, 0.0000, 0.0000,
        -0.9250, 1.0000, 0.0000, 0.0000,
        -0.4175, -1.1959, 1.0000, 0.0000,
        0.5189, -0.4205, 0.0139, 1.0000,

     };

// U Matrix
#ifdef WIN32
double staticRefOutUCase37[] =
#else
__attribute__((section (".staticData")))
     static double staticRefOutUCase37[] =
#endif
     {
        -8.6299, -2.2034, -4.0505, 1.6233,
        0.0000, 3.6933, -10.4981, 4.1093,
        0.0000, 0.0000, -16.9291, -0.1803,
        0.0000, 0.0000, 0.0000, 4.9157,

     };

// X vector
#ifdef WIN32
double staticRefOutXCase37[] =
#else
__attribute__((section (".staticData")))
     static double staticRefOutXCase37[] =
#endif
     {
        1.4654, -1.6692, 0.8579, 2.2910,
     };

// invA Matrix
#ifdef WIN32
double staticRefOutInvACase37[] =
#else
__attribute__((section (".staticData")))
     static double staticRefOutInvACase37[] =
#endif
     {
        0.0692, 0.0551, -0.0872, 0.0986,
        -0.1647, -0.0239, 0.0297, -0.2325,
        -0.0590, -0.0715, -0.0897, -0.0022,
        -0.0028, 0.0822, -0.0307, 0.2034,

     };
