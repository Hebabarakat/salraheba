#include "main.h"
/**
 *
 *
 *
 */
int main(void)
{
size_t n = 0;
ssize_t nreads;
char **token;

char prompt[] = "$ ";
char *lineptr = NULL;
signal (SIGINT, handle_signal);
while (1)
{

_puts(prompt);
nreads = getline(&lineptr, &n, stdin);

if (nreads == -1)
{
perror("getline");
exit(EXIT_FAILURE);
}

/* Check if command is empty */
if (nreads == 1)
{
continue;
}

token =  _strcut(lineptr);
_exce(token);

}
free(lineptr);
lineptr = NULL;

return (0);
}
