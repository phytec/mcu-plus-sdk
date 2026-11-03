#ifdef WIN32
float staticRefInCase11[] =
#else
__attribute__((section (".staticData")))
     static float staticRefInCase11[] =
#endif
     {
        0.308655191415916, 0.7266497528126348, -0.08446669707609239, 0.48712662235343074,
           0.05711129710078455, -0.007821077519677533, 0.7633410456035059, -0.2511013271082915,
           0.09042749816654916, 0.14873381342704373,
     };

#ifdef WIN32
float staticRefOutCase11[] =
#else
__attribute__((section (".staticData")))
     static float staticRefOutCase11[] =
#endif
     {
        2147483647.0, 2147483647.0, 2147483647.0, 2147483647.0, 2147483647.0, 2147483647.0,
           2147483647.0, 2147483647.0, 2147483647.0, 2147483647.0,
     };
