#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    char *prompt = "#cisfun$ ";
    char *lineptr = NULL;
    size_t n = 0;
    ssize_t nreads;
    char **argv = NULL;
    pid_t pid;
    char *token;
    char *line_copy = NULL;
    char *delime = " \n";
    int argc, i;
    while (1)
    {
        argc = 0;
        i = 0;
        free(argv);
        free(line_copy);

        _puts(prompt);
        nreads = getline(&lineptr, &n, stdin);

        if (nreads == -1)
        {
            return (-1);
        }

        token = strtok(lineptr, delime);
        while (token)
        {
            argc++;
            token = strtok(NULL, delime);
        }

        argv = malloc(sizeof(char *) * (argc + 1));
        if (argv == NULL)
            return -1;

        line_copy = malloc(sizeof(char) * (nreads + 1));
        if (line_copy == NULL)
            return -1;

        strcpy(line_copy, lineptr);
        token = strtok(line_copy, delime);
        while (token)
        {
            argv[i] = token;
            token = strtok(NULL, delime);
            i++;
        }
        argv[i] = NULL;

        pid = fork();
        if (pid == -1)
            return -1;
        if (pid == 0)
        {
            if (execve(argv[0], argv, environ) < -1)
            {
                perror("./shell");
                return -1;
            }
        }
        else
            wait(NULL);
    }
    free(argv);
    free(line_copy);
    free(lineptr);
    return (0);
}

