#include"main.h"
/**
 *
 *
 *
 *
*/
void non_interactive (void)
{
char *lineptr;
size_t n;
ssize_t nreads;
n = 0;
lineptr = NULL;
nreads = getline(&lineptr,&n,stdin);
 read_noninteractiv(lineptr, nreads);
}

/**
 *
 *
 *
 */
void read_noninteractiv(char *lineptr, ssize_t nreads)
{
size_t n;
char **token;

n = 0;
if (nreads == -1)
{
perror ("nreads");
exit(EXIT_FAILURE);
}
	while (nreads != -1)
{
         if (lineptr[strlen(lineptr) - 1] == '\n')
        {
            lineptr[strlen(lineptr) - 1] = '\0';
        }
    token = strcut(lineptr);

    if (token == NULL)
    {
   perror ("token");
   exit (EXIT_FAILURE);
    }
    if (strcmp (token[0],"exit") == 0)
    {
            exit(0);
    }
_execve(token);
free (lineptr);
nreads = getline(&lineptr,&n,stdin);
}
}
