#include <gumo/logger.h>
#include <time.h>

#define LOG_FORMAT "[%s] %s: "
#define TIME_FORMAT "%H:%M:%S"

const char* level_names[] =
{
    "TRACE", "DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"
};

#ifdef LOG_USE_COLOR
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define COLORED_LOG_FORMAT "[%s] %s%s\x1b[0m: "

const char* level_colors[] = {
    ANSI_COLOR_BLUE, ANSI_COLOR_CYAN, ANSI_COLOR_GREEN, ANSI_COLOR_YELLOW, ANSI_COLOR_RED, ANSI_COLOR_MAGENTA
};
#endif

void log_format(log_level_t level, const char* _format, ...)
{
    time_t now;
    struct tm* calendar_time;
    char buf[16];

    time(&now);
    calendar_time = localtime(&now);

    strftime(buf, sizeof(buf), TIME_FORMAT, calendar_time);

#ifdef LOG_USE_COLOR
    fprintf(stderr, COLORED_LOG_FORMAT, buf, level_colors[level], level_names[level]);
#else
    fprintf(stderr, LOG_FORMAT, buf, level_names[level]);
#endif

    va_list args;
    va_start(args, _format);
    vfprintf(stderr, _format, args);
    va_end(args);

    fprintf(stderr, "\n");

    fflush(stderr);
}

void log_file_line(log_level_t level, const char *file, int line, const char* _format, ...)
{
    time_t now;
    struct tm* local_time;
    char buffer[16];

    time(&now);
    local_time = localtime(&now);
    strftime(buffer, sizeof(buffer), TIME_FORMAT, local_time);

    fprintf(stderr, LOG_FORMAT, buffer, level_names[level]);

    va_list args;
    va_start(args, _format);
    vfprintf(stderr, _format, args);
    va_end(args);

    fprintf(stderr, "\n%s:%d \n", file, line);

    fflush(stderr);
}