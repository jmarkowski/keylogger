#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <syslog.h>

#include "common.h"
#include "logging.h"

static bool is_open = false;

static void log_do(int priority, const char *fmt, va_list ap);

static void log_open(void)
{
    if (!is_open) {
        const char *ident = cmd_args->cmd_name;
        int option = LOG_CONS | LOG_PID;
        int facility = LOG_DAEMON;

        int logmask = LOG_MASK(LOG_ERR)
                    | LOG_MASK(LOG_WARNING)
                    | LOG_MASK(LOG_INFO)
                    | LOG_MASK(LOG_DEBUG);

        setlogmask(logmask);

        openlog(ident, option, facility);

        is_open = true;
    }
}

static void log_close(void)
{
    closelog();

    is_open = false;
}

static void log_info(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_do(LOG_INFO, fmt, ap);
    va_end(ap);
}

static void log_debug(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_do(LOG_DEBUG, fmt, ap);
    va_end(ap);
}

static void log_warn(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_do(LOG_WARNING, fmt, ap);
    va_end(ap);
}

static void log_error(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_do(LOG_ERR, fmt, ap);
    va_end(ap);
}

static void log_do(int priority, const char *fmt, va_list ap)
{
    char buf[MAX_LOG_LEN];

    log_open();

    vsnprintf(buf, MAX_LOG_LEN - 1, fmt, ap);

    syslog(priority, "%s", buf);

    if (cmd_args->debug) {
        char level_str[12];

        switch (priority) {
        case LOG_INFO:
            sprintf(level_str, "INFO");
            break;
        case LOG_DEBUG:
            sprintf(level_str, "DEBUG");
            break;
        case LOG_WARNING:
            sprintf(level_str, "WARNING");
            break;
        case LOG_ERR:
            sprintf(level_str, "ERROR");
            break;
        default:
            sprintf(level_str, "(unknown)");
            break;
        }
        printf("%s: %s\n", level_str, buf);
    }
}

klog_t klog = {
    .open = log_open,
    .close = log_close,
    .info = log_info,
    .debug = log_debug,
    .warn = log_warn,
    .error = log_error,
};
