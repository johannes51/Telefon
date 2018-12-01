#ifndef LOG_H
#define LOG_H

#include <Arduino.h>

extern void log(const char* out);
extern void log(String out);
extern void logLn(const char* out);
extern void logLn(String out);

#endif // LOG_H