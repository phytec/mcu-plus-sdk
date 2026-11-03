// A Matrix
#ifdef WIN32
float staticRefInACase1[] =
#else
__attribute__((section (".staticData")))
     static float staticRefInACase1[] =
#endif
     {
        1.8000, -5.7200, -8.7200, -2.0600,
        6.2100, 5.1300, 2.4100, -1.2200,
        -3.9900, 5.2000, 7.7200, -4.7000,
        -5.3700, 6.6300, 7.3800, 3.6200,

     };

// B vector
#ifdef WIN32
float staticRefInBCase1[] =
#else
__attribute__((section (".staticData")))
     static float staticRefInBCase1[] =
#endif
     {
        -6.2900, 0.9800, -1.3500, -4.9700,
     };

// P Matrix
#ifdef WIN32
unsigned short staticRefOutPCase1[] =
#else
__attribute__((section (".staticData")))
     static unsigned short staticRefOutPCase1[] =
#endif
     {
        0, 1, 0, 0,
        0, 0, 0, 1,
        1, 0, 0, 0,
        0, 0, 1, 0,

     };

// L Matrix
#ifdef WIN32
float staticRefOutLCase1[] =
#else
__attribute__((section (".staticData")))
     static float staticRefOutLCase1[] =
#endif
     {
        1.0000, 0.0000, 0.0000, 0.0000,
        -0.8647, 1.0000, 0.0000, 0.0000,
        0.2899, -0.6513, 1.0000, 0.0000,
        -0.6425, 0.7678, -0.6152, 1.0000,

     };

// U Matrix
#ifdef WIN32
float staticRefOutUCase1[] =
#else
__attribute__((section (".staticData")))
     static float staticRefOutUCase1[] =
#endif
     {
        6.2100, 5.1300, 2.4100, -1.2200,
        0.0000, 11.0661, 9.4640, 2.5650,
        0.0000, 0.0000, -3.2550, -0.0359,
        0.0000, 0.0000, 0.0000, -7.4752,

     };

// X vector
#ifdef WIN32
float staticRefOutXCase1[] =
#else
__attribute__((section (".staticData")))
     static float staticRefOutXCase1[] =
#endif
     {
        1.5385, -2.9020, 2.8398, 0.4349,
     };

// invA Matrix
#ifdef WIN32
float staticRefOutInvACase1[] =
#else
__attribute__((section (".staticData")))
     static float staticRefOutInvACase1[] =
#endif
     {
        -0.1295, 0.0622, -0.0514, -0.1195,
        0.2810, 0.1543, 0.0297, 0.2506,
        -0.3063, -0.0838, 0.0015, -0.2006,
        -0.0823, -0.0196, -0.1338, 0.0491,

     };
