#include"main.h"

/**
 * execution - executes commands entered by users
 *@cp: command
 *@cmd:vector array of pointers to commands
 * Return: 0
 */
void execution(char **cp)
{
	pid_t child_pid;
	int status;
    char *command;
	char **env = environ;
    
    command = hpath(cp);

	child_pid = fork();
	if (child_pid < 0)
		perror(command);
	if (child_pid == 0)
	{
		execve(command, cp, env);
		perror(command);
		free(cp);
		exit(98);
	}
	else
		wait(&status);
    
}

/**
 *_exce - implement the excution
 *@token: pointer
 *
 */
void _exce(char** token)
{
pid_t pid;
char *command;
int val;
	pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
    command = hpath(token);

val = execve(command, token, NULL);
if (val == -1)
{
    printf("error command\n");
}
}
wait(NULL);

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
