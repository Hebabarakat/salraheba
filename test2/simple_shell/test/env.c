#include "main.h"

/**
 * _env: Implement the env built-in, that prints the current environment
*/

void _env(void)
{
int i;
for (i = 0; environ[i] != NULL; i++)
{
_puts(environ[i]);
_puts("\n");
}
