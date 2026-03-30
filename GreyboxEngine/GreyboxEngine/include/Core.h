#pragma once

#ifdef GBE_PLATFORM_WINDOWS
    #ifdef GBE_BUILD_DLL
        #define GBE_API __declspec(dllexport)
    #else
        #define GBE_API __declspec(dllimport)
    #endif
#else
    #error Greybox Engine only supports windows :(
#endif