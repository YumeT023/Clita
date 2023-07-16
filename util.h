#ifndef CLITA_UTIL_H
#define CLITA_UTIL_H

#include <stddef.h>
#include <stdio.h>

char *cut(const char *s, size_t from, size_t count);

#define report_error(format, ...)                           \
    do {                                                    \
        fprintf(stderr, "Error: ");                         \
        fprintf(stderr, format __VA_OPT__(, ) __VA_ARGS__); \
        fprintf(stderr, "\n");                              \
        exit(1);                                            \
    } while (0)

#endif//CLITA_UTIL_H
