#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <time.h>

#define LOG_DIRECTORY "logs/"

void create_log(const char *logfile, const char *message, FILE *stream);
void log_event(const char *message);
void log_error(const char *message);

#endif