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
char **token;
int i;

i = 1;
n = 0;
lineptr = NULL;
while ((nreads = getline(&lineptr,&n,stdin)) != -1)
{
if (nreads == -1)
{
perror ("nreads");
exit(EXIT_FAILURE);
}
	if(nreads == 1)
	{
		continue;
	}	
       	if (lineptr[_strlen(lineptr) - 1] == '\n')
        {
            lineptr[_strlen(lineptr) - 1] = '\0';
        }
    token = strcut(lineptr);

    if (token == NULL)
    {
   perror ("token");
   exit (EXIT_FAILURE);
    }
    if (_strcmp (token[0], "env") == 0)
    {
	    _env();
    }
    if (_strcmp (token[0],"exit") == 0)
    {
            exit(0);
    }
_execve(token, i);

}
}

