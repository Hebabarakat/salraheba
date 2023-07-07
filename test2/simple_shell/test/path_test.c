#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
extern char **environ;
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
    char *path_env = getenv("PATH");
    char *path_dir;
	int found;
    while (1)
    {
        argc = 0;
        i = 0;
        free(argv);
        free(line_copy);

        printf("%s",prompt);
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

        found = 0;
        path_dir = strtok(path_env, ":");
        while (path_dir != NULL)
        {
            char *path = malloc(strlen(path_dir) + strlen(argv[0]) + 2);
            sprintf(path, "%s/%s", path_dir, argv[0]);
            if (access(path, X_OK) == 0)
            {
                argv[0] = path;
                found = 1;
                break;
            }
            free(path);
            path_dir = strtok(NULL, ":");
        }

        if (!found)
        {
            fprintf(stderr, "%s: command not found\n", argv[0]);
            continue;
        }

        pid = fork();
        if (pid == -1)
            return -1;
        if (pid == 0)
        {
            if (execve(argv[0], argv, environ) < -1)
            {
                perror(argv[0]);
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
