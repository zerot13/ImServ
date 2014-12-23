#include <stdio.h>
#include <stdarg.h>
#include <syslog.h>
#include "logger.h"

void LogInfo(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	vsyslog(LOG_INFO, format, args);
	vprintf(format, args);
	printf("\n");
	va_end(args);
}

void LogError(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	vsyslog(LOG_ERR, format, args);
	vprintf(format, args);
	printf("\n");
	va_end(args);
}
