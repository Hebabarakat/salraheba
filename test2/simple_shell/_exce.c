#include "main.h"
void _exce(char **cp)
{
    int val;
    pid_t child_pid;
    int status;



    child_pid = fork();
    if (child_pid < 0)
    {
        perror("Error");
        free(cp[0]);
        return;
    }
    if (child_pid == 0)
    {
        val = execve(cp[0], cp, NULL);
        if (val == -1)
        {
            perror(cp[0]);
            free(cp[0]);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(&status);
        free(cp);
    }
}
