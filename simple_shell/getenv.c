#include "main.h"

#include <stdio.h>
#include <string.h>
int my_strncmp(const char *s1, const char *s2, size_t n);
char *my_getenv(const char *name);

int my_strncmp(const char *s1, const char *s2, size_t n) {
    int i;
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

int main() {
    char *path = my_getenv("PATH");
    if (path != NULL) {
        printf("The PATH is: %s\n", path);
    } else {
        printf("PATH not found\n");
    }
    return 0;
}


