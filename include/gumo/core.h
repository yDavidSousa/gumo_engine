#pragma once

#define bool int
#define true 1
#define false 0

#ifdef GM_PLATFORM_WINDOWS
    #ifdef GM_BUILD_DLL
        #define GUMO_API __declspec(dllexport)
    #else
        #define GUMO_API __declspec(dllimport)
    #endif
#else
    #error Gumo only support Windows!
#endif