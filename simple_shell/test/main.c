#include "main.h"
/**
 *main - Entry Point
 *Description: Creat own simple shell
 *Return: (0) always success
 */

int main(void)
{
	char *prompt = "#cisfun$ ";
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t nreads;
	char **argv;
	while (1)
	{
		_puts(prompt);
		nreads = getline(&lineptr, &n, stdin);

		if (nreads == -1)
		{
			return (-1);
		}
	argv = _strcut(lineptr);
 	_exce(argv);
	}
	return (0);
}
