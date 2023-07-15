#include "util.h"
#include <stdlib.h>
#include <string.h>

char *cut(const char *s, const size_t from, const size_t count) {
    size_t str_len = strlen(s);
    if (from < 0 || count <= 0 || from > str_len || from + count > str_len) {
        return NULL;
    }
    char *sc = malloc(count + 1);// char is 1 byte
    strncpy(sc, s + from, count);
    sc[count] = '\0';
    return sc;
}
