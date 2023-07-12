#include "main.h"

void _execve(char **argv)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        perror ("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        if(execve(argv[0], argv, NULL) == -1)
        {
            perror("execution");
            free(argv);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(NULL);
	printf("Command output:\n");
        fflush(stdout);
    }
}

char ** strcut (char *lineptr)
{
    char **argv;
    int argc, i;
    char *token;

    #define MAX_ARGS 10

    argc = MAX_ARGS;
    i = 0;
    argv = NULL;
    argv = malloc(sizeof(char*) * argc);
    if (argv == NULL)
    {
        perror ("argv");
        exit(EXIT_FAILURE);
    }
    token = strtok(lineptr, DELMITER);
    while(token && i < MAX_ARGS)
    {
        argv[i] = token;
        i++;
        token = strtok(NULL, DELMITER);
    }
    argv[i] = NULL;
    return(argv);
}

void non_interactive(const char *filename)
{
    char *lineptr;
    size_t n;
    char **token;
    FILE *file;
    ssize_t nreads;

    n = 0;
    lineptr = NULL;
    file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open file '%s': %s\n", filename, strerror(errno));
        exit(EXIT_FAILURE);
    }
    nreads = getline(&lineptr, &n, file);
    while (nreads != -1)
    {
        token = strcut(lineptr);
        if (token == NULL)
        {
            perror ("token");
            exit (EXIT_FAILURE);
        }
        _execve(token);
        free(token);
        nreads = getline(&lineptr, &n, file);
    }
    free(lineptr);
    fclose(file);
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        non_interactive(argv[1]);
    }

    return 0;
}
