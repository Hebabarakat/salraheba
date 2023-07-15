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

char *_getenv(const char *name)
{
    int i;
    char *token;

    i = 0;
    while(environ[i])
    {
    token = strtok(environ[i],"=");
        if (strcmp(name, token) == 0)
       	{
            return (strtok(NULL,"\n"));
        }
	i++;
    }
    return (NULL);
}
