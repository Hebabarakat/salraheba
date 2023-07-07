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
pid_t pid;
char **token;

char prompt[] = "$ ";
char *lineptr = NULL;

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

token = split_line(lineptr);
pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
execve(token[0], token, NULL);

/* If execve returns, an error occured */
perror(token[0]);
exit(EXIT_FAILURE);
}
else
{
wait(NULL);
}
free(token);
}
free(lineptr);
lineptr = NULL;

return (0);
}
