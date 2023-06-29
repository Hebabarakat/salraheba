#include "main.h"
/**
 *
 *
 *
 */
int main(int argc, char **argv)
{
/*if (isatty(STDIN_FILENO))*/
	if (argc != 2)
{
    ssize_t nreads;

    char prompt[] = "$ ";
    char *lineptr = NULL;
    size_t n = 0;
    while (1)
    {

        _puts(prompt);
        nreads = getline(&lineptr, &n, stdin);

        if (nreads == -1)
        {
            exit(EXIT_FAILURE);
        }

        /* Check if command is empty */
        if (nreads == 1)
        {
            continue;
        }

        argv = _strcut(lineptr);
        _exce(argv);
    }
    free(lineptr);
    lineptr = NULL;
}
else
{
    noninteract(argv[1]);
}
    return 0;
}
