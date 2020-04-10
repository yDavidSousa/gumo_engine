#pragma once

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

enum log_level{
    TRACE, DEBUG, INFO, WARNING, ERROR, CRITICAL
};

#define GM_LOG_TRACE(...) log_format(TRACE, __VA_ARGS__)
#define GM_LOG_DEBUG(...) log_format(DEBUG, __VA_ARGS__)
#define GM_LOG_INFO(...) log_format(INFO, __VA_ARGS__)
#define GM_LOG_WARNING(...) log_format(WARNING, __VA_ARGS__)
#define GM_LOG_ERROR(...) log_format(ERROR, __VA_ARGS__)
#define GM_LOG_CRITICAL(...) log_format(CRITICAL, __VA_ARGS__)

#define GM_CORE_CRITICAL(...) log_file_line(CRITICAL, __FILE__, __LINE__, __VA_ARGS__)

void log_format(enum log_level level, const char* _format, ...);
void log_file_line(enum log_level level, const char *file, int line, const char* _format, ...);