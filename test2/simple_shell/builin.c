#include "main.h"

/**
 * execution - executes commands entered by users
 *@cp: command
 *@cmd:vector array of pointers to commands
 * Return: 0
 */
/**void _exce(char **cp)
{
	int val;
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

		val = execve(command, cp, env);
		if(val == -1)
			perror(command);
	}
	else
		wait(&status); 
}*/
/* 
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

