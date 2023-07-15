#include "main.h"

/**
 * _env: Implement the env built-in, that prints the current environment
*/

void _env(void)
{
int i;
for (i = 0; environ[i] != NULL; i++)
{
puts(environ[i]);
}
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
