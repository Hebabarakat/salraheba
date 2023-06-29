#include"main.h"
/**
 *_exce - implement the excution
 *@token: pointer
 *
 */
void _exce(char** token)
{
pid_t pid;
int val;
	pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
val = execve(token[0], token, NULL);
if (val == -1)
{
        if (errno == ENOENT)
        {
            fprintf(stderr, "Error: ls command not found\n");
        }
        else if (errno == EACCES)
        {
            fprintf(stderr, "Error: cannot access directory '/var'\n");
        }
        else
        {
            perror("Error executing command");
        }
        exit(EXIT_FAILURE);
}
}
else
{
wait(NULL);
}

free(token);
}

/**
 *_strcut - cut the string
 *@lineptr: pointer
 *@nreads: integer
 *Return: token always success
 */
char** _strcut(char *lineptr)
{
char *token;
int argc, i;
char **argv;

argc = 64;
i = 0;
argv = NULL;

argv = malloc(sizeof(char *) * (argc));
if (argv == NULL)
{
perror("Allocation error\n");
exit (EXIT_FAILURE);
}
token = strtok(lineptr, DELIMITER);
while (token)
{
argv[i] = token;
i++;
if (i >= argc)
{
argv = _realloc(argv, argc * sizeof(char *),(argc + 64)  * sizeof(char *));
if (argv == NULL)
{
perror("Allocation Error\n");
exit(EXIT_FAILURE);
}
}
token = strtok(NULL, DELIMITER);
}
argv[i] = NULL;
return (argv);
}
