#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
extern char **environ;
#define MAX_INPUT_LENGTH 1024
#define MAX_TOKENS 64

void tokenize(char *input, char **tokens, int *num_tokens) {
    char *token = strtok(input, " \t\n");
    *num_tokens = 0;
    while (token != NULL && *num_tokens < MAX_TOKENS) {
        tokens[*num_tokens] = token;
        ++(*num_tokens);
        token = strtok(NULL, " \t\n");
    }
    tokens[*num_tokens] = NULL;
}

void execute(char **tokens) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        char *path = getenv("PATH");
        char *dir = strtok(path, ":");
        while (dir != NULL) {
            char command[MAX_INPUT_LENGTH];
            snprintf(command, MAX_INPUT_LENGTH, "%s/%s", dir, tokens[0]);
            execve(command, tokens, environ);
            dir = strtok(NULL, ":");
        }

        fprintf(stderr, "Error: command not found\n");
        exit(EXIT_FAILURE);
    }
    else {
        waitpid(pid, NULL, 0);
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char *tokens[MAX_TOKENS];
    int num_tokens;

    while (1) {
        printf("> ");
        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            break;
        }
        tokenize(input, tokens, &num_tokens);
        if (num_tokens == 0) {
            continue;
        }
        if (strcmp(tokens[0], "exit") == 0) {
            break;
        }

        execute(tokens);
    }

    return 0;
}

