#include "main.h"
void _exce(char **cp)
{
    int val;
    pid_t child_pid;
    int status;
    char *command;

    command = hpath(cp);
    if (command == NULL)
    {
        fprintf(stderr, "Error: Command '%s' not found in PATH\n", cp[0]);
        return;
    }


    child_pid = fork();
    if (child_pid < 0)
    {
        perror(command);
        free(command);
        return;
    }
    if (child_pid == 0)
    {
        val = execve(command, cp, NULL);
        if (val == -1)
        {
            perror(command);
            free(command);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(&status);
        free(command);
    }
}
