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
char **token;
ssize_t nreads;
n = 0;
lineptr = NULL;
nreads = getline(&lineptr,&n,stdin);
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
_execve(token);
free (lineptr);
nreads = getline(&lineptr,&n,stdin);
}


}

