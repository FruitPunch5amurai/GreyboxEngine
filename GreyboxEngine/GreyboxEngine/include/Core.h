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

#ifdef GBE_ENABLE_ASSERTS
    #define GBE_ASSERT(x, ...) {if(!(x)) {GBE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define GBE_CORE_ASSERT(x, ...) {if(!(x)) {GBE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define GBE_ASSERT(x, ...)
    #define GBE_CORE_ASSERT(x, ...)
#endif