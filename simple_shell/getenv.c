#include "main.h"
#include <unistd.h>

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 *
 *
 *
 *
 */
void _puts(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		_putchar(str[i]);
	}
		_putchar('\n');
}
/**
 * _env: Implement the env built-in, that prints the current environment
*/

void _env(void)
{
int i;
for (i = 0; environ[i] != NULL; i++)
{
_puts(environ[i]);
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
    	if (_strcmp((char *)name, token) == 0)
       	{
            return (strtok(NULL,"\n"));
        }

	i++;
    }

    return (NULL);
}

