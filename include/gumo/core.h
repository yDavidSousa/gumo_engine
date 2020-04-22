#ifndef GUMO_ENGINE_CORE_H
#define GUMO_ENGINE_CORE_H

#include <gumo/logger.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0

#ifdef GM_DEBUG
#define GM_ASSERT(expression, ...) if (!(expression)) { GM_LOG_ERROR(__VA_ARGS__); exit(EXIT_FAILURE); }
#else
#define GM_ASSERT(expression, ...)
#endif

#define MEM_ALLOC(type, count) malloc(count * sizeof(type))
#define MEM_CALLOC(type, count) (type*)calloc(count, sizeof(type))
#define MEM_REALLOC(ptr, size) realloc(ptr, size)
#define MEM_FREE(ptr) free(ptr)

#ifdef GM_PLATFORM_WINDOWS
    #ifdef GM_BUILD_DLL
        #define GUMO_API __declspec(dllexport)
    #else
        #define GUMO_API __declspec(dllimport)
    #endif
#else
    #error Gumo only support Windows!
#endif

#endif //GUMO_ENGINE_CORE_H