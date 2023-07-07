#include "main.h"

/**
 * split_line - Splits a line of input into tokens
 * @line: The line of input to split
 *
 * Return: An array of tokens
 */
char **split_line(char *line)
{
    int bufsize, position;
    char **tokens;
    char *token;

    bufsize = 64;
    tokens = malloc(bufsize * sizeof(char *));
    if (!tokens)
    {
        perror("Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, ":");
    position = 0;
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        token = strtok(NULL, ":");
    }
    tokens[position] = NULL;
    return tokens;
}

