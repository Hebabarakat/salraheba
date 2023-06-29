#include "main.h"


int my_strncmp(const char *s1, const char *s2, size_t n) {
    size_t i;
    for (i = 0; i < n && s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
    }
    if (i == n) {
        return 0;
    }
    return s1[i] - s2[i];
}

char *my_getenv(const char *name) {
    char *value = NULL;
    int i;
    for (i = 0; environ[i] != NULL; i++) {
        if (my_strncmp(name, environ[i], strlen(name)) == 0) {
            value = environ[i] + strlen(name) + 1;
            break;
        }
    }
    return value;
}

