#ifndef GUMO_ENGINE_LOGGER_H
#define GUMO_ENGINE_LOGGER_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

typedef enum
{
    LEVEL_TRACE,
    LEVEL_DEBUG,
    LEVEL_INFO,
    LEVEL_WARNING,
    LEVEL_ERROR,
    LEVEL_CRITICAL
} log_level_t;

#define GM_LOG_TRACE(...) log_format(LEVEL_TRACE, __VA_ARGS__)
#define GM_LOG_DEBUG(...) log_format(LEVEL_DEBUG, __VA_ARGS__)
#define GM_LOG_INFO(...) log_format(LEVEL_INFO, __VA_ARGS__)
#define GM_LOG_WARNING(...) log_format(LEVEL_WARNING, __VA_ARGS__)
#define GM_LOG_ERROR(...) log_format(LEVEL_ERROR, __VA_ARGS__)
#define GM_LOG_CRITICAL(...) log_format(LEVEL_CRITICAL, __VA_ARGS__)

#define GM_CORE_CRITICAL(...) log_file_line(LEVEL_CRITICAL, __FILE__, __LINE__, __VA_ARGS__)

void log_format(log_level_t level, const char* _format, ...);
void log_file_line(log_level_t level, const char *file, int line, const char* _format, ...);

#endif //GUMO_ENGINE_LOGGER_H