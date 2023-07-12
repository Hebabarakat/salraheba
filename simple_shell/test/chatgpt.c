#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 80
#define MAX_ARGS 10
#include"main.h"
char **strcut(char *lineptr);

int main(int argc, char **argv)
{
    if (argc == 2) {
        non_interactive(argv[1]);
    } else {
        char line[MAX_LINE];
        char **args;
        int status;

        while (1) {
            printf("hsh> ");
            fflush(stdout);

            if (fgets(line, MAX_LINE, stdin) == NULL) {
                break;
            }

            // tokenize input into arguments
            args = strcut(line);

            // handle built-in commands
            if (strcmp(args[0], "cd") == 0) {
                if (args[1] == NULL) {
                    chdir(getenv("HOME"));
                } else {
                    chdir(args[1]);
                }
                free(args);
                continue;
            } else if (strcmp(args[0], "exit") == 0) {
                free(args);
                break;
            }

            // fork and execute command
            pid_t pid = fork();
            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                // child process
                execvp(args[0], args);
                perror(args[0]);
                exit(EXIT_FAILURE);
            } else {
                // parent process
                wait(&status);
            }

            free(args);
        }
    }

    return 0;
}

char **strcut(char *lineptr)
{
    char **argv;
    int argc, i;
    char *token;

    argc = MAX_ARGS;
    i = 0;
    argv = NULL;
    argv = malloc(sizeof(char*) * argc);
    if (argv == NULL) {
        perror("argv");
        exit(EXIT_FAILURE);
    }

    token = strtok(lineptr, " \n");
    while (token && i < MAX_ARGS) {
        argv[i] = token;
        i++;
        token = strtok(NULL, " \n");
    }
    argv[i] = NULL;

    return argv;
}

void non_interactive(const char *filename)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        // tokenize input into arguments
        char **args = strcut(line);

        // handle built-in commands
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                chdir(getenv("HOME"));
            } else {
                chdir(args[1]);
            }
            free(args);
            continue;
        } else if (strcmp(args[0], "exit") == 0) {
            free(args);
            break;
        }

        // fork and execute command
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // child process
            execvp(args[0], args);
            perror(args[0]);
            exit(EXIT_FAILURE);
        } else {
            // parent process
            wait(NULL);
        }

        free(args);
    }

    free(line);
    fclose(fp);
}
